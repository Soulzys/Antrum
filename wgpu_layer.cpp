#include "wgpu_layer.h"
#include "string.h"


// ***** HELPER METHODS
//
wgpu::Instance wgpu::helper::createInstance()
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
		//OutputDebugString("ERROR | wgpu::helper::createInstance() | Coud not initialize WebGPU !\n");
	}

	return instance;
}

WGPUAdapter wgpu::helper::requestAdapterAsync(wgpu::Instance instance, WGPURequestAdapterOptions const* options)
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
				//OutputDebugString("ERROR | wgpu::helper::requestAdapterAsync | Coud not get WebGPU adapter :((\n");
			}

			data.requestEnded = true;
		};


	instance.requestAdapter(options, callbackInfo);
	AdapterRequestData& requestDataResult = *reinterpret_cast<AdapterRequestData*>(callbackInfo.userdata1);
	ASSERT(requestDataResult.requestEnded);

	return requestDataResult.adapter;
}

wgpu::Adapter wgpu::helper::createAdapter(wgpu::Instance instance)
{
	WGPURequestAdapterOptions adapterOptions = {};
	adapterOptions.nextInChain = nullptr;

	wgpu::Adapter adapter = {};
	adapter.object = requestAdapterAsync(instance, &adapterOptions);

	return adapter;
}

WGPUDevice wgpu::helper::requestDeviceAsync(wgpu::Adapter adapter, const WGPUDeviceDescriptor* descriptor)
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
			//OutputDebugString("ERROR | Could not get WebGPU device :((\n");
		}

		data.requestEnded = true;
	};

	adapter.requestDevice(descriptor, callbackInfo);
	DeviceRequestData& requestDataResult = *reinterpret_cast<DeviceRequestData*>(callbackInfo.userdata1);
	ASSERT(requestDataResult.requestEnded);

	return requestDataResult.device;
}

wgpu::Device wgpu::helper::createDevice(wgpu::Adapter adapter, flog* log)
{
	// GPU Features
	//
	WGPULimits limits = adapter.getDefaultLimits();
	limits.maxVertexAttributes             = 2;
	limits.maxVertexBuffers                = 1;
	limits.maxBufferSize                   = 6 * 6 * sizeof(real32);
	limits.maxVertexBufferArrayStride      = 6 * sizeof(real32);
	limits.maxInterStageShaderVariables    = 3;
	limits.maxBindGroups                   = 1;
	limits.maxUniformBuffersPerShaderStage = 1;
	limits.maxUniformBufferBindingSize     = 16 * 4 * sizeof(real32);
	limits.maxDynamicUniformBuffersPerPipelineLayout = 1;
	limits.maxTextureDimension1D = WINDOW_HEIGHT;
	limits.maxTextureDimension2D = WINDOW_WIDTH;
	limits.maxTextureArrayLayers = 1;


	// Requesting a device
	//
	WGPUDeviceDescriptor deviceDesc        = {};
	deviceDesc.nextInChain                 = nullptr;
	deviceDesc.label.data                  = "Device-san";
	deviceDesc.label.length                = strlen(deviceDesc.label.data);
	deviceDesc.requiredFeatureCount        = 0;
	deviceDesc.requiredLimits              = &limits;
	deviceDesc.deviceLostCallbackInfo      = wgpu::callback::onDeviceLost(log);
	deviceDesc.uncapturedErrorCallbackInfo = wgpu::callback::onUncapturedError(log);
	deviceDesc.defaultQueue.nextInChain    = nullptr;
	deviceDesc.defaultQueue.label.data     = "Default Queue-san";
	deviceDesc.defaultQueue.label.length   = strlen(deviceDesc.defaultQueue.label.data);

	wgpu::Device device = {};
	device.object = requestDeviceAsync(adapter, &deviceDesc);

	return device;
}

WGPUDeviceLostCallbackInfo wgpu::callback::onDeviceLost(flog* log)
{
	WGPUDeviceLostCallbackInfo callbackInfo = {};
	callbackInfo.nextInChain = nullptr;
	callbackInfo.mode = WGPUCallbackMode_AllowSpontaneous;
	callbackInfo.userdata1 = log;
	callbackInfo.callback = [](WGPUDevice const* device, WGPUDeviceLostReason reason, WGPUStringView message, WGPU_NULLABLE void* ud1, WGPU_NULLABLE void* ud2)
	{
		flog* log = (flog*)ud1;

		char buffer[KILOBYTES(2)];
		if (message.length >= sizeof(buffer))
		{
			log("ERROR | DeviceLostCallback | Could not print out the message as the buffer is too small !\n");
			return;
		}
		
		// From what I remember, the WGPUStringView::data is not null-terminated
		// It may be useful to double check though
		strcpy(buffer, message.data);
		buffer[message.length - 1] = '\0';


		log("ERROR | DeviceLost callback ~~~~~\n");
		log("Reason: ");
		log(wgpu::stringifier::deviceLostReason(reason));
		log("\n");
		log("Message: ");
		log(buffer);
	};

	return callbackInfo;
}

const char* wgpu::stringifier::deviceLostReason(WGPUDeviceLostReason e)
{
	switch (e)
	{
		case WGPUDeviceLostReason_Unknown           : return "Unknown";
		case WGPUDeviceLostReason_Destroyed         : return "Destroyed";
		case WGPUDeviceLostReason_CallbackCancelled : return "CallbackCancelled";
		case WGPUDeviceLostReason_FailedCreation    : return "FailedCreation";
		case WGPUDeviceLostReason_Force32           : return "Force32";
		default                                     : return "Could not retrieve a valid Reason :((";
	}
}

const char* wgpu::stringifier::errorType(WGPUErrorType e)
{
	switch (e)
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

WGPUUncapturedErrorCallbackInfo wgpu::callback::onUncapturedError(flog* log)
{
	WGPUUncapturedErrorCallbackInfo callbackInfo = {};
	callbackInfo.nextInChain = {};
	callbackInfo.userdata1 = log;
	callbackInfo.callback = [](WGPUDevice const* device, WGPUErrorType type, WGPUStringView message, WGPU_NULLABLE void* ud1, WGPU_NULLABLE void* ud2)
		{
			flog* log = (flog*)ud1;

			char buffer[KILOBYTES(2)];
			if (message.length >= sizeof(buffer))
			{
				log("ERROR | UncapturedErrorCallback | Could not print out the Message as the buffer is too small !\n");
				return;
			}

			// From what I remember, the WGPUStringView::data is not null-terminated
			// It may be useful to double check though
			strcpy(buffer, message.data);
			buffer[message.length - 1] = '\0';


			log("ERROR | UncapturedError callback ~~~~~\n");
			log("Error type: ");
			log(wgpu::stringifier::errorType(type));
			log("\n");
			log("\tMessage: ");
			log(buffer);
			log("\n\n");
		};

	return callbackInfo;
}

wgpu::Surface wgpu::helper::createSurface(void* wndHandle, void* hInstance, wgpu::Instance instance)
{
	WGPUSurfaceSourceWindowsHWND surfaceWindow = {};
	surfaceWindow.hinstance   = hInstance;
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

wgpu::ShaderModule wgpu::helper::createShaderModule(wgpu::Device device, WGPUStringView shaderData, const char* label)
{
	WGPUShaderModuleDescriptor shaderModuleDesc = {};
	shaderModuleDesc.label.data = label;
	shaderModuleDesc.label.length = strlen(label);

	WGPUShaderSourceWGSL shaderCodeDesc = {};
	shaderCodeDesc.chain.next = nullptr;
	shaderCodeDesc.chain.sType = WGPUSType_ShaderSourceWGSL;
	shaderCodeDesc.code = shaderData;
	//shaderCodeDesc.code.data = static_cast<const char*>(file.content);
	//shaderCodeDesc.code.length = file.contentSize;

	shaderModuleDesc.nextInChain = &shaderCodeDesc.chain;

	wgpu::ShaderModule shaderModule = {};
	shaderModule.object = device.createShaderModule(&shaderModuleDesc);

	return shaderModule;
}

void wgpu::helper::setDefault(WGPUBindGroupLayoutEntry& bindingLayout)
{
	bindingLayout.buffer.nextInChain = nullptr;
	bindingLayout.buffer.type = WGPUBufferBindingType_Undefined;
	bindingLayout.buffer.hasDynamicOffset = false;

	bindingLayout.sampler.nextInChain = nullptr;
	bindingLayout.sampler.type = WGPUSamplerBindingType_BindingNotUsed;

	bindingLayout.storageTexture.nextInChain = nullptr;
	bindingLayout.storageTexture.access = WGPUStorageTextureAccess_BindingNotUsed;
	bindingLayout.storageTexture.format = WGPUTextureFormat_Undefined;
	bindingLayout.storageTexture.viewDimension = WGPUTextureViewDimension_Undefined;

	bindingLayout.texture.nextInChain = nullptr;
	bindingLayout.texture.multisampled = false;
	bindingLayout.texture.sampleType = WGPUTextureSampleType_BindingNotUsed;
	bindingLayout.texture.viewDimension = WGPUTextureViewDimension_Undefined;
}

void wgpu::helper::setDefault(WGPUStencilFaceState& stencilFaceState)
{
	stencilFaceState.compare     = WGPUCompareFunction_Always;
	stencilFaceState.failOp      = WGPUStencilOperation_Keep;
	stencilFaceState.depthFailOp = WGPUStencilOperation_Keep;
	stencilFaceState.passOp      = WGPUStencilOperation_Keep;
}

void wgpu::helper::setDefault(WGPUDepthStencilState& depthStencilState)
{
	depthStencilState.format              = WGPUTextureFormat_Undefined;
	depthStencilState.depthWriteEnabled   = WGPUOptionalBool_False;
	depthStencilState.depthCompare        = WGPUCompareFunction_Always;
	depthStencilState.stencilReadMask     = 0xFFFFFFFF;
	depthStencilState.stencilWriteMask    = 0xFFFFFFFF;
	depthStencilState.depthBias           = 0;
	depthStencilState.depthBiasSlopeScale = 0;
	depthStencilState.depthBiasClamp      = 0;
	wgpu::helper::setDefault(depthStencilState.stencilFront);
	wgpu::helper::setDefault(depthStencilState.stencilBack);
}

wgpu::BindGroupLayout wgpu::helper::createBindGroupLayout(wgpu::Device device, uint64_t minBindingSize)
{
	// Create a bind group
	//
	WGPUBindGroupLayoutEntry bindingLayoutEntry = {};
	wgpu::helper::setDefault(bindingLayoutEntry); // Setting every other unused fields to default values unsure we only use what we want
	bindingLayoutEntry.binding     = 0; // This is the binding index we use in our shader
	bindingLayoutEntry.visibility  = WGPUShaderStage_Vertex | WGPUShaderStage_Fragment; // This is the stage that needs to access this resource
	bindingLayoutEntry.buffer.type = WGPUBufferBindingType_Uniform;
	bindingLayoutEntry.buffer.minBindingSize = minBindingSize;
	bindingLayoutEntry.buffer.hasDynamicOffset = true;

	WGPUBindGroupLayoutDescriptor bindGroupLayoutDesc = {};
	bindGroupLayoutDesc.nextInChain = nullptr;
	bindGroupLayoutDesc.entryCount = 1;
	bindGroupLayoutDesc.entries = &bindingLayoutEntry;

	wgpu::BindGroupLayout bindGroupLayout = {};
	bindGroupLayout.object = device.createBindGroupLayout(&bindGroupLayoutDesc);

	return bindGroupLayout;
}

wgpu::PipelineLayout wgpu::helper::createPipelineLayout(wgpu::Device device, wgpu::BindGroupLayout bindGroupLayout)
{
	WGPUPipelineLayoutDescriptor layoutDesc = {};
	layoutDesc.nextInChain          = nullptr;
	layoutDesc.bindGroupLayoutCount = 1;
	layoutDesc.bindGroupLayouts     = &bindGroupLayout.object;

	wgpu::PipelineLayout pipelineLayout = {};
	pipelineLayout.object = device.createPipelineLayout(&layoutDesc);

	return pipelineLayout;
}

wgpu::RenderPipeline wgpu::helper::createRenderPipeline(wgpu::Device device, wgpu::ShaderModule shaderModule, WGPUTextureFormat textureFormat, wgpu::PipelineLayout pipelineLayout)
{
	//std::vector<WGPUVertexAttribute> VertexAttributes(2);

	WGPUVertexAttribute pointAttrib;
	pointAttrib.shaderLocation = 0;
	pointAttrib.format = WGPUVertexFormat_Float32x3;
	pointAttrib.offset = 0;

	WGPUVertexAttribute colorAttrib;
	colorAttrib.shaderLocation = 1;
	colorAttrib.format = WGPUVertexFormat_Float32x3;
	colorAttrib.offset = 3 * sizeof(real32);

	WGPUVertexAttribute vertexAttributes[2] = { pointAttrib, colorAttrib };

	WGPUVertexBufferLayout vertexBufferLayout = {};
	vertexBufferLayout.attributeCount = 1; //(uint32)VertexAttributes.size();
	//vertexBufferLayout.attributes             = vertexAttributes; //VertexAttributes.data();
	vertexBufferLayout.attributes = &pointAttrib; //VertexAttributes.data();
	vertexBufferLayout.arrayStride = 3 * sizeof(real32);
	vertexBufferLayout.stepMode = WGPUVertexStepMode_Vertex;



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
	colorTarget.format = textureFormat;
	colorTarget.blend = &blendState;
	colorTarget.writeMask = WGPUColorWriteMask_All; // We could write to only some of the color channels

	WGPUFragmentState fragmentState = {};
	fragmentState.module = shaderModule.object;
	fragmentState.entryPoint.data = "fs_main";
	fragmentState.entryPoint.length = strlen(fragmentState.entryPoint.data);
	fragmentState.constantCount = 0;
	fragmentState.constants = nullptr;
	fragmentState.targetCount = 1; // We have only one target because our render pass has only one output color attachment
	fragmentState.targets = &colorTarget;
	fragmentState.nextInChain = nullptr;



	WGPUTextureFormat depthTextureFormat = WGPUTextureFormat_Depth24Plus;
	WGPUDepthStencilState depthStencilState = {};
	wgpu::helper::setDefault(depthStencilState);
	depthStencilState.depthCompare = WGPUCompareFunction_Less;
	depthStencilState.depthWriteEnabled = WGPUOptionalBool_False;
	depthStencilState.format = depthTextureFormat;
	depthStencilState.stencilReadMask = 0;
	depthStencilState.stencilWriteMask = 0;


	WGPURenderPipelineDescriptor pipelineDesc = {};
	pipelineDesc.nextInChain = nullptr;
	pipelineDesc.vertex.bufferCount = 1;
	pipelineDesc.vertex.buffers = &vertexBufferLayout;
	pipelineDesc.vertex.module = shaderModule.object;
	pipelineDesc.vertex.entryPoint.data = "vs_main";
	pipelineDesc.vertex.entryPoint.length = strlen(pipelineDesc.vertex.entryPoint.data);
	pipelineDesc.vertex.constantCount = 0;
	pipelineDesc.vertex.constants = nullptr;
	pipelineDesc.vertex.nextInChain = nullptr;
	pipelineDesc.primitive.topology = WGPUPrimitiveTopology_TriangleList;
	pipelineDesc.primitive.stripIndexFormat = WGPUIndexFormat_Undefined;
	pipelineDesc.primitive.frontFace = WGPUFrontFace_CCW;
	// >NOTASCOI: Based on the face orientation. Should eventually set it to 'front'. None is only for debug, so we see everything, nothing is hidden.
	pipelineDesc.primitive.cullMode = WGPUCullMode_None;
	pipelineDesc.fragment = &fragmentState;
	pipelineDesc.depthStencil = &depthStencilState;
	pipelineDesc.multisample.count = 1;
	pipelineDesc.multisample.mask = ~0u; // Default value for the mask. It means "all bits on"
	pipelineDesc.multisample.alphaToCoverageEnabled = false; // Default value as well. It is irrelevant for count = 1 anyways
	pipelineDesc.layout = pipelineLayout.object;

	wgpu::RenderPipeline renderPipeline = {};
	renderPipeline.object = device.createRenderPipeline(&pipelineDesc);

	return renderPipeline;
}



// ***** DEVICE METHODS
//
WGPUBindGroup 
wgpu::Device::createBindGroup
(WGPUBindGroupDescriptor const* descriptor) { return wgpuDeviceCreateBindGroup(object, descriptor); }

WGPU_XIN_EXTRA
wgpu::BindGroup 
wgpu::Device::createBindGroupHelper
(WGPUBindGroupDescriptor const* descriptor) 
{
	wgpu::BindGroup bindGroup = {};
	bindGroup.object = createBindGroup(descriptor);
	return bindGroup;
}

WGPUBindGroupLayout
wgpu::Device::createBindGroupLayout
(WGPUBindGroupLayoutDescriptor const* descriptor) {	return wgpuDeviceCreateBindGroupLayout(object, descriptor); }

WGPUBuffer 
wgpu::Device::createBuffer
(WGPUBufferDescriptor const* descriptor) { return wgpuDeviceCreateBuffer(object, descriptor); }

WGPU_XIN_EXTRA
wgpu::Buffer
wgpu::Device::createBufferHelper
(WGPUBufferDescriptor const* descriptor) 
{
	wgpu::Buffer buffer = {};
	buffer.object = createBuffer(descriptor);
	return buffer;
}

WGPUCommandEncoder 
wgpu::Device::createCommandEncoder
(WGPU_NULLABLE WGPUCommandEncoderDescriptor const* descriptor) { return wgpuDeviceCreateCommandEncoder(object, descriptor); }

WGPU_XIN_EXTRA
wgpu::CommandEncoder 
wgpu::Device::createCommandEncoderHelper
(WGPU_NULLABLE WGPUCommandEncoderDescriptor const* descriptor) 
{
	wgpu::CommandEncoder encoder = {};
	encoder.object = createCommandEncoder(descriptor);
	return encoder;
}

WGPUComputePipeline
wgpu::Device::createComputePipeline
(WGPUComputePipelineDescriptor const* descriptor) { return wgpuDeviceCreateComputePipeline(object, descriptor); }

WGPUFuture
wgpu::Device::createComputePipelineAsync
(WGPUComputePipelineDescriptor const* descriptor, WGPUCreateComputePipelineAsyncCallbackInfo callbackInfo) { return wgpuDeviceCreateComputePipelineAsync(object, descriptor, callbackInfo); }

WGPUBuffer
wgpu::Device::createErrorBuffer
(WGPUBufferDescriptor const* descriptor) { return wgpuDeviceCreateErrorBuffer(object, descriptor); }

WGPUExternalTexture
wgpu::Device::createErrorExternalTexture
() { return wgpuDeviceCreateErrorExternalTexture(object); }

WGPUShaderModule
wgpu::Device::createErrorShaderModule
(WGPUShaderModuleDescriptor const* descriptor, WGPUStringView errorMessage) { return wgpuDeviceCreateErrorShaderModule(object, descriptor, errorMessage); }

WGPUTexture
wgpu::Device::createErrorTexture
(WGPUTextureDescriptor const* descriptor) { return wgpuDeviceCreateErrorTexture(object, descriptor); }

WGPUExternalTexture
wgpu::Device::createExternalTexture
(WGPUExternalTextureDescriptor const* externalTextureDescriptor) { return wgpuDeviceCreateExternalTexture(object, externalTextureDescriptor); }

WGPUPipelineLayout
wgpu::Device::createPipelineLayout
(WGPUPipelineLayoutDescriptor const* descriptor) { return wgpuDeviceCreatePipelineLayout(object, descriptor); }

WGPUQuerySet
wgpu::Device::createQuerySet
(WGPUQuerySetDescriptor const* descriptor) { return wgpuDeviceCreateQuerySet(object, descriptor); }

WGPURenderBundleEncoder
wgpu::Device::createRenderBundleEncoder
(WGPURenderBundleEncoderDescriptor const* descriptor) { return wgpuDeviceCreateRenderBundleEncoder(object, descriptor); }

WGPURenderPipeline
wgpu::Device::createRenderPipeline
(WGPURenderPipelineDescriptor const* descriptor) { return wgpuDeviceCreateRenderPipeline(object, descriptor); }

WGPUFuture
wgpu::Device::createRenderPipelineAsync
(WGPURenderPipelineDescriptor const* descriptor, WGPUCreateRenderPipelineAsyncCallbackInfo callbackInfo) { return wgpuDeviceCreateRenderPipelineAsync(object, descriptor, callbackInfo); }

WGPUResourceTable
wgpu::Device::createResourceTable
(WGPUResourceTableDescriptor const* descriptor) { return wgpuDeviceCreateResourceTable(object, descriptor); }

WGPUSampler
wgpu::Device::createSampler
(WGPU_NULLABLE WGPUSamplerDescriptor const* descriptor) { return wgpuDeviceCreateSampler(object, descriptor); }

WGPUShaderModule
wgpu::Device::createShaderModule
(WGPUShaderModuleDescriptor const* descriptor) { return wgpuDeviceCreateShaderModule(object, descriptor); }

WGPUTexture
wgpu::Device::createTexture
(WGPUTextureDescriptor const* descriptor) { return wgpuDeviceCreateTexture(object, descriptor); }

wgpu::Texture
wgpu::Device::createTextureHelper
(WGPUTextureDescriptor const* descriptor)
{
	wgpu::Texture texture = {};
	texture.object = createTexture(descriptor);
	return texture;
}

void 
wgpu::Device::destroy
() { wgpuDeviceDestroy(object); }

void
wgpu::Device::forceLoss
(WGPUDeviceLostReason type, WGPUStringView message) { wgpuDeviceForceLoss(object, type, message); }

WGPUAdapter
wgpu::Device::getAdapter
() { return wgpuDeviceGetAdapter(object); }

WGPUStatus
wgpu::Device::getAdapterInfo
(WGPUAdapterInfo* adapterInfo) { return wgpuDeviceGetAdapterInfo(object, adapterInfo); }

WGPUStatus
wgpu::Device::getAHardwareBufferProperties
(void* handle, WGPUAHardwareBufferProperties* properties) { return wgpuDeviceGetAHardwareBufferProperties(object, handle, properties); }

void 
wgpu::Device::getFeatures
(WGPUSupportedFeatures* features) { return wgpuDeviceGetFeatures(object, features); }

WGPUStatus
wgpu::Device::getLimits
(WGPULimits* limits) { return wgpuDeviceGetLimits(object, limits); }

WGPUFuture
wgpu::Device::getLostFuture
() { return wgpuDeviceGetLostFuture(object); }

WGPUQueue 
wgpu::Device::getQueue
() { return wgpuDeviceGetQueue(object); }

WGPU_XIN_EXTRA
wgpu::Queue
wgpu::Device::getQueueHelper() 
{
	wgpu::Queue queue = {};
	queue.object = getQueue();
	return queue;
}

WGPUBool
wgpu::Device::hasFeature
(WGPUFeatureName feature) { return wgpuDeviceHasFeature(object, feature); }

WGPUSharedBufferMemory
wgpu::Device::importShaderBufferMemory
(WGPUSharedBufferMemoryDescriptor const* descriptor) { return wgpuDeviceImportSharedBufferMemory(object, descriptor); }

WGPUSharedFence
wgpu::Device::importSharedFence
(WGPUSharedFenceDescriptor const* descriptor) { return wgpuDeviceImportSharedFence(object, descriptor); }

WGPUSharedTextureMemory
wgpu::Device::importSharedTextureMemory
(WGPUSharedTextureMemoryDescriptor const* descriptor) { return wgpuDeviceImportSharedTextureMemory(object, descriptor); }

void
wgpu::Device::injectError
(WGPUErrorType type, WGPUStringView message) { wgpuDeviceInjectError(object, type, message); }

WGPUFuture
wgpu::Device::popErrorScope
(WGPUPopErrorScopeCallbackInfo callbackInfo) { return wgpuDevicePopErrorScope(object, callbackInfo); }

void 
wgpu::Device::pushErrorScope
(WGPUErrorFilter filter) { wgpuDevicePushErrorScope(object, filter); }

void
wgpu::Device::setLabel
(WGPUStringView label) { wgpuDeviceSetLabel(object, label); }

WGPU_XIN_EXTRA
void
wgpu::Device::setLabel
(const char* label) { wgpuDeviceSetLabel(object, { label, strlen(label) }); }

void
wgpu::Device::setLoggingCallback
(WGPULoggingCallbackInfo callbackInfo) { wgpuDeviceSetLoggingCallback(object, callbackInfo); }

void
wgpu::Device::tick
() { wgpuDeviceTick(object); }

void
wgpu::Device::validateTextureDescriptor
(WGPUTextureDescriptor const* descriptor) { wgpuDeviceValidateTextureDescriptor(object, descriptor); }

void 
wgpu::Device::addRef
() { wgpuDeviceAddRef(object); }

void
wgpu::Device::release
() { wgpuDeviceRelease(object); }


// ***** ADAPTER METHODS
//
WGPUDevice
wgpu::Adapter::createDevice
(WGPU_NULLABLE WGPUDeviceDescriptor const* descriptor) { return wgpuAdapterCreateDevice(object, descriptor); }

void
wgpu::Adapter::getFeatures
(WGPUSupportedFeatures* features) { return wgpuAdapterGetFeatures(object, features); }

WGPUStatus
wgpu::Adapter::getFormatCapabilities
(WGPUTextureFormat format, WGPUDawnFormatCapabilities* capabilities) { return wgpuAdapterGetFormatCapabilities(object, format, capabilities); }

WGPUStatus
wgpu::Adapter::getInfo
(WGPUAdapterInfo* info) { return wgpuAdapterGetInfo(object, info); }

WGPUInstance
wgpu::Adapter::getInstance
() { return wgpuAdapterGetInstance(object); }

WGPUStatus
wgpu::Adapter::getLimits
(WGPULimits* limits) { return wgpuAdapterGetLimits(object, limits); }

WGPU_XIN_EXTRA
WGPULimits
wgpu::Adapter::getDefaultLimits()
{
	WGPULimits adapterLimits = {};
	getLimits(&adapterLimits);

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

WGPUBool
wgpu::Adapter::hasFeature
(WGPUFeatureName feature) { return wgpuAdapterHasFeature(object, feature); }

WGPUFuture
wgpu::Adapter::requestDevice
(WGPU_NULLABLE WGPUDeviceDescriptor const* descriptor, WGPURequestDeviceCallbackInfo callbackInfo) { return wgpuAdapterRequestDevice(object, descriptor, callbackInfo); }

void 
wgpu::Adapter::addRef
() { return wgpuAdapterAddRef(object); }

void
wgpu::Adapter::release
(){	wgpuAdapterRelease(object); }


// ***** INSTANCE METHODS
//
WGPUSurface
wgpu::Instance::createSurface
(WGPUSurfaceDescriptor const* descriptor) { return wgpuInstanceCreateSurface(object, descriptor); }

void 
wgpu::Instance::getWGSLLanguageFeatures
(WGPUSupportedWGSLLanguageFeatures* features) { return wgpuInstanceGetWGSLLanguageFeatures(object, features); }

WGPUBool 
wgpu::Instance::hasWGSLLanguageFeature
(WGPUWGSLLanguageFeatureName feature) { return wgpuInstanceHasWGSLLanguageFeature(object, feature); }

void 
wgpu::Instance::processEvents
() { return wgpuInstanceProcessEvents(object); }

WGPUFuture
wgpu::Instance::requestAdapter
(WGPU_NULLABLE WGPURequestAdapterOptions const* options, WGPURequestAdapterCallbackInfo callbackInfo) { return wgpuInstanceRequestAdapter(object, options, callbackInfo); }

WGPUWaitStatus
wgpu::Instance::waitAny
(size_t futureCount, WGPU_NULLABLE WGPUFutureWaitInfo* futures, uint64_t timeoutNS) { return wgpuInstanceWaitAny(object, futureCount, futures, timeoutNS); }

void 
wgpu::Instance::addRef
() { return wgpuInstanceAddRef(object); }

void 
wgpu::Instance::release
() { return wgpuInstanceRelease(object); }



WGPUInstance
wgpu::createInstance
(WGPU_NULLABLE WGPUInstanceDescriptor const* descriptor) { return wgpuCreateInstance(descriptor); }




// ***** SURFACE METHODS
//
void 
wgpu::Surface::configure
(WGPUSurfaceConfiguration const* config) { wgpuSurfaceConfigure(object, config); }

WGPUStatus 
wgpu::Surface::getCapabilities
(WGPUAdapter adapter, WGPUSurfaceCapabilities* capabilities) { return wgpuSurfaceGetCapabilities(object, adapter, capabilities); }

WGPU_XIN_EXTRA
WGPUStatus 
wgpu::Surface::getCapabilities
(wgpu::Adapter adapter, WGPUSurfaceCapabilities* capabilities) { return wgpuSurfaceGetCapabilities(object, adapter.object, capabilities); }

void 
wgpu::Surface::getCurrentTexture
(WGPUSurfaceTexture* surfaceTexture) { wgpuSurfaceGetCurrentTexture(object, surfaceTexture); }

wgpu::TextureView
wgpu::Surface::getCurrentTextureView()
{
	WGPUSurfaceTexture surfaceTexture = {};
	getCurrentTexture(&surfaceTexture);

	if (surfaceTexture.status != WGPUSurfaceGetCurrentTextureStatus_SuccessOptimal && surfaceTexture.status != WGPUSurfaceGetCurrentTextureStatus_SuccessSuboptimal)
	{
		//OutputDebugString("ERROR | wgpu::Surface::getCurrentTextureView() | Failed to retrieve a valid current texture :(\n");
	}

	WGPUTextureViewDescriptor viewDesc = {};
	viewDesc.nextInChain      = nullptr;
	viewDesc.label.data       = "Surface texture view";
	viewDesc.label.length     = strlen(viewDesc.label.data);
	viewDesc.format           = wgpuTextureGetFormat(surfaceTexture.texture);
	viewDesc.dimension        = WGPUTextureViewDimension_2D;
	viewDesc.baseMipLevel     = 0;
	viewDesc.mipLevelCount    = 1;
	viewDesc.baseArrayLayer   = 0;
	viewDesc.arrayLayerCount  = 1;
	viewDesc.aspect           = WGPUTextureAspect_All;


	wgpu::TextureView textureView = {};
	textureView.object = wgpuTextureCreateView(surfaceTexture.texture, &viewDesc);
	wgpuTextureRelease(surfaceTexture.texture);

	return textureView;
}

WGPU_XIN_EXTRA
WGPUTextureFormat
wgpu::Surface::getFormat (WGPUAdapter adapter, uint32 index)
{
	WGPUSurfaceCapabilities capabilities = {};
	getCapabilities(adapter, &capabilities);
	return capabilities.formats[index];
}

WGPU_XIN_EXTRA
WGPUTextureFormat
wgpu::Surface::getFormat (wgpu::Adapter adapter, uint32 index)
{
	WGPUSurfaceCapabilities capabilities = {};
	getCapabilities(adapter.object, &capabilities);
	return capabilities.formats[index];
}

WGPUStatus 
wgpu::Surface::present
() { return wgpuSurfacePresent(object); }

void 
wgpu::Surface::setLabel
(WGPUStringView label) { wgpuSurfaceSetLabel(object, label); }

WGPU_XIN_EXTRA
void
wgpu::Surface::setLabel
(const char* label) { wgpuSurfaceSetLabel(object, { label, strlen(label) }); }

void
wgpu::Surface::unconfigure
() { wgpuSurfaceUnconfigure(object); }

void
wgpu::Surface::addRef
() { wgpuSurfaceAddRef(object); }

void 
wgpu::Surface::release
() { wgpuSurfaceRelease(object); }


// ***** TEXTURE METHODS
//
WGPUTextureView
wgpu::Texture::createErrorView
(WGPU_NULLABLE WGPUTextureViewDescriptor const* descriptor) { return wgpuTextureCreateErrorView(object, descriptor); }

WGPUTextureView 
wgpu::Texture::createView
(WGPU_NULLABLE WGPUTextureViewDescriptor const* descriptor) { return wgpuTextureCreateView(object, descriptor); }

wgpu::TextureView
wgpu::Texture::createViewHelper
(WGPU_NULLABLE WGPUTextureViewDescriptor const* descriptor)
{
	wgpu::TextureView textureView = {};
	textureView.object = createView(descriptor);
	return textureView;
}

void
wgpu::Texture::destroy
() { wgpuTextureDestroy(object); }

uint32
wgpu::Texture::getDepthOrArrayLayers
() { return wgpuTextureGetDepthOrArrayLayers(object); }

WGPUTextureDimension
wgpu::Texture::getDimension
() { return wgpuTextureGetDimension(object); }

WGPUTextureFormat 
wgpu::Texture::getFormat
() { return wgpuTextureGetFormat(object); }

uint32
wgpu::Texture::getHeight
() { return wgpuTextureGetHeight(object); }

uint32
wgpu::Texture::getMipLevelCount
() { return wgpuTextureGetMipLevelCount(object); }

uint32
wgpu::Texture::getSampleCount
() { return wgpuTextureGetSampleCount(object); }

WGPUTextureViewDimension
wgpu::Texture::getTextureBindingViewDimension
() { return wgpuTextureGetTextureBindingViewDimension(object); }

WGPUTextureUsage
wgpu::Texture::getUsage
() { return wgpuTextureGetUsage(object); }

uint32
wgpu::Texture::getWidth
() { return wgpuTextureGetWidth(object); }

void
wgpu::Texture::pin
(WGPUTextureUsage usage) { wgpuTexturePin(object, usage); }

void
wgpu::Texture::setLabel
(WGPUStringView label) { wgpuTextureSetLabel(object, label); }

WGPU_XIN_EXTRA
void
wgpu::Texture::setLabel
(const char* label) { wgpuTextureSetLabel(object, { label, strlen(label) }); }

void 
wgpu::Texture::setOwnershipForMemoryDump
(uint64 ownerGuid) { wgpuTextureSetOwnershipForMemoryDump(object, ownerGuid); }

void
wgpu::Texture::unpin
() { wgpuTextureUnpin(object); }

void
wgpu::Texture::addRef
() { wgpuTextureAddRef(object); }

void 
wgpu::Texture::release
() { wgpuTextureRelease(object); }


// ***** SHADER MODULE METHODS
//
WGPUFuture
wgpu::ShaderModule::getCompilationInfo
(WGPUCompilationInfoCallbackInfo callbackInfo) { return wgpuShaderModuleGetCompilationInfo(object, callbackInfo); }

void 
wgpu::ShaderModule::setLabel
(WGPUStringView label) { wgpuShaderModuleSetLabel(object, label); }

WGPU_XIN_EXTRA
void 
wgpu::ShaderModule::setLabel
(const char* label) { wgpuShaderModuleSetLabel(object, { label, strlen(label) }); }

void 
wgpu::ShaderModule::addRef
() { wgpuShaderModuleAddRef(object); }

void 
wgpu::ShaderModule::release
() { wgpuShaderModuleRelease(object); }


// ***** QUEUE METHODS
//
void
wgpu::Queue::copyExternalTextureForBrowser
(WGPUImageCopyExternalTexture const* source, WGPUTexelCopyTextureInfo const* destination, WGPUExtent3D const* copySize, WGPUCopyTextureForBrowserOptions const* options)
{ wgpuQueueCopyExternalTextureForBrowser(object, source, destination, copySize, options); }

void 
wgpu::Queue::copyTextureForBrowser
(WGPUTexelCopyTextureInfo const* source, WGPUTexelCopyTextureInfo const* destination, WGPUExtent3D const* copySize, WGPUCopyTextureForBrowserOptions const* options)
{ wgpuQueueCopyTextureForBrowser(object, source, destination, copySize, options); }

WGPUFuture
wgpu::Queue::onSubmittedWorkDone
(WGPUQueueWorkDoneCallbackInfo callbackInfo) { return wgpuQueueOnSubmittedWorkDone(object, callbackInfo); }

void
wgpu::Queue::setLabel
(WGPUStringView label) { wgpuQueueSetLabel(object, label); }

WGPU_XIN_EXTRA
void 
wgpu::Queue::setLabel
(const char* label) { wgpuQueueSetLabel(object, { label, strlen(label) }); }

void 
wgpu::Queue::submit
(size_t commandCount, WGPUCommandBuffer const* commands) { wgpuQueueSubmit(object, commandCount, commands); }

void 
wgpu::Queue::writeBuffer
(WGPUBuffer buffer, uint64_t bufferOffset, void const* data, size_t size) { wgpuQueueWriteBuffer(object, buffer, bufferOffset, data, size); }

WGPU_XIN_EXTRA
void 
wgpu::Queue::writeBuffer
(wgpu::Buffer buffer, uint64_t bufferOffset, void const* data, size_t size) { wgpuQueueWriteBuffer(object, buffer.object, bufferOffset, data, size); }

void 
wgpu::Queue::writeTexture
(WGPUTexelCopyTextureInfo const* destination, void const* data, size_t dataSize, WGPUTexelCopyBufferLayout const* dataLayout, WGPUExtent3D const* writeSize)
{ wgpuQueueWriteTexture(object, destination, data, dataSize, dataLayout, writeSize); }

void 
wgpu::Queue::addRef
() { wgpuQueueAddRef(object); }

void 
wgpu::Queue::release
() { wgpuQueueRelease(object); }


// ***** COMMAND ENCODER METHODS
//
WGPUComputePassEncoder
wgpu::CommandEncoder::beginComputePass
(WGPU_NULLABLE WGPUComputePassDescriptor const* descriptor) { return wgpuCommandEncoderBeginComputePass(object, descriptor); }

WGPURenderPassEncoder 
wgpu::CommandEncoder::beginRenderPass
(WGPURenderPassDescriptor const* descriptor) { return wgpuCommandEncoderBeginRenderPass(object, descriptor); }

WGPU_XIN_EXTRA
wgpu::RenderPassEncoder 
wgpu::CommandEncoder::beginRenderPassHelper
(WGPURenderPassDescriptor const* descriptor) 
{
	wgpu::RenderPassEncoder encoder = {};
	encoder.object = beginRenderPass(descriptor);
	return encoder;
}

void 
wgpu::CommandEncoder::clearBuffer
(WGPUBuffer buffer, uint64_t offset, uint64_t size) { return wgpuCommandEncoderClearBuffer(object, buffer, offset, size); }

void 
wgpu::CommandEncoder::copyBufferToBuffer
(WGPUBuffer source, uint64_t sourceOffset, WGPUBuffer destination, uint64_t destinationOffset, uint64_t size)
{ wgpuCommandEncoderCopyBufferToBuffer(object, source, sourceOffset, destination, destinationOffset, size); }

void 
wgpu::CommandEncoder::copyBufferToTexture
(WGPUTexelCopyBufferInfo const* source, WGPUTexelCopyTextureInfo const* destination, WGPUExtent3D const* copySize)
{ wgpuCommandEncoderCopyBufferToTexture(object, source, destination, copySize); }

void 
wgpu::CommandEncoder::copyTextureToBuffer
(WGPUTexelCopyTextureInfo const* source, WGPUTexelCopyBufferInfo const* destination, WGPUExtent3D const* copySize)
{ wgpuCommandEncoderCopyTextureToBuffer(object, source, destination, copySize); }

void 
wgpu::CommandEncoder::copyTextureToTexture
(WGPUTexelCopyTextureInfo const* source, WGPUTexelCopyTextureInfo const* destination, WGPUExtent3D const* copySize)
{ wgpuCommandEncoderCopyTextureToTexture(object, source, destination, copySize); }

WGPUCommandBuffer 
wgpu::CommandEncoder::finish
(WGPU_NULLABLE WGPUCommandBufferDescriptor const* descriptor) { return wgpuCommandEncoderFinish(object, descriptor); }

WGPU_XIN_EXTRA
wgpu::CommandBuffer 
wgpu::CommandEncoder::finishHelper
(WGPU_NULLABLE WGPUCommandBufferDescriptor const* descriptor) 
{
	wgpu::CommandBuffer commandBuffer = {};
	commandBuffer.object = finish(descriptor);
	return commandBuffer;
}

void
wgpu::CommandEncoder::injectValidationError
(WGPUStringView message) { wgpuCommandEncoderInjectValidationError(object, message); }

void
wgpu::CommandEncoder::injectDebugMarker
(WGPUStringView message) { wgpuCommandEncoderInsertDebugMarker(object, message); }

void 
wgpu::CommandEncoder::popDebugGroup
() { wgpuCommandEncoderPopDebugGroup(object); }

void 
wgpu::CommandEncoder::pushDebugGroup
(WGPUStringView groupLabel) { wgpuCommandEncoderPushDebugGroup(object, groupLabel); }

void 
wgpu::CommandEncoder::resolveQuerySet
(WGPUQuerySet querySet, uint32_t firstQuery, uint32_t queryCount, WGPUBuffer destination, uint64_t destinationOffset)
{ wgpuCommandEncoderResolveQuerySet(object, querySet, firstQuery, queryCount, destination, destinationOffset); }

void
wgpu::CommandEncoder::setLabel
(WGPUStringView label) { wgpuCommandEncoderSetLabel(object, label); }

WGPU_XIN_EXTRA
void
wgpu::CommandEncoder::setLabel
(const char* label) { wgpuCommandEncoderSetLabel(object, { label, strlen(label) }); }

void 
wgpu::CommandEncoder::setResourceTable
(WGPU_NULLABLE WGPUResourceTable table) { wgpuCommandEncoderSetResourceTable(object, table); }

void 
wgpu::CommandEncoder::writeBuffer
(WGPUBuffer buffer, uint64_t bufferOffset, uint8_t const* data, uint64_t size) { wgpuCommandEncoderWriteBuffer(object, buffer, bufferOffset, data, size); }

void 
wgpu::CommandEncoder::writeTimestamp
(WGPUQuerySet querySet, uint32_t queryIndex) { wgpuCommandEncoderWriteTimestamp(object, querySet, queryIndex); }

void 
wgpu::CommandEncoder::addRef
() { wgpuCommandEncoderAddRef(object); }

void 
wgpu::CommandEncoder::release
() { wgpuCommandEncoderRelease(object); }


// ***** RENDER PASS ENCODER METHODS
//
void 
wgpu::RenderPassEncoder::beginOcclusionQuery
(uint32_t queryIndex) { wgpuRenderPassEncoderBeginOcclusionQuery(object, queryIndex); }

void 
wgpu::RenderPassEncoder::draw
(uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance) 
{ wgpuRenderPassEncoderDraw(object, vertexCount, instanceCount, firstVertex, firstInstance); }

void 
wgpu::RenderPassEncoder::drawIndexed
(uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t baseVertex, uint32_t firstInstance)
{ wgpuRenderPassEncoderDrawIndexed(object, indexCount, instanceCount, firstIndex, baseVertex, firstInstance); }

void 
wgpu::RenderPassEncoder::drawIndexedIndirect
(WGPUBuffer indirectBuffer, uint64_t indirectOffset) { wgpuRenderPassEncoderDrawIndexedIndirect(object, indirectBuffer, indirectOffset); }

void 
wgpu::RenderPassEncoder::end
() { wgpuRenderPassEncoderEnd(object); }

void 
wgpu::RenderPassEncoder::endOcclusionQuery
() { wgpuRenderPassEncoderEndOcclusionQuery(object); }

void 
wgpu::RenderPassEncoder::executeBundles
(size_t bundleCount, WGPURenderBundle const* bundles) { wgpuRenderPassEncoderExecuteBundles(object, bundleCount, bundles); }

void
wgpu::RenderPassEncoder::insertDebugMarker
(WGPUStringView markerLabel) { wgpuRenderPassEncoderInsertDebugMarker(object, markerLabel); }

void
wgpu::RenderPassEncoder::multiDrawIndexedIndirect
(WGPUBuffer indirectBuffer, uint64_t indirectOffset, uint32_t maxDrawCount, WGPU_NULLABLE WGPUBuffer drawCountBuffer, uint64_t drawCountBufferOffset)
{ wgpuRenderPassEncoderMultiDrawIndexedIndirect(object, indirectBuffer, indirectOffset, maxDrawCount, drawCountBuffer, drawCountBufferOffset); }

void
wgpu::RenderPassEncoder::multiDrawIndirect
(WGPUBuffer indirectBuffer, uint64_t indirectOffset, uint32_t maxDrawCount, WGPU_NULLABLE WGPUBuffer drawCountBuffer, uint64_t drawCountBufferOffset)
{ wgpuRenderPassEncoderMultiDrawIndirect(object, indirectBuffer, indirectOffset, maxDrawCount, drawCountBuffer, drawCountBufferOffset); }

void
wgpu::RenderPassEncoder::pixelLocalStorageBarrier
() { wgpuRenderPassEncoderPixelLocalStorageBarrier(object); }

void
wgpu::RenderPassEncoder::popDebugGroup
() { wgpuRenderPassEncoderPopDebugGroup(object); }

void
wgpu::RenderPassEncoder::pushDebugGroup
(WGPUStringView groupLabel) { wgpuRenderPassEncoderPushDebugGroup(object, groupLabel); }

void 
wgpu::RenderPassEncoder::setBindGroup
(uint32_t groupIndex, WGPU_NULLABLE WGPUBindGroup group, size_t dynamicOffsetCount, uint32_t const* dynamicOffsets)
{ wgpuRenderPassEncoderSetBindGroup(object, groupIndex, group, dynamicOffsetCount, dynamicOffsets); }

void 
wgpu::RenderPassEncoder::setBindGroup
(uint32_t groupIndex, wgpu::BindGroup group, size_t dynamicOffsetCount, uint32_t const* dynamicOffsets)
{ wgpuRenderPassEncoderSetBindGroup(object, groupIndex, group.object, dynamicOffsetCount, dynamicOffsets); }

void 
wgpu::RenderPassEncoder::setBlendConstant
(WGPUColor const* color) { wgpuRenderPassEncoderSetBlendConstant(object, color); }

void 
wgpu::RenderPassEncoder::setImmediates
(uint32_t offset, void const* data, size_t size) { wgpuRenderPassEncoderSetImmediates(object, offset, data, size); }

void 
wgpu::RenderPassEncoder::setIndexBuffer
(WGPUBuffer buffer, WGPUIndexFormat format, uint64_t offset, uint64_t size) { wgpuRenderPassEncoderSetIndexBuffer(object, buffer, format, offset, size); }

WGPU_XIN_EXTRA
void 
wgpu::RenderPassEncoder::setIndexBuffer
(wgpu::Buffer buffer, WGPUIndexFormat format, uint64_t offset, uint64_t size) { wgpuRenderPassEncoderSetIndexBuffer(object, buffer.object, format, offset, size); }

void
wgpu::RenderPassEncoder::setLabel
(WGPUStringView label) { wgpuRenderPassEncoderSetLabel(object, label); }

WGPU_XIN_EXTRA
void 
wgpu::RenderPassEncoder::setLabel
(const char* label) { wgpuRenderPassEncoderSetLabel(object, { label, strlen(label) }); }

void
wgpu::RenderPassEncoder::setPipeline
(WGPURenderPipeline pipeline) {	wgpuRenderPassEncoderSetPipeline(object, pipeline); }

WGPU_XIN_EXTRA
void
wgpu::RenderPassEncoder::setPipeline
(wgpu::RenderPipeline pipeline) {	wgpuRenderPassEncoderSetPipeline(object, pipeline.object); }

void
wgpu::RenderPassEncoder::setScissorRect
(uint32_t x, uint32_t y, uint32_t width, uint32_t height) { wgpuRenderPassEncoderSetScissorRect(object, x, y, width, height); }

void
wgpu::RenderPassEncoder::setStencilReference
(uint32_t reference) { wgpuRenderPassEncoderSetStencilReference(object, reference); }

void 
wgpu::RenderPassEncoder::setVertexBuffer
(uint32_t slot, WGPU_NULLABLE WGPUBuffer buffer, uint64_t offset, uint64_t size) { wgpuRenderPassEncoderSetVertexBuffer(object, slot, buffer, offset, size); }

void 
wgpu::RenderPassEncoder::setVertexBuffer
(uint32_t slot, wgpu::Buffer buffer, uint64_t offset, uint64_t size) { wgpuRenderPassEncoderSetVertexBuffer(object, slot, buffer.object, offset, size); }

void 
wgpu::RenderPassEncoder::setViewport
(float x, float y, float width, float height, float minDepth, float maxDepth) { wgpuRenderPassEncoderSetViewport(object, x, y, width, height, minDepth, maxDepth); }

void 
wgpu::RenderPassEncoder::writeTimestamp
(WGPUQuerySet querySet, uint32_t queryIndex) { wgpuRenderPassEncoderWriteTimestamp(object, querySet, queryIndex); }

void 
wgpu::RenderPassEncoder::addRef
() { wgpuRenderPassEncoderAddRef(object); }

void 
wgpu::RenderPassEncoder::release
() { wgpuRenderPassEncoderRelease(object); }


// ***** RENDER PIPELINE METHODS
//
WGPUBindGroupLayout
wgpu::RenderPipeline::getBindGroupLayout
(uint32_t groupIndex) { return wgpuRenderPipelineGetBindGroupLayout(object, groupIndex); }

void 
wgpu::RenderPipeline::setLabel
(WGPUStringView label) { wgpuRenderPipelineSetLabel(object, label); }

WGPU_XIN_EXTRA
void
wgpu::RenderPipeline::setLabel
(const char* label) { wgpuRenderPipelineSetLabel(object, { label, strlen(label) }); }

void
wgpu::RenderPipeline::addRef
() { wgpuRenderPipelineAddRef(object); }

void 
wgpu::RenderPipeline::release
() { wgpuRenderPipelineRelease(object); }


// ***** BUFFER METHODS
//
WGPUTexelBufferView 
wgpu::Buffer::createTexelView
(WGPUTexelBufferViewDescriptor const* descriptor) { return wgpuBufferCreateTexelView(object, descriptor); }

void
wgpu::Buffer::destroy
() { wgpuBufferDestroy(object); }

void const*
wgpu::Buffer::getConstMappedRange
(size_t offset, size_t size) { return wgpuBufferGetConstMappedRange(object, offset, size); }

void* 
wgpu::Buffer::getMappedRange
(size_t offset, size_t size) { return wgpuBufferGetMappedRange(object, offset, size); }

WGPUBufferMapState
wgpu::Buffer::getMapState
() { return wgpuBufferGetMapState(object); }

uint64
wgpu::Buffer::getSize
() { return wgpuBufferGetSize(object); }

WGPUBufferUsage
wgpu::Buffer::getUsage
() { return wgpuBufferGetUsage(object); }

WGPUFuture
wgpu::Buffer::mapAsync
(WGPUMapMode mode, size_t offset, size_t size, WGPUBufferMapCallbackInfo callbackInfo) { return wgpuBufferMapAsync(object, mode, offset, size, callbackInfo); }

WGPUStatus
wgpu::Buffer::readMappedRange
(size_t offset, void* data, size_t size) { return wgpuBufferReadMappedRange(object, offset, data, size); }

void 
wgpu::Buffer::setLabel
(WGPUStringView label) { wgpuBufferSetLabel(object, label); }

WGPU_XIN_EXTRA
void 
wgpu::Buffer::setLabel
(const char* label) { wgpuBufferSetLabel(object, { label, strlen(label) }); }

void
wgpu::Buffer::unmap
() { wgpuBufferUnmap(object); }

WGPUStatus
wgpu::Buffer::writeMappedRange
(size_t offset, void const* data, size_t size) { return wgpuBufferWriteMappedRange(object, offset, data, size); }

void
wgpu::Buffer::addRef
() { wgpuBufferAddRef(object); }

void 
wgpu::Buffer::release
() { wgpuBufferRelease(object); }


// ***** BIND GROUP LAYOUT METHODS
//
void
wgpu::BindGroupLayout::setLabel
(WGPUStringView label) { wgpuBindGroupLayoutSetLabel(object, label); }

WGPU_XIN_EXTRA
void 
wgpu::BindGroupLayout::setLabel
(const char* label) { wgpuBindGroupLayoutSetLabel(object, {label, strlen(label)}); }

void 
wgpu::BindGroupLayout::addRef
() { wgpuBindGroupLayoutAddRef(object); }

void 
wgpu::BindGroupLayout::release
() { wgpuBindGroupLayoutRelease(object); }


// ***** PIPELINE LAYOUT METHODS
//
void
wgpu::PipelineLayout::setLabel
(WGPUStringView label) { wgpuPipelineLayoutSetLabel(object, label); }

WGPU_XIN_EXTRA
void 
wgpu::PipelineLayout::setLabel
(const char* label) { wgpuPipelineLayoutSetLabel(object, { label, strlen(label) }); }

void 
wgpu::PipelineLayout::addRef
() { wgpuPipelineLayoutAddRef(object); }

void 
wgpu::PipelineLayout::release
() { wgpuPipelineLayoutRelease(object); }



// ***** BIND GROUP METHODS
//
void
wgpu::BindGroup::setLabel
(WGPUStringView label) { wgpuBindGroupSetLabel(object, label); }

WGPU_XIN_EXTRA
void
wgpu::BindGroup::setLabel
(const char* label) { wgpuBindGroupSetLabel(object, { label, strlen(label) }); }

void
wgpu::BindGroup::addRef
() { wgpuBindGroupAddRef(object); }

void
wgpu::BindGroup::release
() { wgpuBindGroupRelease(object); }


// ***** TEXTURE VIEW METHODS
//
void
wgpu::TextureView::setLabel
(WGPUStringView label) { wgpuTextureViewSetLabel(object, label); }

WGPU_XIN_EXTRA
void
wgpu::TextureView::setLabel
(const char* label) { wgpuTextureViewSetLabel(object, { label, strlen(label) }); }

void
wgpu::TextureView::addRef
() { wgpuTextureViewAddRef(object); }

void
wgpu::TextureView::release
() { wgpuTextureViewRelease(object); }


// ***** COMMAND BUFFER METHODS
//
void
wgpu::CommandBuffer::setLabel
(WGPUStringView label) { wgpuCommandBufferSetLabel(object, label); }

WGPU_XIN_EXTRA
void
wgpu::CommandBuffer::setLabel
(const char* label) { wgpuCommandBufferSetLabel(object, { label, strlen(label) }); }

void
wgpu::CommandBuffer::addRef
() { wgpuCommandBufferAddRef(object); }

void
wgpu::CommandBuffer::release
() { wgpuCommandBufferRelease(object); }