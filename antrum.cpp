#include "antrum.h"

bool CharUtil::IsDigit(char c)
{
	int cInt = (int)c;
	return (cInt >= 48 && cInt <= 57);
}

bool CharUtil::IsNewline(char c)
{
	return c == '\n';
}

bool CharUtil::IsTab(char c)
{
	return c == '\t';
}

bool CharUtil::IsSpace(char c)
{
	return c == ' ';
}

bool CharUtil::IsArithmeticSign(char c)
{
	return (c == '+' || c == '-' || c == '/' || c == '*');
}

bool CharUtil::IsDot(char c)
{
	return c == '.';
}

uint8 CharUtil::ToDigit(char c)
{
	return uint8(c - '0');
}

ParseNumberResult ParseNumber(const char* reader, DataType dataType, char endChar)
{
	ParseNumberResult result = {};
	bool negative = false;
	if (*reader == '-')
	{
		negative = true;
		reader++;
	}

	switch (dataType)
	{
	case DataType::INTEGER:
	{
		while (*reader != endChar)
		{
			if (!CharUtil::IsDigit(*reader)) return result;

			result.number.i = result.number.i * 10 + CharUtil::ToDigit(*reader);
			reader++;
		}

		if (negative)
		{
			result.number.i *= -1;
		}
	} break;


	case DataType::REAL32:
	{
		bool hitDot = false;
		real32 divider = 0.f;

		while (*reader != endChar)
		{
			if (!CharUtil::IsDigit(*reader) && !CharUtil::IsDot(*reader)) return result;

			if (*reader == '.')
			{
				hitDot = true;
				reader++;
				continue;
			}

			if (hitDot)
			{
				divider *= 10.f;
			}

			result.number.r32 = result.number.r32 * 10.f + CharUtil::ToDigit(*reader);
			reader++;
		}

		result.number.r32 /= divider;

		if (negative)
		{
			result.number.r32 *= -1.f;
		}
	} break;
	}

	result.valid = true;
	return result;
}

OBJParser::Vec3ILineResult OBJParser::parseFaceLine(FileReader& fileReader)
{
	Vec3ILineResult res = {};

	//counter += 2;
	fileReader += 2;// +2 is the offset, so we start right onto the correct char
	bool hitSpace = true; // We start with true because we're onto the first char's number
	uint8 inputCounter = 0;

	while (*fileReader.reader != '\n')
	{
		if (hitSpace)
		{
			ParseNumberResult parsingRes = ParseNumber(fileReader.reader, DataType::INTEGER, '/');
			if (!parsingRes.valid) return res;

			if (inputCounter == 0)
			{
				res.vector.a = (uint16)parsingRes.number.i;
				res.vector.a--;
			}
			else if (inputCounter == 1)
			{
				res.vector.b = (uint16)parsingRes.number.i;
				res.vector.b--;
			}
			else
			{
				res.vector.c = (uint16)parsingRes.number.i;
				res.vector.c--;
			}

			inputCounter++;
			hitSpace = false;
			continue;
		}

		if (*fileReader.reader == ' ')
		{
			hitSpace = true;
			//counter++;
			//reader++;
			fileReader++;
			continue;
		}

		//counter++;
		//reader++;
		fileReader++;
	}

	return res;
}

OBJParser::Vec3LineResult OBJParser::parseVec3Line(FileReader& fileReader)
{
	Vec3LineResult res = {};
	String         floatString = {};
	bool           isCurrentlyOntoFloat = false;
	int            floatHeadCounter = 0;
	uint8          floatCounter = 0;

	while (*fileReader.reader != '\n')
	{
		bool wasPreviouslyOntoFloat = isCurrentlyOntoFloat;
		isCurrentlyOntoFloat = (CharUtil::IsArithmeticSign(*fileReader.reader) || CharUtil::IsDigit(*fileReader.reader) || CharUtil::IsDot(*fileReader.reader));

		// First float char
		if (!wasPreviouslyOntoFloat && isCurrentlyOntoFloat)
		{
			floatString.head = fileReader.reader;
			floatHeadCounter = 0;
		}

		// Last float char
		if (wasPreviouslyOntoFloat && !isCurrentlyOntoFloat)
		{
			floatString.size = floatHeadCounter;
			switch (floatCounter)
			{
			case 0: res.vector.x = StringUtil::ToFloat(floatString); break;
			case 1: res.vector.y = StringUtil::ToFloat(floatString); break;
			}
			floatString = {};
			floatCounter++;
		}

		floatHeadCounter++;
		fileReader++;
	}

	// >NOTE: The last char of the line will have us exit the while loop so we finish setting the last float here instead
	floatString.size = floatHeadCounter - 1;
	res.vector.z = StringUtil::ToFloat(floatString);
	res.reader = fileReader.reader;

	return res;
}

real32 StringUtil::ToFloat(const char* string, uint8 size)
{
	bool  negative = *string == '-';
	bool  reachedDot = false;
	int   integer = 0;
	int   divider = 1;
	uint8 counter = negative ? 1 : 0;

	for (counter; counter < size; counter++)
	{
		if (string[counter] == '.')
		{
			reachedDot = true;
			continue;
		}

		integer = integer * 10 + CharUtil::ToDigit(string[counter]);

		if (reachedDot)
		{
			divider *= 10;
		}
	}

	float res = (float)(integer) / divider;
	if (negative)
	{
		res *= -1.0f;
	}

	return res;
}

real32 StringUtil::ToFloat(const String& string)
{
	return StringUtil::ToFloat(string.head, (uint8)string.size);
}

int StringUtil::ToInt(const char* string, uint8 size)
{
	bool negative = *string == '-';
	int integer = 0;
	uint8 counter = negative ? 1 : 0;

	for (counter; counter < size; counter++)
	{
		integer = integer * 10 + CharUtil::ToDigit(string[counter]);
	}

	if (negative)
	{
		integer *= -1;
	}

	return integer;
}

int StringUtil::ToInt(const String& string)
{
	return StringUtil::ToInt(string.head, (uint8)string.size);
}

void ReadFile_OBJ(const char* Filename, GameMemory* Memory, PlatformStorage* platformStorage, MeshAsset& outAsset)
{
	//ReadFileResult res = Win32_Util_ReadFile(Filename, Memory);
	ReadFileResult res = platformStorage->readFile(Filename, Memory);

	//OutputDebugString("--------------------------\n");
	//OutputDebugString(static_cast<const char*>(res.content));
	//OutputDebugString("--------------------------\n");

	OBJParser::OBJFileResult fileRes = {};

	Vec3 vec = {};
	Vec3I indexes = {};
	FileReader fileReader = {};
	fileReader.reader = (const char*)res.content;
	
	OBJParser::Vec3LineResult lineRes = {};
	OBJParser::Vec3ILineResult lineResFaces = {};

	while (fileReader.counter < res.contentSize)
	{
		if (*fileReader.reader == 'v')
		{
			char nextChar = *(fileReader.reader + 1);
			if (CharUtil::IsSpace(nextChar))
			{
				lineRes = OBJParser::parseVec3Line(fileReader);
				outAsset.vertices.push(lineRes.vector.x);
				outAsset.vertices.push(lineRes.vector.y);
				outAsset.vertices.push(lineRes.vector.z);
			}
		}
		else if (*fileReader.reader == 'f')
		{
			lineResFaces = OBJParser::parseFaceLine(fileReader);
			outAsset.indexes.push(lineResFaces.vector.a);
			outAsset.indexes.push(lineResFaces.vector.b);
			outAsset.indexes.push(lineResFaces.vector.c);
		}

		fileReader++;
	}
}


uint32 CeilToNextMultiple(uint32 value, uint32 multiple)
{
	uint32 step = value / multiple + (value % multiple == 0 ? 0 : 1);
	return step * multiple;
}

void InitializeWebGPU(WebGPUStorage* storage, void* wndHandle, void* hInstance, GameMemory* memory, MeshAsset* asset, PlatformStorage* platformStorage)
{
	storage->instance = wgpu::helper::createInstance();
	storage->adapter  = wgpu::helper::createAdapter(storage->instance);
	storage->device   = wgpu::helper::createDevice(storage->adapter, platformStorage->log);
	storage->surface  = wgpu::helper::createSurface(wndHandle, hInstance, storage->instance);

	ReadFileResult file = platformStorage->readFile("../resource/shader.sha", memory);
	ASSERT(file.content);
	WGPUStringView shaderCode = {};
	shaderCode.data           = (const char*)file.content;
	shaderCode.length         = file.contentSize;

	storage->shaderModule    = wgpu::helper::createShaderModule(storage->device, shaderCode, "Xin Shader Module");
	storage->bindGroupLayout = wgpu::helper::createBindGroupLayout(storage->device, sizeof(ShaderUniform));
	storage->pipelineLayout  = wgpu::helper::createPipelineLayout(storage->device, storage->bindGroupLayout);
	storage->renderPipeline  = wgpu::helper::createRenderPipeline(storage->device, storage->shaderModule, storage->surface.getFormat(storage->adapter), storage->pipelineLayout);

	WGPUSurfaceConfiguration config = {};
	config.nextInChain     = nullptr;
	config.width           = WINDOW_WIDTH;
	config.height          = WINDOW_HEIGHT;
	config.format          = storage->surface.getFormat(storage->adapter);
	config.viewFormatCount = 0;
	config.viewFormats     = nullptr;
	config.usage           = WGPUTextureUsage_RenderAttachment;
	config.device          = storage->device.object;
	config.presentMode     = WGPUPresentMode::WGPUPresentMode_Fifo;
	config.alphaMode       = WGPUCompositeAlphaMode::WGPUCompositeAlphaMode_Auto;
	storage->surface.configure(&config);	

	storage->adapter.release();
	storage->shaderModule.release();


	storage->queue = storage->device.getQueueHelper();


	ShaderUniform shaderUniform = {};
	shaderUniform.time = 2.0f;
	shaderUniform.color[0] = 0.0f;
	shaderUniform.color[1] = 1.0f;
	shaderUniform.color[2] = 0.0f;
	shaderUniform.color[3] = 1.0f;

	storage->shaderUniform = shaderUniform; // >TODO: put this inside memory



	WGPUBufferDescriptor bufferDesc = {};
	bufferDesc.nextInChain = nullptr;
	bufferDesc.usage = WGPUBufferUsage_CopyDst | WGPUBufferUsage_Vertex;
	bufferDesc.size = asset->vertices.getElementsSize();
	bufferDesc.size = (bufferDesc.size + 3) & ~3;
	bufferDesc.mappedAtCreation = false;
	storage->pointBuffer = storage->device.createBufferHelper(&bufferDesc);
	storage->pointBuffer.setLabel("Point buffer");
	storage->queue.writeBuffer(storage->pointBuffer, 0, asset->vertices.dataPtr(), bufferDesc.size);

	bufferDesc.size = asset->indexes.getElementsSize();
	bufferDesc.size = (bufferDesc.size + 3) & ~3; // From right to left, dummy
	bufferDesc.usage = WGPUBufferUsage_CopyDst | WGPUBufferUsage_Index;
	bufferDesc.mappedAtCreation = false;
	storage->indexBuffer = storage->device.createBufferHelper(&bufferDesc);
	storage->indexBuffer.setLabel("Index buffer");
	storage->queue.writeBuffer(storage->indexBuffer, 0, asset->indexes.dataPtr(), bufferDesc.size);

	WGPULimits supportedLimits = storage->adapter.getDefaultLimits();
	uint32 uniformBufferStride = CeilToNextMultiple((uint32)sizeof(ShaderUniform), (uint32)supportedLimits.minUniformBufferOffsetAlignment);
	bufferDesc.size = uniformBufferStride + sizeof(ShaderUniform);
	bufferDesc.usage = WGPUBufferUsage_CopyDst | WGPUBufferUsage_Uniform;
	bufferDesc.mappedAtCreation = false;
	storage->uniformBuffer = storage->device.createBufferHelper(&bufferDesc);
	storage->uniformBuffer.setLabel("Uniform buffer");
	storage->queue.writeBuffer(storage->uniformBuffer, 0, &storage->shaderUniform, sizeof(ShaderUniform));



	WGPUBindGroupEntry binding = {};
	binding.nextInChain = nullptr;
	binding.binding = 0; // The index of the binding
	binding.buffer = storage->uniformBuffer.object; // The buffer it is bound to
	binding.offset = 0; // A buffer can contain multiple uniforms
	binding.size = sizeof(ShaderUniform); // i.e. the size of the buffer
	WGPUBindGroupDescriptor bindGroupDesc = {};
	bindGroupDesc.nextInChain = nullptr;
	bindGroupDesc.layout = storage->bindGroupLayout.object;
	bindGroupDesc.entryCount = 1;
	bindGroupDesc.entries = &binding;
	storage->bindGroup = storage->device.createBindGroupHelper(&bindGroupDesc);
	storage->bindGroup.setLabel("Bind group san");
}



XARGS(GameMemory* memory, GameState* gameState, PlatformStorage* platformStorage, MeshAsset* asset, WebGPUStorage* wgpuStorage, void* wndHandle, void* hInstance)
extern "C" GAME_INITIALIZE(Game_Initialize)
{
	// Load assets
	//
	ReadFile_OBJ("../resource/TestOBJ.obj", memory, platformStorage, *asset);

	// Load wgpu
	//
	InitializeWebGPU(wgpuStorage, wndHandle, hInstance, memory, asset, platformStorage);


	gameState->initialized = true;
}


XARGS(GameMemory* memory, GameState* gameState, PlatformStorage* platformStorage, WebGPUStorage* wgpuStorage, MeshAsset* asset)
extern "C" GAME_UPDATE(Game_Update)
{
	if (!gameState->initialized)
	{
		gameState->quit = true;
		return;
	}


	wgpuStorage->queue.writeBuffer(wgpuStorage->uniformBuffer, offsetof(ShaderUniform, ShaderUniform::color), 
		&wgpuStorage->shaderUniform.color, sizeof(ShaderUniform::color));

	wgpu::TextureView targetView = wgpuStorage->surface.getCurrentTextureView();
	ASSERT(targetView.object);

	WGPUCommandEncoderDescriptor encoderDesc = {};
	encoderDesc.nextInChain = nullptr;
	encoderDesc.label.data = "Sexy Command Encoder (SCE)";
	encoderDesc.label.length = strlen(encoderDesc.label.data);
	wgpu::CommandEncoder encoder = wgpuStorage->device.createCommandEncoderHelper(&encoderDesc);


	// Describe Render Pass
	//
	WGPURenderPassColorAttachment renderPassColorAttachment = {};
	renderPassColorAttachment.view = targetView.object;
	renderPassColorAttachment.resolveTarget = nullptr;
	renderPassColorAttachment.loadOp = WGPULoadOp_Clear;
	renderPassColorAttachment.storeOp = WGPUStoreOp_Store;
	renderPassColorAttachment.clearValue = WGPUColor{ 0.15, 0.2, 0.33, 1.0f };
	renderPassColorAttachment.depthSlice = WGPU_DEPTH_SLICE_UNDEFINED;

	WGPURenderPassDescriptor renderPassDesc = {};
	renderPassDesc.colorAttachmentCount = 1;
	renderPassDesc.colorAttachments = &renderPassColorAttachment;
	renderPassDesc.nextInChain = nullptr;
	renderPassDesc.depthStencilAttachment = nullptr;
	renderPassDesc.timestampWrites = nullptr;

	wgpu::RenderPassEncoder renderPass = encoder.beginRenderPassHelper(&renderPassDesc);

	// Use Render Pass
	//
	uint32 dynamicOffset = 0;
	WGPULimits supportedLimits = wgpuStorage->adapter.getDefaultLimits();
	uint32 uniformBufferStride = CeilToNextMultiple((uint32)sizeof(ShaderUniform), (uint32)supportedLimits.minUniformBufferOffsetAlignment);
	dynamicOffset = 0 * uniformBufferStride;
	renderPass.setPipeline(wgpuStorage->renderPipeline);
	renderPass.setVertexBuffer(0, wgpuStorage->pointBuffer, 0, wgpuStorage->pointBuffer.getSize());
	renderPass.setIndexBuffer(wgpuStorage->indexBuffer, WGPUIndexFormat_Uint16, 0, wgpuStorage->indexBuffer.getSize());
	renderPass.setBindGroup(0, wgpuStorage->bindGroup, 1, &dynamicOffset);
	renderPass.drawIndexed((uint32)(asset->indexes.getElementsLength()), 1, 0, 0, 0);
	renderPass.end();
	renderPass.release();

	WGPUCommandBufferDescriptor commandBufferDesc = {};
	commandBufferDesc.nextInChain = nullptr;
	commandBufferDesc.label.data = "Command buffer";
	commandBufferDesc.label.length = strlen(commandBufferDesc.label.data);
	wgpu::CommandBuffer commandBuffer = encoder.finishHelper(&commandBufferDesc);
	encoder.release();

	wgpuStorage->queue.submit(1, &commandBuffer.object);
	commandBuffer.release();
	targetView.release();
	wgpuStorage->surface.present();
	wgpuStorage->device.tick();
}

XARGS(WebGPUStorage* storage)
extern "C" GAME_QUIT(Game_Quit)
{
	storage->renderPipeline.release();
	storage->surface.unconfigure();
	storage->queue.release();
	storage->surface.release();
	storage->pipelineLayout.release();
	storage->bindGroup.release();
	storage->bindGroupLayout.release();
	storage->pointBuffer.release();
	storage->indexBuffer.release();
	storage->uniformBuffer.release();
}