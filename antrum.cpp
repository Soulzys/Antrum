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


M4 M4::identity()
{
	M4 o = {};
	o.m[0][0] = 1.0f; o.m[0][1] = 0.0f; o.m[0][2] = 0.0f; o.m[0][3] = 0.0f;
	o.m[1][0] = 0.0f; o.m[1][1] = 1.0f; o.m[1][2] = 0.0f; o.m[1][3] = 0.0f;
	o.m[2][0] = 0.0f; o.m[2][1] = 0.0f; o.m[2][2] = 1.0f; o.m[2][3] = 0.0f;
	o.m[3][0] = 0.0f; o.m[3][1] = 0.0f; o.m[3][2] = 0.0f; o.m[3][3] = 1.0f;

	return o;
}

M4 M4::translate(real32 x, real32 y, real32 z)
{
	M4 o = {};
	o.m[0][0] = 1.0f; o.m[0][1] = 0.0f; o.m[0][2] = 0.0f; o.m[0][3] = 0.0f;
	o.m[1][0] = 0.0f; o.m[1][1] = 1.0f; o.m[1][2] = 0.0f; o.m[1][3] = 0.0f;
	o.m[2][0] = 0.0f; o.m[2][1] = 0.0f; o.m[2][2] = 1.0f; o.m[2][3] = 0.0f;
	o.m[3][0] =    x; o.m[3][1] =    z; o.m[3][2] =    y; o.m[3][3] = 1.0f;

	return o;
}

M4 M4::scale(real32 x, real32 y, real32 z)
{
	M4 o = {};
	o.m[0][0] =    x; o.m[0][1] = 0.0f; o.m[0][2] = 0.0f; o.m[0][3] = 0.0f;
	o.m[1][0] = 0.0f; o.m[1][1] =    y; o.m[1][2] = 0.0f; o.m[1][3] = 0.0f;
	o.m[2][0] = 0.0f; o.m[2][1] = 0.0f; o.m[2][2] =    z; o.m[2][3] = 0.0f;
	o.m[3][0] = 0.0f; o.m[3][1] = 0.0f; o.m[3][2] = 0.0f; o.m[3][3] = 1.0f;

	return o;
}

M4 M4::scale(real32 v)
{
	M4 o = {};
	o.m[0][0] =    v; o.m[0][1] = 0.0f; o.m[0][2] = 0.0f; o.m[0][3] = 0.0f;
	o.m[1][0] = 0.0f; o.m[1][1] =    v; o.m[1][2] = 0.0f; o.m[1][3] = 0.0f;
	o.m[2][0] = 0.0f; o.m[2][1] = 0.0f; o.m[2][2] =    v; o.m[2][3] = 0.0f;
	o.m[3][0] = 0.0f; o.m[3][1] = 0.0f; o.m[3][2] = 0.0f; o.m[3][3] = 1.0f;

	return o;
}

M4 M4::rotateX(real32 a)
{
	M4 o = {};
	o.m[0][0] = 1.0f; o.m[0][1] =              0.0f; o.m[0][2] =           0.0f; o.m[0][3] = 0.0f;
	o.m[1][0] = 0.0f; o.m[1][1] =    (real32)cos(a); o.m[1][2] = (real32)sin(a); o.m[1][3] = 0.0f;
	o.m[2][0] = 0.0f; o.m[2][1] = (real32)(-sin(a)); o.m[2][2] = (real32)cos(a); o.m[2][3] = 0.0f;
	o.m[3][0] = 0.0f; o.m[3][1] =              0.0f; o.m[3][2] =           0.0f; o.m[3][3] = 1.0f;

	return o;
}

M4 M4::rotateY(real32 a)
{
	M4 o = {};
	o.m[0][0] = (real32)cos(a); o.m[0][1] = (real32)(-sin(a)); o.m[0][2] = 0.0f; o.m[0][3] = 0.0f;
	o.m[1][0] = (real32)sin(a); o.m[1][1] =    (real32)cos(a); o.m[1][2] = 0.0f; o.m[1][3] = 0.0f;
	o.m[2][0] =           0.0f; o.m[2][1] =              0.0f; o.m[2][2] = 1.0f; o.m[2][3] = 0.0f;
	o.m[3][0] =           0.0f; o.m[3][1] =              0.0f; o.m[3][2] = 0.0f; o.m[3][3] = 1.0f;
	
	return o;
}

M4 M4::rotateZ(real32 a)
{
	M4 o = {};
	o.m[0][0] =    (real32)cos(a); o.m[0][1] = 0.0f; o.m[0][2] = (real32)sin(a); o.m[0][3] = 0.0f;
	o.m[1][0] =              0.0f; o.m[1][1] = 1.0f; o.m[1][2] =           0.0f; o.m[1][3] = 0.0f;
	o.m[2][0] = (real32)(-sin(a)); o.m[2][1] = 0.0f; o.m[2][2] = (real32)cos(a); o.m[2][3] = 0.0f;
	o.m[3][0] =              0.0f; o.m[3][1] = 0.0f; o.m[3][2] =           0.0f; o.m[3][3] = 1.0f;
	
	return o;
}

real32* M4::operator[](uint8 i)
{
	return m[i];
}

const real32* M4::operator[](uint8 i) const
{
	return m[i];
}

M4 M4::operator*(const M4& n)
{
	M4 o;

	for (uint8 i = 0; i < 4; i++)
	{
		for (uint8 j = 0; j < 4; j++)
		{
			o[i][j] = m[i][0] * n[0][j] + 
					  m[i][1] * n[1][j] + 
					  m[i][2] * n[2][j] + 
					  m[i][3] * n[3][j] ;
		}
	}

	return o;
}

M4& M4::operator*=(const M4& n)
{
	*this = *this * n;
	return *this;
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

OBJParser::LineResult<uint16> OBJParser::parseFaceLine(FileReader& fileReader)
{
	LineResult<uint16> res = {};

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
				res.vector.x = (uint16)parsingRes.number.i;
				res.vector.x--;
			}
			else if (inputCounter == 1)
			{
				res.vector.y = (uint16)parsingRes.number.i;
				res.vector.y--;
			}
			else
			{
				res.vector.z = (uint16)parsingRes.number.i;
				res.vector.z--;
			}

			inputCounter++;
			hitSpace = false;
			continue;
		}

		if (*fileReader.reader == ' ')
		{
			hitSpace = true;
			fileReader++;
			continue;
		}

		fileReader++;
	}

	return res;
}

OBJParser::LineResult<real32> OBJParser::parseVerticesLine(FileReader& fileReader)
{
	LineResult<real32> res                  = {};
	String             floatString          = {};
	bool               isCurrentlyOntoFloat = false;
	int                floatHeadCounter     = 0;
	uint8              floatCounter         = 0;

	while (*fileReader.reader != '\n')
	{
		bool wasPreviouslyOntoFloat = isCurrentlyOntoFloat;
		isCurrentlyOntoFloat = (CharUtil::IsArithmeticSign(*fileReader.reader) || CharUtil::IsDigit(*fileReader.reader) || CharUtil::IsDot(*fileReader.reader));

		// First char of float number
		if (!wasPreviouslyOntoFloat && isCurrentlyOntoFloat)
		{
			floatString.head = fileReader.reader;
			floatHeadCounter = 0;
		}

		// Last char of float number
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
	floatString.size = floatHeadCounter;
	res.vector.z     = StringUtil::ToFloat(floatString);
	res.reader       = fileReader.reader;

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

MeshAsset LoadOBJ(const char* filename, GameMemory* memory, PlatformFunctions* platformFunctions)
{
	MeshAsset asset = {};
	ReadFileResult res = platformFunctions->readFile(filename, memory);

	FileReader fileReader = {};
	fileReader.reader = (const char*)res.content;
	
	OBJParser::LineResult<real32> vertices = {};
	OBJParser::LineResult<real32> normals  = {};
	OBJParser::LineResult<uint16> faces    = {};

	while (fileReader.counter < res.contentSize)
	{
		if (*fileReader.reader == 'v')
		{
			char nextChar = *(fileReader.reader + 1);
			if (CharUtil::IsSpace(nextChar))
			{
				vertices = OBJParser::parseVerticesLine(fileReader);
				asset.vertices.push(vertices.vector.x);
				asset.vertices.push(vertices.vector.y);
				asset.vertices.push(vertices.vector.z);
			}
			else if (nextChar == 'n')
			{
				normals = OBJParser::parseVerticesLine(fileReader);
				asset.normals.push(normals.vector.x);
				asset.normals.push(normals.vector.y);
				asset.normals.push(normals.vector.z);
			}
		}
		else if (*fileReader.reader == 'f')
		{
			faces = OBJParser::parseFaceLine(fileReader);
			asset.indexes.push(faces.vector.x);
			asset.indexes.push(faces.vector.y);
			asset.indexes.push(faces.vector.z);
		}

		fileReader++;
	}

	return asset;
}


uint32 CeilToNextMultiple(uint32 value, uint32 multiple)
{
	uint32 step = value / multiple + (value % multiple == 0 ? 0 : 1);
	return step * multiple;
}

void InitializeWebGPU(WebGPUStorage* storage, void* wndHandle, void* hInstance, GameMemory* memory, MeshAsset* asset, PlatformFunctions* platformFunctions)
{
	storage->instance = wgpu::helper::createInstance();
	storage->adapter = wgpu::helper::createAdapter(storage->instance);
	storage->device = wgpu::helper::createDevice(storage->adapter, platformFunctions->log);
	storage->surface = wgpu::helper::createSurface(wndHandle, hInstance, storage->instance);

	ReadFileResult file = platformFunctions->readFile("../resource/shaders/shader.sha", memory);
	ASSERT(file.content);
	WGPUStringView shaderCode = {};
	shaderCode.data = (const char*)file.content;
	shaderCode.length = file.contentSize;

	storage->shaderModule = wgpu::helper::createShaderModule(storage->device, shaderCode, "Xin Shader Module");
	storage->bindGroupLayout = wgpu::helper::createBindGroupLayout(storage->device, sizeof(ShaderUniform));
	storage->pipelineLayout = wgpu::helper::createPipelineLayout(storage->device, storage->bindGroupLayout);
	storage->renderPipeline = wgpu::helper::createRenderPipeline(storage->device, storage->shaderModule, storage->surface.getFormat(storage->adapter), storage->pipelineLayout);

	WGPUSurfaceConfiguration config = {};
	config.nextInChain = nullptr;
	config.width = WINDOW_WIDTH;
	config.height = WINDOW_HEIGHT;
	config.format = storage->surface.getFormat(storage->adapter);
	config.viewFormatCount = 0;
	config.viewFormats = nullptr;
	config.usage = WGPUTextureUsage_RenderAttachment;
	config.device = storage->device.object;
	config.presentMode = WGPUPresentMode::WGPUPresentMode_Fifo;
	config.alphaMode = WGPUCompositeAlphaMode::WGPUCompositeAlphaMode_Auto;
	storage->surface.configure(&config);

	storage->adapter.release();
	storage->shaderModule.release();

	storage->queue = storage->device.getQueueHelper();



	WGPUTextureFormat depthTextureFormat = WGPUTextureFormat_Depth24Plus;
	WGPUTextureDescriptor depthTextureDesc = {};
	depthTextureDesc.dimension = WGPUTextureDimension_2D;
	depthTextureDesc.format = depthTextureFormat;
	depthTextureDesc.mipLevelCount = 1;
	depthTextureDesc.sampleCount = 1;
	depthTextureDesc.size = { WINDOW_WIDTH , WINDOW_HEIGHT, 1 };
	depthTextureDesc.usage = WGPUTextureUsage_RenderAttachment;
	depthTextureDesc.viewFormatCount = 1;
	depthTextureDesc.viewFormats = &depthTextureFormat;
	storage->depthTexture = storage->device.createTextureHelper(&depthTextureDesc);

	WGPUTextureViewDescriptor depthTextureViewDesc = {};
	depthTextureViewDesc.aspect = WGPUTextureAspect_DepthOnly;
	depthTextureViewDesc.baseArrayLayer = 0;
	depthTextureViewDesc.arrayLayerCount = 1;
	depthTextureViewDesc.baseMipLevel = 0;
	depthTextureViewDesc.mipLevelCount = 1;
	depthTextureViewDesc.dimension = WGPUTextureViewDimension_2D;
	depthTextureViewDesc.format = depthTextureFormat;
	storage->depthTextureView = storage->depthTexture.createViewHelper(&depthTextureViewDesc);




	real32 ratio       = (real32)(WINDOW_WIDTH / WINDOW_HEIGHT);
	real32 focalLength = 1.0f;
	real32 near        = 0.01f;
	real32 far         = 100.0f;
	real32 divides     = 1.0f / (far - near);

	ShaderUniform shaderUniform = {};

	shaderUniform.projectionMatrix =
	{
		focalLength,                 0.0,                   0.0, 0.0,
		0.0        , focalLength * ratio,                   0.0, 0.0,
		0.0        ,                 0.0,         far * divides, 1.0,
		0.0        ,                 0.0, -far * near * divides, 0.0
	};

	shaderUniform.viewMatrix =
	{
		1.0, 0.0, 0.0, 0.0,
		0.0, 1.0, 0.0, 0.0,
		0.0, 0.0, 1.0, 0.0,
		0.0, 0.0, 0.0, 1.0
	};

	shaderUniform.modelMatrix =
	{
		1.0, 0.0, 0.0, 0.0,
		0.0, 1.0, 0.0, 0.0,
		0.0, 0.0, 1.0, 0.0,
		0.0, 0.0, 0.0, 1.0
	};

	shaderUniform.time = 0.0f;
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

	bufferDesc.usage = WGPUBufferUsage_CopyDst | WGPUBufferUsage_Vertex;
	bufferDesc.size = asset->normals.getElementsSize();
	bufferDesc.size = (bufferDesc.size + 3) & ~3;
	bufferDesc.mappedAtCreation = false;
	storage->normalBuffer = storage->device.createBufferHelper(&bufferDesc);
	storage->normalBuffer.setLabel("Normal buffer");
	storage->queue.writeBuffer(storage->normalBuffer, 0, asset->normals.dataPtr(), bufferDesc.size);

	bufferDesc.usage = WGPUBufferUsage_CopyDst | WGPUBufferUsage_Index;
	bufferDesc.size = asset->indexes.getElementsSize();
	bufferDesc.size = (bufferDesc.size + 3) & ~3; // From right to left, dummy
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



XARGS(GameMemory* memory, GameState* gameState, PlatformFunctions* platformFunctions, MeshAsset* asset, WebGPUStorage* wgpuStorage, void* wndHandle, void* hInstance)
extern "C" GAME_INITIALIZE(Game_Initialize)
{
	// Load assets
	//
	//LoadOBJ("../resource/TestOBJ.obj", memory, platformStorage, *asset);
	//LoadOBJ("../resource/Pyramid_01.obj", memory, platformStorage, *asset);
	*asset = LoadOBJ("../resource/Suzy.obj", memory, platformFunctions);
	//size_t vSize = asset->vertices.getElementsLength();

	// Load wgpu
	//
	InitializeWebGPU(wgpuStorage, wndHandle, hInstance, memory, asset, platformFunctions);


	gameState->initialized = true;
}


XARGS(GameMemory* memory, GameState* gameState, PlatformFunctions* platformFunctions, WebGPUStorage* wgpuStorage, MeshAsset* asset)
extern "C" GAME_UPDATE(Game_Update)
{
	if (!gameState->initialized)
	{
		gameState->quit = true;
		return;
	}

	wgpuStorage->shaderUniform.time += 0.0008f;

	// Object
	M4 S  = M4::scale(0.6f);
	M4 T1 = M4::translate(0.0f, 0.0f, 0.0f);
	M4 R1 = M4::rotateX(wgpuStorage->shaderUniform.time);
	wgpuStorage->shaderUniform.modelMatrix = R1 * T1 * S;

	// View
	M4 T2 = M4::translate(0.0, 5.0, 0.0f);
	M4 R2 = M4::rotateX(PI / 8.0f);
	M4 R3 = M4::rotateZ(PI / 4.0f);
	wgpuStorage->shaderUniform.viewMatrix = /*R3 * R2 * */ T2;


	// Update the uniform time 
	wgpuStorage->queue.writeBuffer(wgpuStorage->uniformBuffer, offsetof(ShaderUniform, ShaderUniform::time), 
		&wgpuStorage->shaderUniform.time, sizeof(ShaderUniform::time));

	wgpuStorage->queue.writeBuffer(wgpuStorage->uniformBuffer, offsetof(ShaderUniform, ShaderUniform::projectionMatrix),
		&wgpuStorage->shaderUniform.projectionMatrix, sizeof(ShaderUniform::projectionMatrix));

	wgpuStorage->queue.writeBuffer(wgpuStorage->uniformBuffer, offsetof(ShaderUniform, ShaderUniform::viewMatrix),
		&wgpuStorage->shaderUniform.viewMatrix, sizeof(ShaderUniform::viewMatrix));

	wgpuStorage->queue.writeBuffer(wgpuStorage->uniformBuffer, offsetof(ShaderUniform, ShaderUniform::modelMatrix),
		&wgpuStorage->shaderUniform.modelMatrix, sizeof(ShaderUniform::modelMatrix));

	// Update the uniform color
	//wgpuStorage->queue.writeBuffer(wgpuStorage->uniformBuffer, offsetof(ShaderUniform, ShaderUniform::color), 
	//	&wgpuStorage->shaderUniform.color, sizeof(ShaderUniform::color));

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

	WGPURenderPassDepthStencilAttachment depthStencilAttachment = {};
	depthStencilAttachment.view = wgpuStorage->depthTextureView.object;
	depthStencilAttachment.depthClearValue = 1.0f;
	depthStencilAttachment.depthLoadOp = WGPULoadOp_Clear;
	depthStencilAttachment.depthStoreOp = WGPUStoreOp_Store;
	depthStencilAttachment.depthReadOnly = WGPUOptionalBool_False;
	depthStencilAttachment.stencilClearValue = 0;
	depthStencilAttachment.stencilLoadOp = WGPULoadOp_Undefined; // Dawn specific
	depthStencilAttachment.stencilStoreOp = WGPUStoreOp_Undefined; // Dawn specific
	depthStencilAttachment.stencilReadOnly = WGPUOptionalBool_True;

	WGPURenderPassDescriptor renderPassDesc = {};
	renderPassDesc.colorAttachmentCount = 1;
	renderPassDesc.colorAttachments = &renderPassColorAttachment;
	renderPassDesc.nextInChain = nullptr;
	renderPassDesc.depthStencilAttachment = &depthStencilAttachment;
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
	//renderPass.setVertexBuffer(1, wgpuStorage->normalBuffer, 0, wgpuStorage->pointBuffer.getSize());
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