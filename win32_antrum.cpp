#include "win32_antrum.h"

#include <vector>






bool gRunning = false;



WGPUShaderModule WGPU::Device::createShaderModule(WGPUShaderModuleDescriptor const* descriptor)
{
	return wgpuDeviceCreateShaderModule(device, descriptor);
}

WGPUBindGroupLayout WGPU::Device::createBindGroupLayout(WGPUBindGroupLayoutDescriptor const* descriptor)
{
	return wgpuDeviceCreateBindGroupLayout(device, descriptor);
}

WGPUPipelineLayout WGPU::Device::createPipelineLayout(WGPUPipelineLayoutDescriptor const* descriptor)
{
	return wgpuDeviceCreatePipelineLayout(device, descriptor);
}

WGPURenderPipeline WGPU::Device::createRenderPipeline(WGPURenderPipelineDescriptor const* descriptor)
{
	return wgpuDeviceCreateRenderPipeline(device, descriptor);
}

WGPUQueue WGPU::Device::getQueue()
{
	return wgpuDeviceGetQueue(device);
}

WGPUBuffer WGPU::Device::createBuffer(WGPUBufferDescriptor const* descriptor)
{
	return wgpuDeviceCreateBuffer(device, descriptor);
}

WGPUBindGroup WGPU::Device::createBindGroup(WGPUBindGroupDescriptor const* descriptor)
{
	return wgpuDeviceCreateBindGroup(device, descriptor);
}

WGPUCommandEncoder WGPU::Device::createCommandEncoder(WGPU_NULLABLE WGPUCommandEncoderDescriptor const* descriptor)
{
	return wgpuDeviceCreateCommandEncoder(device, descriptor);
}

void WGPU::Device::tick()
{
	wgpuDeviceTick(device);
}

WGPUFuture WGPU::Adapter::requestDevice(WGPU_NULLABLE WGPUDeviceDescriptor const* descriptor, WGPURequestDeviceCallbackInfo callbackInfo)
{
	return wgpuAdapterRequestDevice(adapter, descriptor, callbackInfo);
}

WGPUStatus WGPU::Adapter::getLimits(WGPULimits* limits)
{
	return wgpuAdapterGetLimits(adapter, limits);
}

void WGPU::Adapter::release()
{
	wgpuAdapterRelease(adapter);
}

WGPUFuture WGPU::Instance::requestAdapter(WGPU_NULLABLE WGPURequestAdapterOptions const* options, WGPURequestAdapterCallbackInfo callbackInfo)
{
	return wgpuInstanceRequestAdapter(instance, options, callbackInfo);
}

WGPUSurface WGPU::Instance::createSurface(WGPUSurfaceDescriptor const* descriptor)
{
	return wgpuInstanceCreateSurface(instance, descriptor);
}

WGPU::Instance WGPU::createInstance(WGPU_NULLABLE WGPUInstanceDescriptor const* descriptor)
{
	Instance wInstance = {};
	wInstance.instance = wgpuCreateInstance(descriptor);
	return wInstance;
}

WGPUStatus WGPU::Surface::getCapabilities(WGPUAdapter adapter, WGPUSurfaceCapabilities* capabilities)
{
	return wgpuSurfaceGetCapabilities(surface, adapter, capabilities);
}

void WGPU::Surface::configure(WGPUSurfaceConfiguration const* config)
{
	wgpuSurfaceConfigure(surface, config);
}

void WGPU::Surface::getCurrentTexture(WGPUSurfaceTexture* surfaceTexture)
{
	wgpuSurfaceGetCurrentTexture(surface, surfaceTexture);
}

WGPUStatus WGPU::Surface::present()
{
	return wgpuSurfacePresent(surface);
}

WGPUTextureFormat WGPU::Texture::getFormat()
{
	return wgpuTextureGetFormat(texture);
}

WGPUTextureView WGPU::Texture::createView(WGPU_NULLABLE WGPUTextureViewDescriptor const* descriptor)
{
	return wgpuTextureCreateView(texture, descriptor);
}

void WGPU::Texture::release()
{
	wgpuTextureRelease(texture);
}

void WGPU::ShaderModule::release()
{
	wgpuShaderModuleRelease(shaderModule);
}

void WGPU::Queue::writeBuffer(WGPUBuffer buffer, uint64_t bufferOffset, void const* data, size_t size)
{
	wgpuQueueWriteBuffer(queue, buffer, bufferOffset, data, size);
}

void WGPU::Queue::submit(size_t commandCount, WGPUCommandBuffer const* commands)
{
	wgpuQueueSubmit(queue, commandCount, commands);
}

WGPURenderPassEncoder WGPU::CommandEncoder::beginRenderPass(WGPURenderPassDescriptor const* descriptor)
{
	return wgpuCommandEncoderBeginRenderPass(commandEncoder, descriptor);
}

WGPUCommandBuffer WGPU::CommandEncoder::finish(WGPU_NULLABLE WGPUCommandBufferDescriptor const* descriptor)
{
	return wgpuCommandEncoderFinish(commandEncoder, descriptor);
}

void WGPU::CommandEncoder::release()
{
	wgpuCommandEncoderRelease(commandEncoder);
}

void WGPU::RenderPassEncoder::setPipeline(WGPURenderPipeline pipeline)
{
	wgpuRenderPassEncoderSetPipeline(renderPassEncoder, pipeline);
}

void WGPU::RenderPassEncoder::setVertexBuffer(uint32_t slot, WGPU_NULLABLE WGPUBuffer buffer, uint64_t offset, uint64_t size)
{
	wgpuRenderPassEncoderSetVertexBuffer(renderPassEncoder, slot, buffer, offset, size);
}

void WGPU::RenderPassEncoder::setIndexBuffer(WGPUBuffer buffer, WGPUIndexFormat format, uint64_t offset, uint64_t size)
{
	wgpuRenderPassEncoderSetIndexBuffer(renderPassEncoder, buffer, format, offset, size);
}

void WGPU::RenderPassEncoder::setBindGroup(uint32_t groupIndex, WGPU_NULLABLE WGPUBindGroup group, size_t dynamicOffsetCount, uint32_t const* dynamicOffsets)
{
	wgpuRenderPassEncoderSetBindGroup(renderPassEncoder, groupIndex, group, dynamicOffsetCount, dynamicOffsets);
}

void WGPU::RenderPassEncoder::drawIndexed(uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t baseVertex, uint32_t firstInstance)
{
	wgpuRenderPassEncoderDrawIndexed(renderPassEncoder, indexCount, instanceCount, firstIndex, baseVertex, firstInstance);
}

void WGPU::RenderPassEncoder::end()
{
	wgpuRenderPassEncoderEnd(renderPassEncoder);
}

void WGPU::RenderPassEncoder::release()
{
	wgpuRenderPassEncoderRelease(renderPassEncoder);
}



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
				res.vector.a = parsingRes.number.i;
				res.vector.a--;
			}
			else if (inputCounter == 1)
			{
				res.vector.b = parsingRes.number.i;
				res.vector.b--;
			}
			else
			{
				res.vector.c = parsingRes.number.i;
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
	WGPULimits limits = Win32_WGPU_GetDefaultLimits(Adapter);
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

WGPULimits Win32_WGPU_GetDefaultLimits(WGPUAdapter Adapter)
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

	return limits;
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
	surfaceDescNative.label.length = strlen(surfaceDescNative.label.data);
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
	shaderModuleDesc.label.length = strlen(shaderModuleDesc.label.data);

	WGPUShaderSourceWGSL shaderCodeDesc = {};
	shaderCodeDesc.chain.next  = nullptr;
	shaderCodeDesc.chain.sType = WGPUSType_ShaderSourceWGSL;
	shaderCodeDesc.code.data   = static_cast<const char*>(file.content);
	shaderCodeDesc.code.length = file.contentSize;// Win32_Util_StringSize(shaderSource);

	shaderModuleDesc.nextInChain = &shaderCodeDesc.chain;
	OutShaderModule = wgpuDeviceCreateShaderModule(Device, &shaderModuleDesc);
}

void Win32_WGPU_GetBindGroupLayout(WGPUDevice Device, WGPUBindGroupLayout& BindGroupLayout)
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
	BindGroupLayout = wgpuDeviceCreateBindGroupLayout(Device, &bindGroupLayoutDesc);
}

void Win32_WGPU_GetPipelineLayout(WGPUDevice Device, WGPUBindGroupLayout BindGroupLayout, WGPUPipelineLayout& PipelineLayout)
{
	WGPUPipelineLayoutDescriptor layoutDesc = {};
	layoutDesc.nextInChain = nullptr;
	layoutDesc.bindGroupLayoutCount = 1;
	layoutDesc.bindGroupLayouts = &BindGroupLayout;
	PipelineLayout = wgpuDeviceCreatePipelineLayout(Device, &layoutDesc);
}

void Win32_WGPU_GetRenderPipeline(WGPUDevice Device, WGPUShaderModule ShaderModule, WGPUTextureFormat SurfaceFormat, WGPUBindGroupLayout BindGroupLayout, WGPUPipelineLayout PipelineLayout, WGPURenderPipeline& OutRenderPipeline)
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
	colorTarget.format    = SurfaceFormat;
	colorTarget.blend     = &blendState;
	colorTarget.writeMask = WGPUColorWriteMask_All; // We could write to only some of the color channels

	WGPUFragmentState fragmentState = {};
	fragmentState.module            = ShaderModule;
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
	pipelineDesc.vertex.module                      = ShaderModule;
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
	pipelineDesc.layout                             = PipelineLayout;

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
	viewDesc.label.length     = strlen(viewDesc.label.data);
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
		OutputDebugString(buffer);
		int toto = 1;
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
	ReadFileResult res = Win32_Util_ReadFile(Filename, Memory);

	OutputDebugString("--------------------------\n");
	OutputDebugString(static_cast<const char*>(res.content));
	OutputDebugString("--------------------------\n");

	OBJParser::OBJFileResult fileRes = {};

	Vec3 vec = {};
	Vec3I indexes = {};
	const char* reader = (const char*)res.content;
	FileReader fileReader = {};
	fileReader.reader = (const char*)res.content;
	char* floatPointer = nullptr;
	size_t tPointer = 0;
	
	OBJParser::Vec3LineResult lineRes = {};
	OBJParser::Vec3ILineResult lineResFaces = {};
	size_t counter = 0;

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

	int a = 2;

	return asset;
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
	res.content = Win32_Util_AllocateReadFileMemory(Memory, fileSize32);
	if (!res.content)
	{
		res.message = "ERROR | Win32_Util_ReadFile() | Your file is too big !\n";
		return res;
	}

	DWORD bytesRead;
	if (!ReadFile(fileHandle, res.content, fileSize32, &bytesRead, 0))
	{
		res.message = "ERROR | Win32_Util_ReadFile() | Could not read the file !\n";
		Memory->readFileChunk.offset -= fileSize32; // Deallocate
		return res;
	}
	if (bytesRead != fileSize32)
	{
		res.message = "ERROR | Win32_Util_ReadFile() | We did not read all of the bytes we expected !\n";
		Memory->readFileChunk.offset -= fileSize32; // Deallocate
		return res;
	}

	res.contentSize = fileSize32;

	// Deallocate
	//Memory->ReadFileMemory.offset = 0;
	//Memory->ReadFileMemory.memory = nullptr;

	CloseHandle(fileHandle);

	return res;
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

	GameMemory gameMemory           = {};
	gameMemory.fattyChunk.size      = MEMSIZE_GAME;
	gameMemory.fattyChunk.memory    = static_cast<char*>(VirtualAlloc(0, gameMemory.fattyChunk.size, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE));
	gameMemory.readFileChunk.size   = MEMSIZE_READ_FILE;
	gameMemory.readFileChunk.memory = gameMemory.fattyChunk.memory;
	gameMemory.assetsChunk.size     = MEMSIZE_ASSETS;
	gameMemory.assetsChunk.memory   = gameMemory.readFileChunk.memory + gameMemory.readFileChunk.size;


	const char* testReal32 = "-1.04560";
	Win32_Util_ConvertStringToFloat(testReal32, Win32_Util_StringSize(testReal32));



	AssetManager assetManager = {};

	MeshAsset asset = Win32_Util_ReadFile_OBJ("../resource/TestOBJ.obj", &gameMemory);
	


	// WGPU initialization
	//
	WGPUMaster wgpu = {};
	Win32_WGPU_GetInstance        (wgpu.instance);
	Win32_WGPU_GetAdapter         (wgpu.instance, wgpu.adapter);
	Win32_WGPU_GetDevice          (wgpu.adapter, wgpu.device);
	Win32_WGPU_GetSurface         (&wndClass, wndHandle, wgpu.instance, wgpu.surface);
	Win32_WGPU_GetSurfaceFormat   (wgpu.surface, wgpu.adapter, wgpu.surfaceFormat);
	Win32_WGPU_GetShaderModule    (wgpu.device, wgpu.shaderModule, &gameMemory);
	Win32_WGPU_GetBindGroupLayout (wgpu.device, wgpu.bindGroupLayout);
	Win32_WGPU_GetPipelineLayout  (wgpu.device, wgpu.bindGroupLayout, wgpu.pipelineLayout);
	Win32_WGPU_GetRenderPipeline  (wgpu.device, wgpu.shaderModule, wgpu.surfaceFormat, wgpu.bindGroupLayout, wgpu.pipelineLayout, wgpu.renderPipeline);

	Win32_WGPU_ConfigureSurface(wgpu.surface, wgpu.surfaceFormat, wgpu.device, wgpu.adapter);
	wgpuAdapterRelease(wgpu.adapter);
	wgpuShaderModuleRelease(wgpu.shaderModule);

	wgpu.queue = wgpuDeviceGetQueue(wgpu.device);


	// Buffer stuff
	//
	std::vector<real32> pointData =
	{
		// First triangle
		//-0.2f, -0.2f, 1.0f, 0.0f, 0.0f,
		//+0.2f, -0.2f, 0.0f, 1.0f, 0.0f,
		//+0.2f, +0.2f, 0.0f, 0.0f, 1.0f,
		//p1.x, p1.y, p1.z, 0.7f, 1.0f, 0.3f, 
		//p2.x, p2.y, p2.z, 1.0f, 0.5f, 1.0f,  
		//p3.x, p3.y, p3.z, 1.0f, 0.2f, 1.0f,  
		//p4.x, p4.y, p4.z, 1.0f, 1.0f, 1.0f,  

		//asset.vertices.at(0), asset.vertices.at(1) , asset.vertices.at(2) , 0.7f, 1.0f, 1.0f,
		//asset.vertices.at(3), asset.vertices.at(4) , asset.vertices.at(5) , 1.0f, 0.5f, 1.0f,
		//asset.vertices.at(6), asset.vertices.at(7) , asset.vertices.at(8) , 1.0f, 0.2f, 1.0f,
		//asset.vertices.at(9), asset.vertices.at(10), asset.vertices.at(11), 1.0f, 1.0f, 1.0f,

		asset.vertices.at(0), asset.vertices.at(1) , asset.vertices.at(2) , //0.7f, 1.0f, 1.0f,
		asset.vertices.at(3), asset.vertices.at(4) , asset.vertices.at(5) , //1.0f, 0.5f, 1.0f,
		asset.vertices.at(6), asset.vertices.at(7) , asset.vertices.at(8) , //1.0f, 0.2f, 1.0f,
		asset.vertices.at(9), asset.vertices.at(10), asset.vertices.at(11), //1.0f, 1.0f, 1.0f,

		//-0.2f, +0.2f, 1.0f, 1.0f, 0.0f,
	};

	//std::vector<uint16> indexData =
	//{
	//	//0, 1, 2,
	//	//1, 2, 3,
	//	//i1.a, i1.b, i1.c, 
	//	//i2.a, i2.b, i2.c,
	//
	//	asset.indexes.at(0), asset.indexes.at(1), asset.indexes.at(2),
	//	asset.indexes.at(3), asset.indexes.at(4), asset.indexes.at(5),
	//};
	//indexData.resize((indexData.size() + 1) & ~1); // round up to the next multiple of 2

	//uint32 indexCount = (uint32)(indexData.size());


	ShaderUniform shaderUniform = {};
	shaderUniform.time = 2.0f;
	shaderUniform.color[0] = 0.0f;
	shaderUniform.color[1] = 1.0f;
	shaderUniform.color[2] = 0.0f;
	shaderUniform.color[3] = 1.0f;



	WGPUBufferDescriptor bufferDesc = {};
	bufferDesc.nextInChain = nullptr;
	bufferDesc.label.data = "Point buffer";
	bufferDesc.label.length = strlen(bufferDesc.label.data);
	bufferDesc.usage = WGPUBufferUsage_CopyDst | WGPUBufferUsage_Vertex;
	//bufferDesc.size = pointData.size() * sizeof(real32); // round up to the next multiple of 4
	bufferDesc.size = asset.vertices.getElementsSize();
	bufferDesc.size = (bufferDesc.size + 3) & ~3;
	bufferDesc.mappedAtCreation = false;
	WGPUBuffer pointBuffer = wgpuDeviceCreateBuffer(wgpu.device, &bufferDesc);
	//wgpuQueueWriteBuffer(wgpu.queue, pointBuffer, 0, pointData.data(), bufferDesc.size);
	wgpuQueueWriteBuffer(wgpu.queue, pointBuffer, 0, asset.vertices.dataPtr(), bufferDesc.size);

	//bufferDesc.size = indexData.size() * sizeof(uint16);
	bufferDesc.size = asset.indexes.getElementsSize();
	bufferDesc.size = (bufferDesc.size + 3) & ~3; // From right to left, dummy
	bufferDesc.label.data = "Index buffer";
	bufferDesc.label.length = strlen(bufferDesc.label.data);
	bufferDesc.usage = WGPUBufferUsage_CopyDst | WGPUBufferUsage_Index;
	bufferDesc.mappedAtCreation = false;
	WGPUBuffer indexBuffer = wgpuDeviceCreateBuffer(wgpu.device, &bufferDesc);
	//wgpuQueueWriteBuffer(wgpu.queue, indexBuffer, 0, indexData.data(), bufferDesc.size);
	wgpuQueueWriteBuffer(wgpu.queue, indexBuffer, 0, asset.indexes.dataPtr(), bufferDesc.size);

	WGPULimits supportedLimits = Win32_WGPU_GetDefaultLimits(wgpu.adapter);
	uint32 uniformBufferStride = Win32_WGPU_Util_CeilToNextMultiple((uint32)sizeof(ShaderUniform), (uint32)supportedLimits.minUniformBufferOffsetAlignment);
	bufferDesc.size = uniformBufferStride + sizeof(ShaderUniform);
	bufferDesc.label.data = "Uniform buffer";
	bufferDesc.label.length = strlen(bufferDesc.label.data);
	bufferDesc.usage = WGPUBufferUsage_CopyDst | WGPUBufferUsage_Uniform;
	bufferDesc.mappedAtCreation = false;
	WGPUBuffer uniformBuffer = wgpuDeviceCreateBuffer(wgpu.device, &bufferDesc);
	wgpuQueueWriteBuffer(wgpu.queue, uniformBuffer, 0, &shaderUniform, sizeof(ShaderUniform));
	
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
	binding.buffer = uniformBuffer; // The buffer it is bound to
	binding.offset = 0; // A buffer can contain multiple uniforms
	binding.size = sizeof(ShaderUniform); // i.e. the size of the buffer
	WGPUBindGroupDescriptor bindGroupDesc = {};
	bindGroupDesc.nextInChain = nullptr;
	bindGroupDesc.layout = wgpu.bindGroupLayout;
	bindGroupDesc.entryCount = 1;
	bindGroupDesc.entries = &binding;
	wgpu.bindGroup = wgpuDeviceCreateBindGroup(wgpu.device, &bindGroupDesc);


	real32 fakeTime = 1.0f;

	gRunning = true;
	while (gRunning)
	{
		Win32_ProcessPendingMessages();

		//fakeTime += 0.02f;
		//shaderUniform.time = fakeTime;
		//wgpuQueueWriteBuffer(wgpu.queue, uniformBuffer, offsetof(ShaderUniform, ShaderUniform::time), &shaderUniform.time, sizeof(real32));

		//shaderUniform.color[1] = (real32)sin(fakeTime);
		wgpuQueueWriteBuffer(wgpu.queue, uniformBuffer, offsetof(ShaderUniform, ShaderUniform::color), &shaderUniform.color, sizeof(ShaderUniform::color));
		//wgpuQueueWriteBuffer(wgpu.queue, uniformBuffer, sizeof(real32) * 2, &shaderUniform.color[1], sizeof(real32));


		WGPUTextureView targetView = Win32_WGPU_GetNextSurfaceTextureView(wgpu.surface);
		if (!targetView) return 0;


		WGPUCommandEncoderDescriptor encoderDesc = {};
		encoderDesc.nextInChain = nullptr;
		encoderDesc.label.data = "Sexy Command Encoder (SCE)";
		encoderDesc.label.length = strlen(encoderDesc.label.data);
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
		uint32 dynamicOffset = 0;
		dynamicOffset = 0 * uniformBufferStride;
		wgpuRenderPassEncoderSetPipeline(renderPass, wgpu.renderPipeline);
		wgpuRenderPassEncoderSetVertexBuffer(renderPass, 0, pointBuffer, 0, wgpuBufferGetSize(pointBuffer));
		wgpuRenderPassEncoderSetIndexBuffer(renderPass, indexBuffer, WGPUIndexFormat_Uint16, 0, wgpuBufferGetSize(indexBuffer));
		wgpuRenderPassEncoderSetBindGroup(renderPass, 0, wgpu.bindGroup, 1, &dynamicOffset);
		//wgpuRenderPassEncoderDrawIndexed(renderPass, indexCount, 1, 0, 0, 0);
		wgpuRenderPassEncoderDrawIndexed(renderPass, (uint32)(asset.indexes.getElementsLength()), 1, 0, 0, 0);
		//dynamicOffset = 1 * uniformBufferStride;
		//wgpuRenderPassEncoderSetBindGroup(renderPass, 0, wgpu.bindGroup, 1, &dynamicOffset);
		//wgpuRenderPassEncoderDrawIndexed(renderPass, indexCount, 1, 0, 0, 0);
		wgpuRenderPassEncoderEnd(renderPass);
		wgpuRenderPassEncoderRelease(renderPass);

		WGPUCommandBufferDescriptor commandBufferDesc = {};
		commandBufferDesc.nextInChain = nullptr;
		commandBufferDesc.label.data = "Command buffer";
		commandBufferDesc.label.length = strlen(commandBufferDesc.label.data);
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
	wgpuPipelineLayoutRelease(wgpu.pipelineLayout);
	wgpuBindGroupRelease(wgpu.bindGroup);
	wgpuBindGroupLayoutRelease(wgpu.bindGroupLayout);
	wgpuBufferRelease(pointBuffer);
	wgpuBufferRelease(indexBuffer);
	wgpuBufferRelease(uniformBuffer);

	return 0;
}