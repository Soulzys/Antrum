#include "wgpu_layer.h"
#include "string.h"


// ***** HELPER METHODS
//



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