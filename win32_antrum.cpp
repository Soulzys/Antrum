#include "win32_antrum.h"

#include <vector>






bool gRunning = false;



void Win32_WGPU_GetInstance(WGPUInstance& OutInstance)
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

	OutInstance = wgpuCreateInstance(&desc);

	if (!OutInstance)
	{
		OutputDebugString("ERROR | Win32_WGPU_GetInstance() | Coud not initialize WebGPU !\n");
	}
}

void Win32_WGPU_GetAdapter(WGPUInstance Instance, WGPUAdapter& OutAdapter)
{
	WGPURequestAdapterOptions adapterOptions = {};
	adapterOptions.nextInChain = nullptr;

	OutAdapter = Win32_WGPU_Sync_RequestAdapter(Instance, &adapterOptions);
}

void Win32_WGPU_GetDevice(WGPUAdapter Adapter, WGPUDevice& OutDevice)
{
	// GPU Features
	//
	WGPULimits limits = Win32_WGPU_GetLimits(Adapter);

	// Requesting a device
	//
	WGPUDeviceDescriptor deviceDesc        = {};
	deviceDesc.nextInChain                 = nullptr;
	deviceDesc.label.data                  = "Device-san";
	deviceDesc.label.length                = Win32_Util_StringSize(deviceDesc.label.data);
	deviceDesc.requiredFeatureCount        = 0;
	deviceDesc.requiredLimits              = &limits;
	deviceDesc.deviceLostCallbackInfo      = Win32_WGPU_Callback_DeviceLost();
	deviceDesc.uncapturedErrorCallbackInfo = Win32_WGPU_Callback_UncapturedError();
	deviceDesc.defaultQueue.nextInChain    = nullptr;
	deviceDesc.defaultQueue.label.data     = "Default Queue-san";
	deviceDesc.defaultQueue.label.length   = Win32_Util_StringSize(deviceDesc.defaultQueue.label.data);

	OutDevice = Win32_WGPU_Sync_RequestDevice(Adapter, &deviceDesc);
}

WGPUAdapter Win32_WGPU_Sync_RequestAdapter(WGPUInstance Instance, WGPURequestAdapterOptions const* Options)
{
	struct AdapterRequestData
	{
		WGPUAdapter adapter;
		bool requestEnded;
	};

	AdapterRequestData requestData = {};

	WGPURequestAdapterCallbackInfo callbackInfo = {};
	callbackInfo.nextInChain = nullptr;
	callbackInfo.mode = WGPUCallbackMode::WGPUCallbackMode_AllowSpontaneous;
	callbackInfo.userdata1 = (void*)&requestData;
	callbackInfo.callback = [](WGPURequestAdapterStatus Status, WGPUAdapter Adapter, WGPUStringView Message, WGPU_NULLABLE void* UD_1, WGPU_NULLABLE void* UD_2)
	{
		AdapterRequestData& data = *reinterpret_cast<AdapterRequestData*>(UD_1);
		if (Status == WGPURequestAdapterStatus::WGPURequestAdapterStatus_Success)
		{
			data.adapter = Adapter;
		}
		else
		{
			OutputDebugString("ERROR | Coud not get WebGPU adapter :((\n");
		}

		data.requestEnded = true;
	};

	wgpuInstanceRequestAdapter(Instance, Options, callbackInfo);
	AdapterRequestData& requestDataResult = *reinterpret_cast<AdapterRequestData*>(callbackInfo.userdata1);
	ASSERT(requestDataResult.requestEnded);

	return requestDataResult.adapter;
}

WGPUDevice Win32_WGPU_Sync_RequestDevice(WGPUAdapter Adapter, const WGPUDeviceDescriptor* Descriptor)
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

	wgpuAdapterRequestDevice(Adapter, Descriptor, callbackInfo);
	DeviceRequestData& requestDataResult = *reinterpret_cast<DeviceRequestData*>(callbackInfo.userdata1);
	ASSERT(requestDataResult.requestEnded);

	return requestDataResult.device;
}

WGPULimits Win32_WGPU_GetLimits(WGPUAdapter Adapter)
{
	WGPULimits adapterLimits = {};
	wgpuAdapterGetLimits(Adapter, &adapterLimits);

	WGPULimits limits = {};
	limits.nextInChain = nullptr;

	// Set everything to default
	limits.maxTextureDimension1D                     = WGPU_LIMIT_U32_UNDEFINED;
	limits.maxTextureDimension2D                     = WGPU_LIMIT_U32_UNDEFINED;
	limits.maxTextureDimension3D                     = WGPU_LIMIT_U32_UNDEFINED;
	limits.maxTextureArrayLayers                     = WGPU_LIMIT_U32_UNDEFINED;
	limits.maxBindGroups                             = WGPU_LIMIT_U32_UNDEFINED;
	limits.maxBindGroupsPlusVertexBuffers            = WGPU_LIMIT_U32_UNDEFINED;
	limits.maxBindingsPerBindGroup                   = WGPU_LIMIT_U32_UNDEFINED;
	limits.maxDynamicUniformBuffersPerPipelineLayout = WGPU_LIMIT_U32_UNDEFINED;
	limits.maxDynamicStorageBuffersPerPipelineLayout = WGPU_LIMIT_U32_UNDEFINED;
	limits.maxSampledTexturesPerShaderStage          = WGPU_LIMIT_U32_UNDEFINED;
	limits.maxSamplersPerShaderStage                 = WGPU_LIMIT_U32_UNDEFINED;
	limits.maxStorageBuffersPerShaderStage           = WGPU_LIMIT_U32_UNDEFINED;
	limits.maxStorageTexturesPerShaderStage          = WGPU_LIMIT_U32_UNDEFINED;
	limits.minUniformBufferOffsetAlignment           = WGPU_LIMIT_U32_UNDEFINED;
	limits.minStorageBufferOffsetAlignment           = WGPU_LIMIT_U32_UNDEFINED;
	limits.maxVertexBuffers                          = WGPU_LIMIT_U32_UNDEFINED;
	limits.maxBufferSize                             = WGPU_LIMIT_U64_UNDEFINED;
	limits.maxVertexAttributes                       = WGPU_LIMIT_U32_UNDEFINED;
	limits.maxVertexBufferArrayStride                = WGPU_LIMIT_U32_UNDEFINED;
	limits.maxUniformBuffersPerShaderStage           = WGPU_LIMIT_U32_UNDEFINED;
	limits.maxStorageBufferBindingSize               = WGPU_LIMIT_U64_UNDEFINED;
	limits.maxColorAttachments                       = WGPU_LIMIT_U32_UNDEFINED;
	limits.maxColorAttachmentBytesPerSample          = WGPU_LIMIT_U32_UNDEFINED;
	limits.maxComputeWorkgroupStorageSize            = WGPU_LIMIT_U32_UNDEFINED;
	limits.maxComputeInvocationsPerWorkgroup         = WGPU_LIMIT_U32_UNDEFINED;
	limits.maxComputeWorkgroupSizeX                  = WGPU_LIMIT_U32_UNDEFINED;
	limits.maxComputeWorkgroupSizeY                  = WGPU_LIMIT_U32_UNDEFINED;
	limits.maxComputeWorkgroupSizeZ                  = WGPU_LIMIT_U32_UNDEFINED;
	limits.maxComputeWorkgroupsPerDimension          = WGPU_LIMIT_U32_UNDEFINED;
	limits.maxImmediateSize                          = WGPU_LIMIT_U32_UNDEFINED;

	// These two limits are special
	limits.minUniformBufferOffsetAlignment           = adapterLimits.minUniformBufferOffsetAlignment;
	limits.minStorageBufferOffsetAlignment           = adapterLimits.minStorageBufferOffsetAlignment;


	// Project settings, update whenever needed
	limits.maxVertexAttributes          = 2;
	limits.maxVertexBuffers             = 1;
	limits.maxBufferSize                = 6 * 5 * sizeof(float);
	limits.maxVertexBufferArrayStride   = 5 * sizeof(float);
	limits.maxInterStageShaderVariables = 3;

	return limits;
}


void Win32_WGPU_GetSurface(WNDCLASS* WndClass, HWND WndHandle, WGPUInstance Instance, WGPUSurface& OutSurface)
{
	WGPUSurfaceSourceWindowsHWND surfaceWindow = {};
	surfaceWindow.hinstance   = WndClass->hInstance;
	surfaceWindow.hwnd        = WndHandle;
	surfaceWindow.chain.next  = nullptr;
	surfaceWindow.chain.sType = WGPUSType_SurfaceSourceWindowsHWND;

	// Getting our surface to draw on screen
	//
	WGPUSurfaceDescriptor surfaceDescNative = {};
	surfaceDescNative.label.data   = "Surface native";
	surfaceDescNative.label.length = Win32_Util_StringSize(surfaceDescNative.label.data);
	surfaceDescNative.nextInChain  = &surfaceWindow.chain;

	OutSurface = wgpuInstanceCreateSurface(Instance, &surfaceDescNative);
}

void Win32_WGPU_GetSurfaceFormat(WGPUSurface Surface, WGPUAdapter Adapter, WGPUTextureFormat& OutSurfaceFormat)
{
	WGPUSurfaceCapabilities surfaceCapabilities = {};
	wgpuSurfaceGetCapabilities(Surface, Adapter, &surfaceCapabilities);
	OutSurfaceFormat = surfaceCapabilities.formats[0];
}

void Win32_WGPU_ConfigureSurface(WGPUSurface Surface, WGPUTextureFormat SurfaceFormat, WGPUDevice Device, WGPUAdapter Adapter)
{
	WGPUSurfaceConfiguration config = {};
	config.nextInChain     = nullptr;
	config.width           = WINDOW_WIDTH;
	config.height          = WINDOW_HEIGHT;
	config.format          = SurfaceFormat;
	config.viewFormatCount = 0;
	config.viewFormats     = nullptr;
	config.usage           = WGPUTextureUsage_RenderAttachment;
	config.device          = Device;
	config.presentMode     = WGPUPresentMode::WGPUPresentMode_Fifo;
	config.alphaMode       = WGPUCompositeAlphaMode::WGPUCompositeAlphaMode_Auto;
	wgpuSurfaceConfigure(Surface, &config);	
}

void Win32_WGPU_GetShaderModule(WGPUDevice Device, WGPUShaderModule& OutShaderModule, GameMemory* Memory)
{
	ReadFileResult file = Win32_Util_ReadFile("../resource/shader.sha", Memory);
	if (!file.content)
	{
		OutputDebugString(file.message);
		return;
	}

	WGPUShaderModuleDescriptor shaderModuleDesc = {};
	shaderModuleDesc.label.data   = "Shader Descriptor";
	shaderModuleDesc.label.length = Win32_Util_StringSize(shaderModuleDesc.label.data);

	WGPUShaderSourceWGSL shaderCodeDesc = {};
	shaderCodeDesc.chain.next  = nullptr;
	shaderCodeDesc.chain.sType = WGPUSType_ShaderSourceWGSL;
	shaderCodeDesc.code.data   = static_cast<const char*>(file.content);
	shaderCodeDesc.code.length = file.contentSize;// Win32_Util_StringSize(shaderSource);

	shaderModuleDesc.nextInChain = &shaderCodeDesc.chain;
	OutShaderModule = wgpuDeviceCreateShaderModule(Device, &shaderModuleDesc);
}

void Win32_WGPU_GetRenderPipeline(WGPUDevice Device, WGPUShaderModule ShaderModule, WGPUTextureFormat SurfaceFormat, WGPURenderPipeline& OutRenderPipeline)
{
	//std::vector<WGPUVertexAttribute> VertexAttributes(2);

	WGPUVertexAttribute pointAttrib;
	pointAttrib.shaderLocation = 0;
	pointAttrib.format         = WGPUVertexFormat_Float32x2;
	pointAttrib.offset         = 0;

	WGPUVertexAttribute colorAttrib;
	colorAttrib.shaderLocation = 1;
	colorAttrib.format         = WGPUVertexFormat_Float32x3;
	colorAttrib.offset         = 2 * sizeof(float);

	WGPUVertexAttribute vertexAttributes[2] = { pointAttrib, colorAttrib };

	WGPUVertexBufferLayout vertexBufferLayout = {};
	vertexBufferLayout.attributeCount         = 2; //(uint32)VertexAttributes.size();
	vertexBufferLayout.attributes             = vertexAttributes; //VertexAttributes.data();
	vertexBufferLayout.arrayStride            = 5 * sizeof(float);
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
	colorTarget.format    = SurfaceFormat;
	colorTarget.blend     = &blendState;
	colorTarget.writeMask = WGPUColorWriteMask_All; // We could write to only some of the color channels

	WGPUFragmentState fragmentState = {};
	fragmentState.module            = ShaderModule;
	fragmentState.entryPoint.data   = "fs_main";
	fragmentState.entryPoint.length = Win32_Util_StringSize(fragmentState.entryPoint.data);
	fragmentState.constantCount     = 0;
	fragmentState.constants         = nullptr;
	fragmentState.targetCount       = 1; // We have only one target because our render pass has only one output color attachment
	fragmentState.targets           = &colorTarget;
	fragmentState.nextInChain       = nullptr;



	WGPURenderPipelineDescriptor pipelineDesc       = {};
	pipelineDesc.nextInChain                        = nullptr;
	pipelineDesc.vertex.bufferCount                 = 1;
	pipelineDesc.vertex.buffers                     = &vertexBufferLayout;
	pipelineDesc.vertex.module                      = ShaderModule;
	pipelineDesc.vertex.entryPoint.data             = "vs_main";
	pipelineDesc.vertex.entryPoint.length           = Win32_Util_StringSize(pipelineDesc.vertex.entryPoint.data);
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
	pipelineDesc.layout                             = nullptr;

	OutRenderPipeline = wgpuDeviceCreateRenderPipeline(Device, &pipelineDesc);
}


WGPUTextureView Win32_WGPU_GetNextSurfaceTextureView(WGPUSurface Surface)
{
	if (!Surface) return nullptr;

	WGPUSurfaceTexture sTexture = {};
	wgpuSurfaceGetCurrentTexture(Surface, &sTexture);

	if (sTexture.status != WGPUSurfaceGetCurrentTextureStatus_SuccessOptimal && sTexture.status != WGPUSurfaceGetCurrentTextureStatus_SuccessSuboptimal)
	{
		return nullptr;
	}

	WGPUTextureViewDescriptor viewDesc = {};
	viewDesc.nextInChain      = nullptr;
	viewDesc.label.data       = "Surface texture view";
	viewDesc.label.length     = Win32_Util_StringSize(viewDesc.label.data);
	viewDesc.format           = wgpuTextureGetFormat(sTexture.texture);
	viewDesc.dimension        = WGPUTextureViewDimension_2D;
	viewDesc.baseMipLevel     = 0;
	viewDesc.mipLevelCount    = 1;
	viewDesc.baseArrayLayer   = 0;
	viewDesc.arrayLayerCount  = 1;
	viewDesc.aspect           = WGPUTextureAspect_All;

	WGPUTextureView targetViewTexture = wgpuTextureCreateView(sTexture.texture, &viewDesc);
	wgpuTextureRelease(sTexture.texture);

	return targetViewTexture;
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

ReadFileResult Win32_Util_ReadFile(const char* Filename, GameMemory* Memory)
{
	ReadFileResult res = {};

	HANDLE fileHandle = CreateFile(Filename, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0);
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
	res.content = Win32_Util_AllocateIOMemory(Memory, fileSize32);
	if (!res.content)
	{
		res.message = "ERROR | Win32_Util_ReadFile() | Your file is too big !\n";
		return res;
	}

	DWORD bytesRead;
	if (!ReadFile(fileHandle, res.content, fileSize32, &bytesRead, 0))
	{
		res.message = "ERROR | Win32_Util_ReadFile() | Could not read the file !\n";
		Memory->IOMemory.offset -= fileSize32; // Deallocate
		return res;
	}
	if (bytesRead != fileSize32)
	{
		res.message = "ERROR | Win32_Util_ReadFile() | We did not read all of the bytes we expected !\n";
		Memory->IOMemory.offset -= fileSize32; // Deallocate
		return res;
	}

	res.contentSize = fileSize32;

	CloseHandle(fileHandle);

	return res;
}

uint32 Win32_Util_SafeTruncate_uin64(uint64 Value)
{
	ASSERT(Value <= 0xFFFFFFFF);

	uint32 res = (uint32)Value;
	return res;
}

char* Win32_Util_AllocateIOMemory(GameMemory* Memory, size_t Size)
{
	if (Memory->IOMemory.offset + Size >= Memory->IOMemory.size)
	{
		OutputDebugString("ERROR | Win32_Util_AllocateIOMemory | You asked for too much !\n");
		return nullptr;
	}

	char* ptr = Memory->IOMemory.memory + Memory->IOMemory.offset;
	Memory->IOMemory.offset += Size;

	return ptr;
}


void Win32_ProcessPendingMessages()
{
	MSG msg = {};
	while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
	{
		switch (msg.message)
		{
			case WM_QUIT:
			{
				gRunning = false;
			} break;

			case WM_SYSKEYDOWN:
			case WM_SYSKEYUP:
			case WM_KEYDOWN:
			case WM_KEYUP:
			{
				uint32 vkCode = (uint32)msg.wParam;
				if (vkCode == 'A') OutputDebugString("A KEY PRESSED !\n");
				if (vkCode == 'D') OutputDebugString("D KEY PRESSED !\n");
				if (vkCode == VK_ESCAPE) gRunning = false;
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
			gRunning = false;
		} break;

		default:
		{
			result = DefWindowProc(Window, Message, WParam, LParam);
		} break;
	}

	return result;
}

int CALLBACK WinMain(HINSTANCE Instance, HINSTANCE PrevInstance, LPSTR CmdLine, int CmdShow)
{
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

	GameMemory gameMemory      = {};
	gameMemory.size            = MEMSIZE_GAME;
	gameMemory.memory          = static_cast<char*>(VirtualAlloc(0, gameMemory.size, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE));
	gameMemory.IOMemory.size   = MEMSIZE_IO;
	gameMemory.IOMemory.memory = gameMemory.memory;



	// WGPU initialization
	//
	WGPUMaster wgpu = {};
	Win32_WGPU_GetInstance       (wgpu.instance);
	Win32_WGPU_GetAdapter        (wgpu.instance, wgpu.adapter);
	Win32_WGPU_GetDevice         (wgpu.adapter, wgpu.device);
	Win32_WGPU_GetSurface        (&wndClass, wndHandle, wgpu.instance, wgpu.surface);
	Win32_WGPU_GetSurfaceFormat  (wgpu.surface, wgpu.adapter, wgpu.surfaceFormat);
	Win32_WGPU_GetShaderModule   (wgpu.device, wgpu.shaderModule, &gameMemory);
	Win32_WGPU_GetRenderPipeline (wgpu.device, wgpu.shaderModule, wgpu.surfaceFormat, wgpu.renderPipeline);

	Win32_WGPU_ConfigureSurface(wgpu.surface, wgpu.surfaceFormat, wgpu.device, wgpu.adapter);
	wgpuAdapterRelease(wgpu.adapter);
	wgpuShaderModuleRelease(wgpu.shaderModule);

	wgpu.queue = wgpuDeviceGetQueue(wgpu.device);




	// Buffer stuff
	//
	std::vector<float> pointData =
	{
		// First triangle
		-0.5, -0.5, 1.0, 0.0, 0.0,
		+0.5, -0.5, 0.0, 1.0, 0.0,
		+0.5, +0.5, 0.0, 0.0, 1.0,
		-0.5, +0.5, 1.0, 1.0, 0.0,
	};

	std::vector<uint16> indexData =
	{
		0, 1, 2,
		0, 2, 3,
	};
	indexData.resize((indexData.size() + 1) & ~1); // round up to the next multiple of 2

	uint32 indexCount = (uint32)(indexData.size());

	WGPUBufferDescriptor bufferDesc = {};
	bufferDesc.nextInChain = nullptr;
	bufferDesc.label.data = "Point buffer";
	bufferDesc.label.length = Win32_Util_StringSize(bufferDesc.label.data);
	bufferDesc.usage = WGPUBufferUsage_CopyDst | WGPUBufferUsage_Vertex;
	bufferDesc.size = pointData.size() * sizeof(float); // round up to the next multiple of 4
	bufferDesc.mappedAtCreation = false;
	WGPUBuffer pointBuffer = wgpuDeviceCreateBuffer(wgpu.device, &bufferDesc);
	wgpuQueueWriteBuffer(wgpu.queue, pointBuffer, 0, pointData.data(), bufferDesc.size);

	bufferDesc.size = indexData.size() * sizeof(uint16);
	bufferDesc.size = (bufferDesc.size + 3) & ~3;
	bufferDesc.label.data = "Index buffer";
	bufferDesc.label.length = Win32_Util_StringSize(bufferDesc.label.data);
	bufferDesc.usage = WGPUBufferUsage_CopyDst | WGPUBufferUsage_Index;
	WGPUBuffer indexBuffer = wgpuDeviceCreateBuffer(wgpu.device, &bufferDesc);
	wgpuQueueWriteBuffer(wgpu.queue, indexBuffer, 0, indexData.data(), bufferDesc.size);


	gRunning = true;
	while (gRunning)
	{
		Win32_ProcessPendingMessages();

		WGPUTextureView targetView = Win32_WGPU_GetNextSurfaceTextureView(wgpu.surface);
		if (!targetView) return 0;


		WGPUCommandEncoderDescriptor encoderDesc = {};
		encoderDesc.nextInChain = nullptr;
		encoderDesc.label.data = "Sexy Command Encoder (SCE)";
		encoderDesc.label.length = Win32_Util_StringSize(encoderDesc.label.data);
		WGPUCommandEncoder encoder = wgpuDeviceCreateCommandEncoder(wgpu.device, &encoderDesc);


		// Describe Render Pass
		//
		WGPURenderPassColorAttachment renderPassColorAttachment = {};
		renderPassColorAttachment.view = targetView;
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

		WGPURenderPassEncoder renderPass = wgpuCommandEncoderBeginRenderPass(encoder, &renderPassDesc);

		// Use Render Pass
		//
		wgpuRenderPassEncoderSetPipeline(renderPass, wgpu.renderPipeline);
		wgpuRenderPassEncoderSetVertexBuffer(renderPass, 0, pointBuffer, 0, wgpuBufferGetSize(pointBuffer));
		wgpuRenderPassEncoderSetIndexBuffer(renderPass, indexBuffer, WGPUIndexFormat_Uint16, 0, wgpuBufferGetSize(indexBuffer));
		wgpuRenderPassEncoderDrawIndexed(renderPass, indexCount, 1, 0, 0, 0);
		wgpuRenderPassEncoderEnd(renderPass);
		wgpuRenderPassEncoderRelease(renderPass);

		WGPUCommandBufferDescriptor commandBufferDesc = {};
		commandBufferDesc.nextInChain = nullptr;
		commandBufferDesc.label.data = "Command buffer";
		commandBufferDesc.label.length = Win32_Util_StringSize(commandBufferDesc.label.data);
		WGPUCommandBuffer commandBuffer = wgpuCommandEncoderFinish(encoder, &commandBufferDesc);
		wgpuCommandEncoderRelease(encoder);

		wgpuQueueSubmit(wgpu.queue, 1, &commandBuffer);
		wgpuCommandBufferRelease(commandBuffer);


		wgpuTextureViewRelease(targetView);
		wgpuSurfacePresent(wgpu.surface);
		wgpuDeviceTick(wgpu.device);
	}

	// Once we have retrieved our adapter, we do not need the WGPUInstance anymore
	wgpuRenderPipelineRelease(wgpu.renderPipeline);
	wgpuSurfaceUnconfigure(wgpu.surface);
	wgpuQueueRelease(wgpu.queue);
	wgpuSurfaceRelease(wgpu.surface);
	wgpuDeviceRelease(wgpu.device);
	wgpuBufferRelease(pointBuffer);
	wgpuBufferRelease(indexBuffer);

	return 0;
}