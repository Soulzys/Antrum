#include "antrum.h"

#include "windows.h"
#include "win32_antrum.h"

#include <vector>






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

void* MemoryChunk::allocate(size_t Amount)
{
	if (offset + Amount > size)
	{
		OutputDebugString("ERROR | GameMemory::allocate | You attempted to allocate too much memory !\n");
		return nullptr;
	}

	void* memPtr = memory + offset;
	offset += Amount;

	return memPtr;
}

ParseNumberResult Win32_Util_ParseNumber(const char* reader, DataType dataType, char endChar)
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

				result.number.i = result.number.i * 10 + Win32_Util_ConvertCharToDigit(*reader);
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

				result.number.r32 = result.number.r32 * 10.f + Win32_Util_ConvertCharToDigit(*reader);
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
			ParseNumberResult parsingRes = Win32_Util_ParseNumber(fileReader.reader, DataType::INTEGER, '/');
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
				case 0: res.vector.x = Win32_Util_ConvertStringToFloat(floatString); break;
				case 1: res.vector.y = Win32_Util_ConvertStringToFloat(floatString); break;
			}
			floatString = {};
			floatCounter++;
		}

		floatHeadCounter++;
		fileReader++;
	}

	// >NOTE: The last char of the line will have us exit the while loop so we finish setting the last float here instead
	floatString.size = floatHeadCounter - 1;
	res.vector.z = Win32_Util_ConvertStringToFloat(floatString);
	res.reader = fileReader.reader;

	return res;
}


wgpu::Instance createInstance()
{
	// >NOTASCOI: is it of any use to have it here, knowing that our instance is going to be released a few lines below ? Hmmmm...
	const char* toggleName = "enable_immediate_error_handling";

	WGPUDawnTogglesDescriptor toggleDesc = {};
	toggleDesc.chain.next                = nullptr;
	toggleDesc.chain.sType               = WGPUSType::WGPUSType_DawnTogglesDescriptor;
	toggleDesc.disabledToggleCount       = 0;
	toggleDesc.enabledToggleCount        = 1;
	toggleDesc.enabledToggles            = &toggleName;

	WGPUInstanceDescriptor desc = {};
	desc.nextInChain = &toggleDesc.chain;

	wgpu::Instance instance = {};
	instance.object = wgpu::createInstance(&desc);
	if (!instance.object)
	{
		OutputDebugString("ERROR | wgpu::helper::createInstance() | Coud not initialize WebGPU !\n");
	}

	return instance;
}

//void Win32_WGPU_GetInstance(wgpu::Instance& OutInstance)
//{
//	// >NOTASCOI: is it of any use to have it here, knowing that our instance is going to be released a few lines below ? Hmmmm...
//	const char* toggleName = "enable_immediate_error_handling";
//
//	WGPUDawnTogglesDescriptor toggleDesc = {};
//	toggleDesc.chain.next                = nullptr;
//	toggleDesc.chain.sType               = WGPUSType::WGPUSType_DawnTogglesDescriptor;
//	toggleDesc.disabledToggleCount       = 0;
//	toggleDesc.enabledToggleCount        = 1;
//	toggleDesc.enabledToggles            = &toggleName;
//
//	WGPUInstanceDescriptor desc = {};
//	desc.nextInChain = &toggleDesc.chain;
//
//	OutInstance.instance = wgpuCreateInstance(&desc);
//
//	if (!OutInstance.instance)
//	{
//		OutputDebugString("ERROR | Win32_WGPU_GetInstance() | Coud not initialize WebGPU !\n");
//	}
//}


WGPUAdapter requestAdapterAsync(wgpu::Instance instance, WGPURequestAdapterOptions const* options)
{
	struct AdapterRequestData
	{
		WGPUAdapter adapter;
		bool requestEnded;
	};

	AdapterRequestData requestData = {};

	WGPURequestAdapterCallbackInfo callbackInfo = {};
	callbackInfo.nextInChain = nullptr;
	callbackInfo.mode        = WGPUCallbackMode::WGPUCallbackMode_AllowSpontaneous;
	callbackInfo.userdata1   = (void*)&requestData;
	callbackInfo.callback    = [](WGPURequestAdapterStatus Status, WGPUAdapter Adapter, WGPUStringView Message, WGPU_NULLABLE void* UD_1, WGPU_NULLABLE void* UD_2)
		{
			AdapterRequestData& data = *reinterpret_cast<AdapterRequestData*>(UD_1);
			if (Status == WGPURequestAdapterStatus::WGPURequestAdapterStatus_Success)
			{
				data.adapter = Adapter;
			}
			else
			{
				OutputDebugString("ERROR | wgpu::helper::requestAdapterAsync | Coud not get WebGPU adapter :((\n");
			}

			data.requestEnded = true;
		};


	instance.requestAdapter(options, callbackInfo);
	AdapterRequestData& requestDataResult = *reinterpret_cast<AdapterRequestData*>(callbackInfo.userdata1);
	ASSERT(requestDataResult.requestEnded);

	return requestDataResult.adapter;
}

wgpu::Adapter createAdapter(wgpu::Instance instance)
{
	WGPURequestAdapterOptions adapterOptions = {};
	adapterOptions.nextInChain = nullptr;

	wgpu::Adapter adapter = {};
	adapter.object = requestAdapterAsync(instance, &adapterOptions);

	return adapter;
}

//void Win32_WGPU_GetAdapter(wgpu::Instance Instance, wgpu::Adapter& OutAdapter)
//{
//	WGPURequestAdapterOptions adapterOptions = {};
//	adapterOptions.nextInChain = nullptr;
//
//	OutAdapter.adapter = Win32_WGPU_Sync_RequestAdapter(Instance.instance, &adapterOptions);
//}


WGPUDevice requestDeviceAsync(wgpu::Adapter adapter, const WGPUDeviceDescriptor* descriptor)
{
	struct DeviceRequestData
	{
		WGPUDevice device;
		bool requestEnded;
	}; 

	DeviceRequestData requestData = {};	

	WGPURequestDeviceCallbackInfo callbackInfo = {};
	callbackInfo.nextInChain = nullptr;
	callbackInfo.mode        = WGPUCallbackMode::WGPUCallbackMode_AllowSpontaneous;
	callbackInfo.userdata1   = (void*)&requestData;
	callbackInfo.callback    = [](WGPURequestDeviceStatus Status, WGPUDevice Device, WGPUStringView Message, WGPU_NULLABLE void* UD_1, WGPU_NULLABLE void* UD_2)
	{
		DeviceRequestData& data = *reinterpret_cast<DeviceRequestData*>(UD_1);

		if (Status == WGPURequestDeviceStatus::WGPURequestDeviceStatus_Success)
		{
			data.device = Device;
		}
		else
		{
			OutputDebugString("ERROR | Could not get WebGPU device :((\n");
		}

		data.requestEnded = true;
	};

	adapter.requestDevice(descriptor, callbackInfo);
	DeviceRequestData& requestDataResult = *reinterpret_cast<DeviceRequestData*>(callbackInfo.userdata1);
	ASSERT(requestDataResult.requestEnded);

	return requestDataResult.device;
}

wgpu::Device createDevice(wgpu::Adapter adapter)
{
	// GPU Features
	//
	WGPULimits limits = adapter.getDefaultLimits();
	limits.maxVertexAttributes             = 2;
	limits.maxVertexBuffers                = 1;
	limits.maxBufferSize                   = 6 * 6 * sizeof(real32);
	limits.maxVertexBufferArrayStride      = 5 * sizeof(real32);
	limits.maxInterStageShaderVariables    = 3;
	limits.maxBindGroups                   = 1;
	limits.maxUniformBuffersPerShaderStage = 1;
	limits.maxUniformBufferBindingSize     = 16 * 4;
	limits.maxDynamicUniformBuffersPerPipelineLayout = 1;

	// Requesting a device
	//
	WGPUDeviceDescriptor deviceDesc        = {};
	deviceDesc.nextInChain                 = nullptr;
	deviceDesc.label.data                  = "Device-san";
	deviceDesc.label.length                = strlen(deviceDesc.label.data);
	deviceDesc.requiredFeatureCount        = 0;
	deviceDesc.requiredLimits              = &limits;
	deviceDesc.deviceLostCallbackInfo      = Win32_WGPU_Callback_DeviceLost();
	deviceDesc.uncapturedErrorCallbackInfo = Win32_WGPU_Callback_UncapturedError();
	deviceDesc.defaultQueue.nextInChain    = nullptr;
	deviceDesc.defaultQueue.label.data     = "Default Queue-san";
	deviceDesc.defaultQueue.label.length   = strlen(deviceDesc.defaultQueue.label.data);

	wgpu::Device device = {};
	device.object = requestDeviceAsync(adapter, &deviceDesc);

	return device;
}


void Win32_WGPU_GetDefaultBindingLayout(WGPUBindGroupLayoutEntry& bindingLayout)
{
	bindingLayout.buffer.nextInChain           = nullptr;
	bindingLayout.buffer.type                  = WGPUBufferBindingType_Undefined;
	bindingLayout.buffer.hasDynamicOffset      = false;

	bindingLayout.sampler.nextInChain          = nullptr;
	bindingLayout.sampler.type                 = WGPUSamplerBindingType_BindingNotUsed;

	bindingLayout.storageTexture.nextInChain   = nullptr;
	bindingLayout.storageTexture.access        = WGPUStorageTextureAccess_BindingNotUsed;
	bindingLayout.storageTexture.format        = WGPUTextureFormat_Undefined;
	bindingLayout.storageTexture.viewDimension = WGPUTextureViewDimension_Undefined;

	bindingLayout.texture.nextInChain          = nullptr;
	bindingLayout.texture.multisampled         = false;
	bindingLayout.texture.sampleType           = WGPUTextureSampleType_BindingNotUsed;
	bindingLayout.texture.viewDimension        = WGPUTextureViewDimension_Undefined;
}

uint32 Win32_WGPU_Util_CeilToNextMultiple(uint32 Value, uint32 Multiple)
{
	uint32 step = Value / Multiple + (Value % Multiple == 0 ? 0 : 1);
	return step * Multiple;
}


wgpu::Surface createSurface(WNDCLASS* wndClass, HWND wndHandle, wgpu::Instance instance)
{
	WGPUSurfaceSourceWindowsHWND surfaceWindow = {};
	surfaceWindow.hinstance   = wndClass->hInstance;
	surfaceWindow.hwnd        = wndHandle;
	surfaceWindow.chain.next  = nullptr;
	surfaceWindow.chain.sType = WGPUSType_SurfaceSourceWindowsHWND;

	// Getting our surface to draw on screen
	//
	WGPUSurfaceDescriptor surfaceDescNative = {};
	surfaceDescNative.label.data   = "Surface native";
	surfaceDescNative.label.length = strlen(surfaceDescNative.label.data);
	surfaceDescNative.nextInChain  = &surfaceWindow.chain;

	wgpu::Surface surface = {};
	surface.object = instance.createSurface(&surfaceDescNative);

	return surface;
}

wgpu::BindGroupLayout createBindGroupLayout(wgpu::Device device)
{
	// Create a bind group
	//
	WGPUBindGroupLayoutEntry bindingLayoutEntry = {};
	Win32_WGPU_GetDefaultBindingLayout(bindingLayoutEntry); // Setting every other unused fields to default values unsure we only use what we want
	bindingLayoutEntry.binding = 0; // This is the binding index we use in our shader
	bindingLayoutEntry.visibility = WGPUShaderStage_Vertex | WGPUShaderStage_Fragment; // This is the stage that needs to access this resource
	bindingLayoutEntry.buffer.type = WGPUBufferBindingType_Uniform;
	bindingLayoutEntry.buffer.minBindingSize = sizeof(ShaderUniform);
	bindingLayoutEntry.buffer.hasDynamicOffset = true;

	WGPUBindGroupLayoutDescriptor bindGroupLayoutDesc = {};
	bindGroupLayoutDesc.nextInChain = nullptr;
	bindGroupLayoutDesc.entryCount = 1;
	bindGroupLayoutDesc.entries = &bindingLayoutEntry;

	wgpu::BindGroupLayout bindGroupLayout = {};
	bindGroupLayout.object = device.createBindGroupLayout(&bindGroupLayoutDesc);

	return bindGroupLayout;
}

wgpu::PipelineLayout createPipelineLayout(wgpu::Device device, wgpu::BindGroupLayout bindGroupLayout)
{
	WGPUPipelineLayoutDescriptor layoutDesc = {};
	layoutDesc.nextInChain          = nullptr;
	layoutDesc.bindGroupLayoutCount = 1;
	layoutDesc.bindGroupLayouts     = &bindGroupLayout.object;

	wgpu::PipelineLayout pipelineLayout = {};
	pipelineLayout.object = device.createPipelineLayout(&layoutDesc);

	return pipelineLayout;
}

wgpu::RenderPipeline 
createRenderPipeline
(wgpu::Device device, wgpu::ShaderModule shaderModule, WGPUTextureFormat textureFormat, wgpu::PipelineLayout pipelineLayout)
{
	//std::vector<WGPUVertexAttribute> VertexAttributes(2);

	WGPUVertexAttribute pointAttrib;
	pointAttrib.shaderLocation = 0;
	pointAttrib.format         = WGPUVertexFormat_Float32x3;
	pointAttrib.offset         = 0;

	WGPUVertexAttribute colorAttrib;
	colorAttrib.shaderLocation = 1;
	colorAttrib.format         = WGPUVertexFormat_Float32x3;
	colorAttrib.offset         = 3 * sizeof(real32);

	WGPUVertexAttribute vertexAttributes[2] = { pointAttrib, colorAttrib };

	WGPUVertexBufferLayout vertexBufferLayout = {};
	vertexBufferLayout.attributeCount         = 1; //(uint32)VertexAttributes.size();
	//vertexBufferLayout.attributes             = vertexAttributes; //VertexAttributes.data();
	vertexBufferLayout.attributes             = &pointAttrib; //VertexAttributes.data();
	vertexBufferLayout.arrayStride            = 3 * sizeof(real32);
	vertexBufferLayout.stepMode               = WGPUVertexStepMode_Vertex;



	// Pipeline stuff
	//
	WGPUBlendState blendState = {};
	blendState.color.srcFactor = WGPUBlendFactor_SrcAlpha;
	blendState.color.dstFactor = WGPUBlendFactor_OneMinusSrcAlpha;
	blendState.color.operation = WGPUBlendOperation_Add;
	blendState.alpha.srcFactor = WGPUBlendFactor_Zero;
	blendState.alpha.dstFactor = WGPUBlendFactor_One;
	blendState.alpha.operation = WGPUBlendOperation_Add;

	WGPUColorTargetState colorTarget = {};
	colorTarget.format    = textureFormat;
	colorTarget.blend     = &blendState;
	colorTarget.writeMask = WGPUColorWriteMask_All; // We could write to only some of the color channels

	WGPUFragmentState fragmentState = {};
	fragmentState.module            = shaderModule.object;
	fragmentState.entryPoint.data   = "fs_main";
	fragmentState.entryPoint.length = strlen(fragmentState.entryPoint.data);
	fragmentState.constantCount     = 0;
	fragmentState.constants         = nullptr;
	fragmentState.targetCount       = 1; // We have only one target because our render pass has only one output color attachment
	fragmentState.targets           = &colorTarget;
	fragmentState.nextInChain       = nullptr;


	

	WGPURenderPipelineDescriptor pipelineDesc       = {};
	pipelineDesc.nextInChain                        = nullptr;
	pipelineDesc.vertex.bufferCount                 = 1;
	pipelineDesc.vertex.buffers                     = &vertexBufferLayout;
	pipelineDesc.vertex.module                      = shaderModule.object;
	pipelineDesc.vertex.entryPoint.data             = "vs_main";
	pipelineDesc.vertex.entryPoint.length           = strlen(pipelineDesc.vertex.entryPoint.data);
	pipelineDesc.vertex.constantCount               = 0;
	pipelineDesc.vertex.constants                   = nullptr;
	pipelineDesc.vertex.nextInChain                 = nullptr;
	pipelineDesc.primitive.topology                 = WGPUPrimitiveTopology_TriangleList;
	pipelineDesc.primitive.stripIndexFormat         = WGPUIndexFormat_Undefined;
	pipelineDesc.primitive.frontFace                = WGPUFrontFace_CCW;
	// >NOTASCOI: Based on the face orientation. Should eventually set it to 'front'. None is only for debug, so we see everything, nothing is hidden.
	pipelineDesc.primitive.cullMode                 = WGPUCullMode_None;
	pipelineDesc.fragment                           = &fragmentState;
	pipelineDesc.depthStencil                       = nullptr;
	pipelineDesc.multisample.count                  = 1;
	pipelineDesc.multisample.mask                   = ~0u; // Default value for the mask. It means "all bits on"
	pipelineDesc.multisample.alphaToCoverageEnabled = false; // Default value as well. It is irrelevant for count = 1 anyways
	pipelineDesc.layout                             = pipelineLayout.object;

	wgpu::RenderPipeline renderPipeline = {};
	renderPipeline.object = device.createRenderPipeline(&pipelineDesc);

	return renderPipeline;
}

WGPUDeviceLostCallbackInfo Win32_WGPU_Callback_DeviceLost()
{
	WGPUDeviceLostCallbackInfo callbackInfo = {};
	callbackInfo.nextInChain = nullptr;
	callbackInfo.mode        = WGPUCallbackMode_AllowSpontaneous;
	callbackInfo.callback    = [](WGPUDevice const* Device, WGPUDeviceLostReason Reason, WGPUStringView Message, WGPU_NULLABLE void* UD_1, WGPU_NULLABLE void* UD_2)
	{
		char buffer[KILOBYTES(2)];
		if (Message.length >= sizeof(buffer))
		{
			OutputDebugString("ERROR | DeviceLostCallback | Could not print out the Message as the buffer is too small !\n");
			return;
		}

		wsprintf(buffer, "ERROR | DeviceListCallback | ERROR - Reason: %s\n\tERROR - Message: %s\n", Win32_Util_Stringify_WGPUDeviceLostReason(Reason), Message.data);
		OutputDebugString(buffer);
	};

	return callbackInfo;
}

WGPUUncapturedErrorCallbackInfo Win32_WGPU_Callback_UncapturedError()
{
	WGPUUncapturedErrorCallbackInfo callbackInfo = {};
	callbackInfo.nextInChain = {};
	callbackInfo.callback    = [](WGPUDevice const* Device, WGPUErrorType Type, WGPUStringView Message, WGPU_NULLABLE void* UD_1, WGPU_NULLABLE void* UD_2)
	{
		char buffer[KILOBYTES(2)];
		if (Message.length >= sizeof(buffer))
		{
			OutputDebugString("ERROR | UncapturedErrorCallback | Could not print out the Message as the buffer is too small !\n");
			return;
		}

		wsprintf(buffer, "ERROR | UncapturedErrorCallback | ERROR - Type: %s\n\tERROR - Message: %s", Win32_Util_Stringify_WGPUErrorType(Type), Message.data);
		OutputDebugString(buffer);
	};

	return callbackInfo;
}

const char* Win32_Util_Stringify_WGPUDeviceLostReason(WGPUDeviceLostReason Reason)
{
	switch (Reason)
	{
		case WGPUDeviceLostReason_Unknown           : return "Unknown";
		case WGPUDeviceLostReason_Destroyed         : return "Destroyed";
		case WGPUDeviceLostReason_CallbackCancelled : return "CallbackCancelled";
		case WGPUDeviceLostReason_FailedCreation    : return "FailedCreation";
		case WGPUDeviceLostReason_Force32           : return "Force32";
		default                                     : return "Could not retrieve a valid Reason :((";
	}
}

const char* Win32_Util_Stringify_WGPUErrorType(WGPUErrorType Err)
{
	switch (Err)
	{
		case WGPUErrorType_NoError     : return "NoError";
		case WGPUErrorType_Validation  : return "Validation";
		case WGPUErrorType_OutOfMemory : return "OutOfMemory";
		case WGPUErrorType_Internal    : return "Internal";
		case WGPUErrorType_Unknown     : return "Unknown";
		case WGPUErrorType_Force32     : return "Force32";
		default                        : return "Could not retrieve a valid ErrorType :((";
	}
}

PLATFORM_READ_FILE(Platform_ReadFile)
//ReadFileResult Win32_Util_ReadFile(const char* Filename, GameMemory* Memory)
{
	ReadFileResult res = {};

	HANDLE fileHandle = CreateFile(filename, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0);
	if (fileHandle == INVALID_HANDLE_VALUE)
	{
		res.message = "ERROR | Win32_Util_ReadFile() | Could not retrieve a handle to the file !\n";
		return res;
	}

	LARGE_INTEGER fileSize;
	if (!GetFileSizeEx(fileHandle, &fileSize))
	{
		res.message = "ERROR | Win32_Util_ReadFile() | Could not retrieve the size of the file !\n";
		return res;
	}

	uint32 fileSize32 = Win32_Util_SafeTruncate_uin64(fileSize.QuadPart);
	res.content = Win32_Util_AllocateReadFileMemory(memory, fileSize32);
	if (!res.content)
	{
		res.message = "ERROR | Win32_Util_ReadFile() | Your file is too big !\n";
		return res;
	}

	DWORD bytesRead;
	if (!ReadFile(fileHandle, res.content, fileSize32, &bytesRead, 0))
	{
		res.message = "ERROR | Win32_Util_ReadFile() | Could not read the file !\n";
		memory->readFileChunk.offset -= fileSize32; // Deallocate
		return res;
	}
	if (bytesRead != fileSize32)
	{
		res.message = "ERROR | Win32_Util_ReadFile() | We did not read all of the bytes we expected !\n";
		memory->readFileChunk.offset -= fileSize32; // Deallocate
		return res;
	}

	res.contentSize = fileSize32;

	// Deallocate
	//Memory->ReadFileMemory.offset = 0;
	//Memory->ReadFileMemory.memory = nullptr;

	CloseHandle(fileHandle);

	return res;
}

size_t Win32_Util_StringSize(const char* Str)
{
	size_t counter = 0;

	while (Str[counter] != '\0')
	{
		counter++;

		if (counter == STRING_MAX_LENGTH)
		{
			OutputDebugString("ERROR | Win32_Util_StringSize | const char* too long !\n");
			return 0;
		}
	}

	return counter;
}

uint8 Win32_Util_ConvertCharToDigit(char Char)
{
	return uint8(Char - '0');
}

int Win32_Util_ConvertStringToInt(const char* String, uint8 Size)
{
	bool negative = *String == '-';
	int integer = 0;
	uint8 counter = negative ? 1 : 0;

	for (counter; counter < Size; counter++)
	{
		integer = integer * 10 + Win32_Util_ConvertCharToDigit(String[counter]);
	}

	if (negative)
	{
		integer *= -1;
	}

	return integer;
}

real32 Win32_Util_ConvertStringToFloat(const char* String, uint8 Size)
{
	bool  negative   = *String == '-';
	bool  reachedDot = false;
	int   integer    = 0;
	int   divider    = 1;
	uint8 counter    = negative ? 1 : 0;

	for (counter; counter < Size; counter++)
	{
		if (String[counter] == '.')
		{
			reachedDot = true;
			continue;
		}

		integer = integer * 10 + Win32_Util_ConvertCharToDigit(String[counter]);

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

int Win32_Util_ConvertStringToInt(const String& String)
{
	return Win32_Util_ConvertStringToInt(String.head, (uint8)String.size);
}

real32 Win32_Util_ConvertStringToFloat(const String& String)
{
	return Win32_Util_ConvertStringToFloat(String.head, (uint8)String.size);
}


MeshAsset Win32_Util_ReadFile_OBJ(const char* Filename, GameMemory* Memory)
{
	MeshAsset asset = {};
	//ReadFileResult res = Win32_Util_ReadFile(Filename, Memory);
	ReadFileResult res = Platform_ReadFile(Filename, Memory);

	OutputDebugString("--------------------------\n");
	OutputDebugString(static_cast<const char*>(res.content));
	OutputDebugString("--------------------------\n");

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
				asset.vertices.push(lineRes.vector.x);
				asset.vertices.push(lineRes.vector.y);
				asset.vertices.push(lineRes.vector.z);
			}
		}
		else if (*fileReader.reader == 'f')
		{
			lineResFaces = OBJParser::parseFaceLine(fileReader);
			asset.indexes.push(lineResFaces.vector.a);
			asset.indexes.push(lineResFaces.vector.b);
			asset.indexes.push(lineResFaces.vector.c);
		}

		fileReader++;
	}

	return asset;
}

wgpu::ShaderModule createShaderModule(wgpu::Device device, GameMemory* memory, const char* path, const char* label)
{
	//ReadFileResult file = Win32_Util_ReadFile(path, memory);
	ReadFileResult file = Platform_ReadFile(path, memory);
	if (!file.content)
	{
		OutputDebugString(file.message);
	}

	WGPUShaderModuleDescriptor shaderModuleDesc = {};
	shaderModuleDesc.label.data = label;
	shaderModuleDesc.label.length = strlen(label);

	WGPUShaderSourceWGSL shaderCodeDesc = {};
	shaderCodeDesc.chain.next = nullptr;
	shaderCodeDesc.chain.sType = WGPUSType_ShaderSourceWGSL;
	shaderCodeDesc.code.data = static_cast<const char*>(file.content);
	shaderCodeDesc.code.length = file.contentSize;

	shaderModuleDesc.nextInChain = &shaderCodeDesc.chain;

	wgpu::ShaderModule shaderModule = {};
	shaderModule.object = device.createShaderModule(&shaderModuleDesc);

	return shaderModule;
}



uint32 Win32_Util_SafeTruncate_uin64(uint64 Value)
{
	ASSERT(Value <= 0xFFFFFFFF);

	uint32 res = (uint32)Value;
	return res;
}

char* Win32_Util_AllocateReadFileMemory(GameMemory* Memory, size_t Size)
{
	if (Memory->readFileChunk.offset + Size >= Memory->readFileChunk.size)
	{
		OutputDebugString("ERROR | Win32_Util_AllocateReadFileMemory | You asked for too much !\n");
		return nullptr;
	}

	char* ptr = Memory->readFileChunk.memory + Memory->readFileChunk.offset;
	Memory->readFileChunk.offset += Size;

	return ptr;
}


void Win32_ProcessPendingMessages(GameState* gameState)
{
	MSG msg = {};
	while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
	{
		switch (msg.message)
		{
			case WM_QUIT:
			{
				gameState->quit = true;
			} break;

			case WM_SYSKEYDOWN:
			case WM_SYSKEYUP:
			case WM_KEYDOWN:
			case WM_KEYUP:
			{
				uint32 vkCode = (uint32)msg.wParam;
				if (vkCode == 'A') OutputDebugString("A KEY PRESSED !\n");
				if (vkCode == 'D') OutputDebugString("D KEY PRESSED !\n");
				if (vkCode == VK_ESCAPE) gameState->quit = true;
			} break;

			default:
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			} break;
		}
	}
}

LRESULT CALLBACK Win32_MainWindowCallback(HWND Window, UINT Message, WPARAM WParam, LPARAM LParam)
{
	LRESULT result = 0;

	switch (Message)
	{
		case WM_DESTROY:
		case WM_CLOSE:
		{
			//gRunning = false;
		} break;

		default:
		{
			result = DefWindowProc(Window, Message, WParam, LParam);
		} break;
	}

	return result;
}

void Win32_WGPU_Util_Initialize()
{

}

struct Win32GameDLL
{
	HMODULE DLL;
	game_update* update;
};

Win32GameDLL Win32_LoadGameDLL()
{
	Win32GameDLL game = {};
	game.DLL = LoadLibrary("antrum.dll");
	ASSERT(game.DLL)

	game.update = (game_update*)(GetProcAddress(game.DLL, "Game_Update"));
	ASSERT(game.update);

	return game;
}

int CALLBACK WinMain(HINSTANCE Instance, HINSTANCE PrevInstance, LPSTR CmdLine, int CmdShow)
{
	Win32GameDLL gameDLL = Win32_LoadGameDLL();	

	WNDCLASS wndClass      = {};
	wndClass.style         = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	wndClass.hInstance     = Instance;
	wndClass.lpfnWndProc   = Win32_MainWindowCallback;
	wndClass.lpszClassName = "Antrum";

	bool32 success = RegisterClass(&wndClass);
	if (!success) return 0;

	RECT wndRect   = {};
	wndRect.top    = 0;
	wndRect.bottom = WINDOW_HEIGHT;
	wndRect.left   = 0;
	wndRect.right  = WINDOW_WIDTH;
	AdjustWindowRectEx(&wndRect, WS_OVERLAPPEDWINDOW | WS_VISIBLE, false, 0);

	HWND wndHandle = CreateWindowExA
	(
		0,
		wndClass.lpszClassName,
		"Antrum",
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		CW_USEDEFAULT, CW_USEDEFAULT,
		wndRect.right - wndRect.left,
		wndRect.bottom - wndRect.top, 
		0, 0, 
		wndClass.hInstance, 
		0
	);

	GameMemory gameMemory           = {};
	gameMemory.fattyChunk.size      = MEMSIZE_GAME;
	gameMemory.fattyChunk.memory    = static_cast<char*>(VirtualAlloc(0, gameMemory.fattyChunk.size, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE));
	gameMemory.readFileChunk.size   = MEMSIZE_READ_FILE;
	gameMemory.readFileChunk.memory = gameMemory.fattyChunk.memory;
	gameMemory.assetsChunk.size     = MEMSIZE_ASSETS;
	gameMemory.assetsChunk.memory   = gameMemory.readFileChunk.memory + gameMemory.readFileChunk.size;

	GameState gameState = {};

	PlatformStorage platformStorage = {};
	platformStorage.readFile = Platform_ReadFile;



	



	AssetManager assetManager = {};
	MeshAsset asset = Win32_Util_ReadFile_OBJ("../resource/TestOBJ.obj", &gameMemory);
	
	// WGPU initialization
	//
	wgpu::Instance        instance        = createInstance        ();
	wgpu::Adapter         adapter         = createAdapter         (instance);
	wgpu::Device          device          = createDevice          (adapter);
	wgpu::Surface         surface         = createSurface         (&wndClass, wndHandle, instance);
	wgpu::ShaderModule    shaderModule    = createShaderModule    (device, &gameMemory, "../resource/shader.sha", "Xin Shader Module");
	wgpu::BindGroupLayout bindGroupLayout = createBindGroupLayout (device);
	wgpu::PipelineLayout  pipelineLayout  = createPipelineLayout  (device, bindGroupLayout);
	wgpu::RenderPipeline  renderPipeline  = createRenderPipeline  (device, shaderModule, surface.getFormat(adapter), pipelineLayout);

	WGPUSurfaceConfiguration config = {};
	config.nextInChain     = nullptr;
	config.width           = WINDOW_WIDTH;
	config.height          = WINDOW_HEIGHT;
	config.format          = surface.getFormat(adapter);
	config.viewFormatCount = 0;
	config.viewFormats     = nullptr;
	config.usage           = WGPUTextureUsage_RenderAttachment;
	config.device          = device.object;
	config.presentMode     = WGPUPresentMode::WGPUPresentMode_Fifo;
	config.alphaMode       = WGPUCompositeAlphaMode::WGPUCompositeAlphaMode_Auto;
	surface.configure(&config);	

	adapter.release();
	shaderModule.release();


	wgpu::Queue queue = device.getQueueHelper();


	ShaderUniform shaderUniform = {};
	shaderUniform.time = 2.0f;
	shaderUniform.color[0] = 0.0f;
	shaderUniform.color[1] = 1.0f;
	shaderUniform.color[2] = 0.0f;
	shaderUniform.color[3] = 1.0f;



	WGPUBufferDescriptor bufferDesc = {};
	bufferDesc.nextInChain = nullptr;
	bufferDesc.usage = WGPUBufferUsage_CopyDst | WGPUBufferUsage_Vertex;
	bufferDesc.size = asset.vertices.getElementsSize();
	bufferDesc.size = (bufferDesc.size + 3) & ~3;
	bufferDesc.mappedAtCreation = false;
	wgpu::Buffer pointBuffer = device.createBufferHelper(&bufferDesc);
	pointBuffer.setLabel("Point buffer");
	queue.writeBuffer(pointBuffer, 0, asset.vertices.dataPtr(), bufferDesc.size);

	//bufferDesc.size = indexData.size() * sizeof(uint16);
	bufferDesc.size = asset.indexes.getElementsSize();
	bufferDesc.size = (bufferDesc.size + 3) & ~3; // From right to left, dummy
	bufferDesc.usage = WGPUBufferUsage_CopyDst | WGPUBufferUsage_Index;
	bufferDesc.mappedAtCreation = false;
	wgpu::Buffer indexBuffer = device.createBufferHelper(&bufferDesc);
	indexBuffer.setLabel("Index buffer");
	queue.writeBuffer(indexBuffer, 0, asset.indexes.dataPtr(), bufferDesc.size);

    //WGPULimits supportedLimits = Win32_WGPU_GetDefaultLimits(wgpu.adapter);
	WGPULimits supportedLimits = adapter.getDefaultLimits();
	uint32 uniformBufferStride = Win32_WGPU_Util_CeilToNextMultiple((uint32)sizeof(ShaderUniform), (uint32)supportedLimits.minUniformBufferOffsetAlignment);
	bufferDesc.size = uniformBufferStride + sizeof(ShaderUniform);
	bufferDesc.usage = WGPUBufferUsage_CopyDst | WGPUBufferUsage_Uniform;
	bufferDesc.mappedAtCreation = false;
	wgpu::Buffer uniformBuffer = device.createBufferHelper(&bufferDesc);
	uniformBuffer.setLabel("Uniform buffer");
	queue.writeBuffer(uniformBuffer, 0, &shaderUniform, sizeof(ShaderUniform));
	
	//shaderUniform.color[0] = 0.5f;
	//shaderUniform.color[1] = 1.0f;
	//shaderUniform.color[2] = 0.3f;
	//shaderUniform.color[3] = 1.0f;
	//shaderUniform.time = -1.2f;
	//wgpuQueueWriteBuffer(wgpu.queue, uniformBuffer, uniformBufferStride, &shaderUniform, sizeof(ShaderUniform));



	// Initialize bind groups (it must come from AFTER the creation of the buffer and other resources !)
	//
	WGPUBindGroupEntry binding = {};
	binding.nextInChain = nullptr;
	binding.binding = 0; // The index of the binding
	binding.buffer = uniformBuffer.object; // The buffer it is bound to
	binding.offset = 0; // A buffer can contain multiple uniforms
	binding.size = sizeof(ShaderUniform); // i.e. the size of the buffer
	WGPUBindGroupDescriptor bindGroupDesc = {};
	bindGroupDesc.nextInChain = nullptr;
	bindGroupDesc.layout = bindGroupLayout.object;
	bindGroupDesc.entryCount = 1;
	bindGroupDesc.entries = &binding;
	wgpu::BindGroup bindGroup = device.createBindGroupHelper(&bindGroupDesc);
	bindGroup.setLabel("Bind group san");


	while (!gameState.quit)
	{
		Win32_ProcessPendingMessages(&gameState);

		gameDLL.update(&gameMemory, &gameState, &platformStorage);

		//fakeTime += 0.02f;
		//shaderUniform.time = fakeTime;
		//wgpuQueueWriteBuffer(wgpu.queue, uniformBuffer, offsetof(ShaderUniform, ShaderUniform::time), &shaderUniform.time, sizeof(real32));

		//shaderUniform.color[1] = (real32)sin(fakeTime);
		queue.writeBuffer(uniformBuffer, offsetof(ShaderUniform, ShaderUniform::color), &shaderUniform.color, sizeof(ShaderUniform::color));
		//wgpuQueueWriteBuffer(wgpu.queue, uniformBuffer, offsetof(ShaderUniform, ShaderUniform::color), &shaderUniform.color, sizeof(ShaderUniform::color));
		//wgpuQueueWriteBuffer(wgpu.queue, uniformBuffer, sizeof(real32) * 2, &shaderUniform.color[1], sizeof(real32));


		wgpu::TextureView targetView = surface.getCurrentTextureView();
		ASSERT(targetView.object);


		WGPUCommandEncoderDescriptor encoderDesc = {};
		encoderDesc.nextInChain = nullptr;
		encoderDesc.label.data = "Sexy Command Encoder (SCE)";
		encoderDesc.label.length = strlen(encoderDesc.label.data);
		wgpu::CommandEncoder encoder = device.createCommandEncoderHelper(&encoderDesc);


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
		dynamicOffset = 0 * uniformBufferStride;
		renderPass.setPipeline(renderPipeline);
		renderPass.setVertexBuffer(0, pointBuffer, 0, pointBuffer.getSize());
		renderPass.setIndexBuffer(indexBuffer, WGPUIndexFormat_Uint16, 0, indexBuffer.getSize());
		renderPass.setBindGroup(0, bindGroup, 1, &dynamicOffset);
		renderPass.drawIndexed((uint32)(asset.indexes.getElementsLength()), 1, 0, 0, 0);
		renderPass.end();
		renderPass.release();

		WGPUCommandBufferDescriptor commandBufferDesc = {};
		commandBufferDesc.nextInChain = nullptr;
		commandBufferDesc.label.data = "Command buffer";
		commandBufferDesc.label.length = strlen(commandBufferDesc.label.data);
		wgpu::CommandBuffer commandBuffer = encoder.finishHelper(&commandBufferDesc);
		encoder.release();

		queue.submit(1, &commandBuffer.object);
		commandBuffer.release();
		targetView.release();
		surface.present();
		device.tick();
	}

	// Once we have retrieved our adapter, we do not need the WGPUInstance anymore
	renderPipeline.release();
	surface.unconfigure();
	queue.release();
	surface.release();
	pipelineLayout.release();
	bindGroup.release();
	bindGroupLayout.release();
	pointBuffer.release();
	indexBuffer.release();
	uniformBuffer.release();

	return 0;
}