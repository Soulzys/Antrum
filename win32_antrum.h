#pragma once

#include "include/webgpu.h"
#include "windows.h"
#include <stdint.h>



/* 
	# TODO
	~~~~~~

	1. Create game layer
	2. Move to 3D
	3. Add inputs
	4. Profit

*/



typedef int8_t   int8   ;
typedef int16_t  int16  ;
typedef int32_t  int32  ;
typedef int64_t  int64  ;
typedef uint8_t  uint8  ;
typedef uint16_t uint16 ;
typedef uint32_t uint32 ;
typedef uint64_t uint64 ;

typedef float    real32 ;
typedef double   real64 ;

typedef int32    bool32 ;




#define KILOBYTES(Value) ((Value)          * 1024LL)
#define MEGABYTES(Value) (KILOBYTES(Value) * 1024LL)
#define GIGABYTES(Value) (MEGABYTES(Value) * 1024LL)

#define ASSERT(Expression) if (!(Expression)) {*(int*)0 = 0;}
#define ASSERT_MSG(Expression, Message) if (!(Expression)) \
{                                                          \
	OutputDebugString(Message);                            \
	ASSERT(Expression);                                    \
}                                                          \


#define STRING_MAX_LENGTH 10000
#define WINDOW_WIDTH      1200
#define WINDOW_HEIGHT     800
#define MEMSIZE_GAME      MEGABYTES(64)
#define MEMSIZE_READ_FILE MEGABYTES(4)
#define MEMSIZE_ASSETS    MEGABYTES(12)
#define ASSET_MAX_POINTS  1000





enum AssetType
{
	SHADER_CODE = 0, 
	MESH = 1
};

struct Vec3
{
	real32 x;
	real32 y;
	real32 z;
};

struct Vec3I
{
	uint16 a;
	uint16 b;
	uint16 c;
};



struct String
{
	const char* head;
	size_t size;
};



struct ShaderUniform
{
	// When dealing with uniform offset, the formula is that for each struct member, its offset has to be a multiple of: offset * sizeof(memberType);
	real32 color[4]; // offset = 0 * sizeof(vec4f) --> OK, 0 is a multiple of 16
	real32 time; // offset = 16 = 4 * sizeof(f32) --> OK, 16 is a multiple of 16

	// Makes it host-shareable by adding padding at the end of the struct so its total size if a multiple of its largest bit-field (here, a multiple of 16,
	// as its total size would then be 32 bytes).
	real32 __padding[3];
};
static_assert(sizeof(ShaderUniform) % sizeof(ShaderUniform::color) == 0);

struct MemoryChunk
{
	void* allocate(size_t amount);

	uint64 size;
	uint64 offset;
	char*  memory;
};


template<typename T>
struct VectorGPU
{
	T arr;
	size_t counter;
};

template<typename T, size_t N>
class Vector
{

public:
	inline void push(T stuff)
	{
		ASSERT_MSG(m_index < N, "ERROR | Vector::push() | End of array reached, cannot push any more !\n");
		
		m_arr[m_index] = stuff;
		m_index++;
	}

	inline const T& at_read(size_t index)
	{
		ASSERT(index <= N);
		const T& element = m_arr[index];
		return element;
	}
	inline T* at_readWrite(size_t index)
	{
		ASSERT(index <= N);
		return &m_arr[index];
	}
	inline T at(size_t index)
	{
		ASSERT(index <= N);
		return m_arr[index];
	}

	inline size_t   getSize()            const { return sizeof(T) * N + sizeof(m_index); }
	inline size_t   getLength()          const { return N;                               }
	inline size_t   getElementsSize()    const { return sizeof(T) * (m_index);           }
	inline size_t   getElementsLength()  const { return m_index;                         }
	inline const T& dataRef()            const { return m_arr[0];                        }
	inline const T* dataPtr()            const { return &m_arr[0];                       }

	//inline VectorGPU<T> trimForGPU() const
	//{
	//	VectorGPU<T> v = {};
	//	v.arr = m_arr.at(0);
	//	v.counter = m_index;
	//}

private:
	T m_arr[N];
	size_t m_index = 0;
};

struct MeshAsset
{
	Vector<real32, ASSET_MAX_POINTS> vertices;
	Vector<uint16, ASSET_MAX_POINTS> indexes; // >TODO: find a more efficient way to calculate the minimum amount of indexes
	uint64 size;
};

struct AssetManager
{
	Vector<MeshAsset*, 1> meshAssets;
};



/*
	Memory Layout
	~~~~~~~~~~~~~

	+-------------+--------------------+
	|  Read File  |       Assets       |
	+-------------+--------------------+
	<------------- Fatty -------------->
*/
struct GameMemory
{
	MemoryChunk fattyChunk;
	MemoryChunk readFileChunk;
	MemoryChunk assetsChunk;
};

struct ReadFileResult
{
	uint32      contentSize;
	void*       content;
	const char* message;
};

struct FileReader
{
	const char* reader;
	size_t counter;

	inline FileReader& operator++(int)
	{
		reader++;
		counter++;
		return *this;
	}

	inline FileReader& operator+=(int n)
	{
		reader += n;
		counter += n;
		return *this;
	}

	inline FileReader operator+(int n)
	{
		FileReader temp = *this;
		temp.reader += n;
		temp.counter += n;
		return temp;
	}
};


// >NOTE: custom utilitary functions that were added to WGPU objects structs
#if !defined(WGPU_XIN_EXTRA)
#define WGPU_XIN_EXTRA
#endif

namespace wgpu
{
	WGPUInstance createInstance(WGPU_NULLABLE WGPUInstanceDescriptor const* descriptor);

	struct Device            ;
	struct Adapter           ;
	struct Instance          ;
	struct Surface           ;
	struct Texture           ;
	struct ShaderModule      ;
	struct Queue             ;
	struct CommandEncoder    ;
	struct RenderPassEncoder ;
	struct RenderPipeline    ;
	struct Buffer            ;
	struct BindGroupLayout   ;
	struct PipelineLayout    ;
	struct BindGroup         ;
	struct TextureView       ;
	struct CommandBuffer     ;

	namespace helper
	{
		wgpu::Instance        createInstance        ();
		wgpu::Adapter         createAdapter         (wgpu::Instance instance);
		wgpu::Device          createDevice          (wgpu::Adapter adapter);
		wgpu::Surface         createSurface         (WNDCLASS* wndClass, HWND wndHandle, wgpu::Instance instance);
		wgpu::ShaderModule    createShaderModule    (wgpu::Device device, GameMemory* memory, const char* path, const char* label);
		wgpu::BindGroupLayout createBindGroupLayout (wgpu::Device device);
		wgpu::PipelineLayout  createPipelineLayout  (wgpu::Device device, wgpu::BindGroupLayout bindGroupLayout);
		wgpu::RenderPipeline  createRenderPipeline  (wgpu::Device, wgpu::ShaderModule, WGPUTextureFormat, wgpu::PipelineLayout);

		WGPUAdapter requestAdapterAsync (wgpu::Instance instance, WGPURequestAdapterOptions const* options);
		WGPUDevice  requestDeviceAsync  (wgpu::Adapter adapter, const WGPUDeviceDescriptor* descriptor);
	}

	// 
	//struct ObjectContainer
	//{
	//	Instance*           instance;
	//	WGPUAdapter         adapter;
	//	WGPUDevice          device;
	//	WGPUSurface         surface;
	//	WGPUTextureFormat   surfaceFormat;
	//	WGPUShaderModule    shaderModule;
	//	WGPUPipelineLayout  pipelineLayout;
	//	WGPUBindGroupLayout bindGroupLayout;
	//	WGPUBindGroup       bindGroup;
	//	WGPURenderPipeline  renderPipeline;
	//	WGPUQueue           queue;
	//};


	// >NOTE: All of these structs are referred to as "helpers"
	//        Example: Device::getQueueHelper will return wgpu::Queue while Device::getQueue will return WGPUQueue
	struct Device
	{
		WGPUBindGroup           createBindGroup              (WGPUBindGroupDescriptor const* descriptor);
		wgpu::BindGroup         createBindGroupHelper        (WGPUBindGroupDescriptor const* descriptor) WGPU_XIN_EXTRA;
		WGPUBindGroupLayout     createBindGroupLayout        (WGPUBindGroupLayoutDescriptor const* descriptor);
		WGPUBuffer              createBuffer                 (WGPUBufferDescriptor const* descriptor);
		wgpu::Buffer            createBufferHelper           (WGPUBufferDescriptor const* descriptor) WGPU_XIN_EXTRA;
		WGPUCommandEncoder      createCommandEncoder         (WGPU_NULLABLE WGPUCommandEncoderDescriptor const* descriptor);
		wgpu::CommandEncoder    createCommandEncoderHelper   (WGPU_NULLABLE WGPUCommandEncoderDescriptor const* descriptor) WGPU_XIN_EXTRA;
		WGPUComputePipeline     createComputePipeline        (WGPUComputePipelineDescriptor const* descriptor);
		WGPUFuture              createComputePipelineAsync   (WGPUComputePipelineDescriptor const* descriptor, WGPUCreateComputePipelineAsyncCallbackInfo callbackInfo);
		WGPUBuffer              createErrorBuffer            (WGPUBufferDescriptor const* descriptor);
		WGPUExternalTexture     createErrorExternalTexture   ();
		WGPUShaderModule        createErrorShaderModule      (WGPUShaderModuleDescriptor const* descriptor, WGPUStringView errorMessage);
		WGPUTexture             createErrorTexture           (WGPUTextureDescriptor const* descriptor);
		WGPUExternalTexture     createExternalTexture        (WGPUExternalTextureDescriptor const* externalTextureDescriptor);
		WGPUPipelineLayout      createPipelineLayout         (WGPUPipelineLayoutDescriptor const* descriptor);
		WGPUQuerySet            createQuerySet               (WGPUQuerySetDescriptor const* descriptor);
		WGPURenderBundleEncoder createRenderBundleEncoder    (WGPURenderBundleEncoderDescriptor const* descriptor);
		WGPURenderPipeline      createRenderPipeline         (WGPURenderPipelineDescriptor const* descriptor);
		WGPUFuture              createRenderPipelineAsync    (WGPURenderPipelineDescriptor const* descriptor, WGPUCreateRenderPipelineAsyncCallbackInfo callbackInfo);
		WGPUResourceTable       createResourceTable          (WGPUResourceTableDescriptor const* descriptor);
		WGPUSampler             createSampler                (WGPU_NULLABLE WGPUSamplerDescriptor const* descriptor);
		WGPUShaderModule        createShaderModule           (WGPUShaderModuleDescriptor const* descriptor);
		WGPUTexture             createTexture                (WGPUTextureDescriptor const* descriptor);
		void                    destroy                      ();
		void                    forceLoss                    (WGPUDeviceLostReason type, WGPUStringView message);
		WGPUAdapter             getAdapter                   ();
		WGPUStatus              getAdapterInfo               (WGPUAdapterInfo* adapterInfo);
		WGPUStatus              getAHardwareBufferProperties (void* handle, WGPUAHardwareBufferProperties* properties);
		void                    getFeatures                  (WGPUSupportedFeatures* features);
		WGPUStatus              getLimits                    (WGPULimits* limits);
		WGPUFuture              getLostFuture                ();
		WGPUQueue               getQueue                     ();
		wgpu::Queue             getQueueHelper               () WGPU_XIN_EXTRA;
		WGPUBool                hasFeature                   (WGPUFeatureName feature);
		WGPUSharedBufferMemory  importShaderBufferMemory     (WGPUSharedBufferMemoryDescriptor const* descriptor);
		WGPUSharedFence         importSharedFence            (WGPUSharedFenceDescriptor const* descriptor);
		WGPUSharedTextureMemory importSharedTextureMemory    (WGPUSharedTextureMemoryDescriptor const* descriptor);
		void                    injectError                  (WGPUErrorType type, WGPUStringView message);
		WGPUFuture              popErrorScope                (WGPUPopErrorScopeCallbackInfo callbackInfo);
		void                    pushErrorScope               (WGPUErrorFilter filter);
		void                    setLabel                     (WGPUStringView label);
		void                    setLabel                     (const char* label) WGPU_XIN_EXTRA;
		void                    setLoggingCallback           (WGPULoggingCallbackInfo callbackInfo);
		void                    tick                         ();
		void                    validateTextureDescriptor    (WGPUTextureDescriptor const* descriptor);
		void                    addRef                       ();
		void                    release                      ();

		WGPUDevice object;
	};

	struct Adapter
	{
		WGPUDevice   createDevice          (WGPU_NULLABLE WGPUDeviceDescriptor const* descriptor);
		void         getFeatures           (WGPUSupportedFeatures* features);
		WGPUStatus   getFormatCapabilities (WGPUTextureFormat format, WGPUDawnFormatCapabilities* capabilities);
		WGPUStatus   getInfo               (WGPUAdapterInfo* info);
		WGPUInstance getInstance           ();
		WGPUStatus   getLimits             (WGPULimits* limits);
		WGPULimits   getDefaultLimits      () WGPU_XIN_EXTRA;
		WGPUBool     hasFeature            (WGPUFeatureName feature);
		WGPUFuture   requestDevice         (WGPU_NULLABLE WGPUDeviceDescriptor const* descriptor, WGPURequestDeviceCallbackInfo callbackInfo);
		void         addRef                ();
		void         release               ();

		WGPUAdapter object;
	};

	struct Instance
	{
		WGPUSurface    createSurface           (WGPUSurfaceDescriptor const* descriptor);
		void           getWGSLLanguageFeatures (WGPUSupportedWGSLLanguageFeatures* features);
		WGPUBool       hasWGSLLanguageFeature  (WGPUWGSLLanguageFeatureName feature);
		void           processEvents           ();
		WGPUFuture     requestAdapter          (WGPU_NULLABLE WGPURequestAdapterOptions const* options, WGPURequestAdapterCallbackInfo callbackInfo);
		WGPUWaitStatus waitAny                 (size_t futureCount, WGPU_NULLABLE WGPUFutureWaitInfo* futures, uint64_t timeoutNS);
		void           addRef                  ();
		void           release                 ();

		WGPUInstance object;
	};

	struct Surface
	{
		void              configure             (WGPUSurfaceConfiguration const* config);
		WGPUStatus        getCapabilities       (WGPUAdapter adapter, WGPUSurfaceCapabilities* capabilities);
		WGPUStatus        getCapabilities       (wgpu::Adapter adapter, WGPUSurfaceCapabilities* capabilities) WGPU_XIN_EXTRA;
		void              getCurrentTexture     (WGPUSurfaceTexture* surfaceTexture);
		wgpu::TextureView getCurrentTextureView () WGPU_XIN_EXTRA;
		WGPUTextureFormat getFormat             (WGPUAdapter adapter, uint32 index = 0) WGPU_XIN_EXTRA;
		WGPUTextureFormat getFormat             (wgpu::Adapter adapter, uint32 index = 0) WGPU_XIN_EXTRA;
		WGPUStatus        present               ();
		void              setLabel              (WGPUStringView label);
		void              setLabel              (const char* label) WGPU_XIN_EXTRA;
		void              unconfigure           ();
		void              addRef                ();
		void              release               ();

		WGPUSurface object;
	};

	struct Texture
	{
		WGPUTextureView          createErrorView                (WGPU_NULLABLE WGPUTextureViewDescriptor const* descriptor);
		WGPUTextureView          createView                     (WGPU_NULLABLE WGPUTextureViewDescriptor const* descriptor);
		void                     destroy                        ();
		uint32                   getDepthOrArrayLayers          ();
		WGPUTextureDimension     getDimension                   ();
		WGPUTextureFormat        getFormat                      ();
		uint32                   getHeight                      ();
		uint32                   getMipLevelCount               ();
		uint32                   getSampleCount                 ();
		WGPUTextureViewDimension getTextureBindingViewDimension ();
		WGPUTextureUsage         getUsage                       ();
		uint32                   getWidth                       ();
		void                     pin                            (WGPUTextureUsage usage);
		void                     setLabel                       (WGPUStringView label);
		void                     setLabel                       (const char* label) WGPU_XIN_EXTRA;
		void                     setOwnershipForMemoryDump      (uint64 ownerGuid);
		void                     unpin                          ();
		void                     addRef                         ();
		void                     release                        ();

		WGPUTexture object;
	};

	struct ShaderModule
	{
		WGPUFuture getCompilationInfo (WGPUCompilationInfoCallbackInfo callbackInfo);
		void       setLabel           (WGPUStringView label);
		void       setLabel           (const char* label) WGPU_XIN_EXTRA;
		void       addRef             ();
		void       release            ();

		WGPUShaderModule object;
	};

	struct Queue
	{
		void       copyExternalTextureForBrowser (WGPUImageCopyExternalTexture const* source, WGPUTexelCopyTextureInfo const* destination, WGPUExtent3D const* copySize, WGPUCopyTextureForBrowserOptions const* options);
		void       copyTextureForBrowser         (WGPUTexelCopyTextureInfo const* source, WGPUTexelCopyTextureInfo const* destination, WGPUExtent3D const* copySize, WGPUCopyTextureForBrowserOptions const* options);
		WGPUFuture onSubmittedWorkDone           (WGPUQueueWorkDoneCallbackInfo callbackInfo);
		void       setLabel                      (WGPUStringView label);
		void       setLabel                      (const char* label) WGPU_XIN_EXTRA;
		void       submit                        (size_t commandCount, WGPUCommandBuffer const* commands);
		void       writeBuffer                   (WGPUBuffer buffer, uint64_t bufferOffset, void const* data, size_t size);
		void       writeBuffer                   (wgpu::Buffer buffer, uint64_t bufferOffset, void const* data, size_t size) WGPU_XIN_EXTRA;
		void       writeTexture                  (WGPUTexelCopyTextureInfo const* destination, void const* data, size_t dataSize, WGPUTexelCopyBufferLayout const* dataLayout, WGPUExtent3D const* writeSize);
		void       addRef                        ();
		void       release                       ();

		WGPUQueue object;
	};

	struct CommandEncoder
	{
		WGPUComputePassEncoder   beginComputePass      (WGPU_NULLABLE WGPUComputePassDescriptor const* descriptor);
		WGPURenderPassEncoder    beginRenderPass       (WGPURenderPassDescriptor const* descriptor);
		wgpu::RenderPassEncoder  beginRenderPassHelper (WGPURenderPassDescriptor const* descriptor) WGPU_XIN_EXTRA;
		void                     clearBuffer           (WGPUBuffer buffer, uint64_t offset, uint64_t size);
		void                     copyBufferToBuffer    (WGPUBuffer source, uint64_t sourceOffset, WGPUBuffer destination, uint64_t destinationOffset, uint64_t size);
		void                     copyBufferToTexture   (WGPUTexelCopyBufferInfo const* source, WGPUTexelCopyTextureInfo const* destination, WGPUExtent3D const* copySize);
		void                     copyTextureToBuffer   (WGPUTexelCopyTextureInfo const* source, WGPUTexelCopyBufferInfo const* destination, WGPUExtent3D const* copySize);
		void                     copyTextureToTexture  (WGPUTexelCopyTextureInfo const* source, WGPUTexelCopyTextureInfo const* destination, WGPUExtent3D const* copySize);
		WGPUCommandBuffer        finish                (WGPU_NULLABLE WGPUCommandBufferDescriptor const* descriptor);
		wgpu::CommandBuffer      finishHelper          (WGPU_NULLABLE WGPUCommandBufferDescriptor const* descriptor);
		void                     injectValidationError (WGPUStringView message);
		void                     injectDebugMarker     (WGPUStringView markerLabel);
		void                     popDebugGroup         ();
		void                     pushDebugGroup        (WGPUStringView groupLabel);
		void                     resolveQuerySet       (WGPUQuerySet querySet, uint32_t firstQuery, uint32_t queryCount, WGPUBuffer destination, uint64_t destinationOffset);
		void                     setLabel              (WGPUStringView label);
		void                     setLabel              (const char* label) WGPU_XIN_EXTRA;
		void                     setResourceTable      (WGPU_NULLABLE WGPUResourceTable table);
		void                     writeBuffer           (WGPUBuffer buffer, uint64_t bufferOffset, uint8_t const* data, uint64_t size);
		void                     writeTimestamp        (WGPUQuerySet querySet, uint32_t queryIndex);
		void                     addRef                ();
		void                     release               ();

		WGPUCommandEncoder object;
	};

	struct RenderPassEncoder
	{
		void beginOcclusionQuery      (uint32_t queryIndex);
		void draw                     (uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance);
		void drawIndexed              (uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t baseVertex, uint32_t firstInstance);
		void drawIndexedIndirect      (WGPUBuffer indirectBuffer, uint64_t indirectOffset);
		void end                      ();
		void endOcclusionQuery        ();
		void executeBundles           (size_t bundleCount, WGPURenderBundle const* bundles);
		void insertDebugMarker        (WGPUStringView markerLabel);
		void multiDrawIndexedIndirect (WGPUBuffer indirectBuffer, uint64_t indirectOffset, uint32_t maxDrawCount, WGPU_NULLABLE WGPUBuffer drawCountBuffer, uint64_t drawCountBufferOffset);
		void multiDrawIndirect        (WGPUBuffer indirectBuffer, uint64_t indirectOffset, uint32_t maxDrawCount, WGPU_NULLABLE WGPUBuffer drawCountBuffer, uint64_t drawCountBufferOffset);
		void pixelLocalStorageBarrier ();
		void popDebugGroup            ();
		void pushDebugGroup           (WGPUStringView groupLabel);
		void setBindGroup             (uint32_t groupIndex, WGPU_NULLABLE WGPUBindGroup group, size_t dynamicOffsetCount, uint32_t const* dynamicOffsets);
		void setBindGroup             (uint32_t groupIndex, wgpu::BindGroup group, size_t dynamicOffsetCount, uint32_t const* dynamicOffsets) WGPU_XIN_EXTRA;
		void setBlendConstant         (WGPUColor const* color);
		void setImmediates            (uint32_t offset, void const* data, size_t size);
		void setIndexBuffer           (WGPUBuffer buffer, WGPUIndexFormat format, uint64_t offset, uint64_t size);
		void setIndexBuffer           (wgpu::Buffer buffer, WGPUIndexFormat format, uint64_t offset, uint64_t size) WGPU_XIN_EXTRA;
		void setLabel                 (WGPUStringView label);
		void setLabel                 (const char* label) WGPU_XIN_EXTRA;
		void setPipeline              (WGPURenderPipeline pipeline);
		void setPipeline              (wgpu::RenderPipeline pipeline) WGPU_XIN_EXTRA;
		void setScissorRect           (uint32_t x, uint32_t y, uint32_t width, uint32_t height);
		void setStencilReference      (uint32_t reference);
		void setVertexBuffer          (uint32_t slot, WGPU_NULLABLE WGPUBuffer buffer, uint64_t offset, uint64_t size);
		void setVertexBuffer          (uint32_t slot, wgpu::Buffer buffer, uint64_t offset, uint64_t size) WGPU_XIN_EXTRA;
		void setViewport              (float x, float y, float width, float height, float minDepth, float maxDepth);
		void writeTimestamp           (WGPUQuerySet querySet, uint32_t queryIndex);
		void addRef                   ();
		void release                  ();

		WGPURenderPassEncoder object;
	};

	struct RenderPipeline
	{
		WGPUBindGroupLayout getBindGroupLayout (uint32_t groupIndex);
		void                setLabel           (WGPUStringView label);
		void                setLabel           (const char* label) WGPU_XIN_EXTRA;
		void                addRef             ();
		void                release            ();

		WGPURenderPipeline object;
	};

	struct Buffer
	{
		WGPUTexelBufferView createTexelView     (WGPUTexelBufferViewDescriptor const* descriptor);
		void                destroy             ();
		void const*         getConstMappedRange (size_t offset, size_t size);
		void*               getMappedRange      (size_t offset, size_t size);
		WGPUBufferMapState  getMapState         ();
		uint64              getSize             ();
		WGPUBufferUsage     getUsage            ();
		WGPUFuture          mapAsync            (WGPUMapMode mode, size_t offset, size_t size, WGPUBufferMapCallbackInfo callbackInfo);
		WGPUStatus          readMappedRange     (size_t offset, void* data, size_t size);
		void                setLabel            (WGPUStringView label);
		void                setLabel            (const char* label) WGPU_XIN_EXTRA;
		void                unmap               ();
		WGPUStatus          writeMappedRange    (size_t offset, void const* data, size_t size);
		void                addRef              ();
		void                release             ();

		WGPUBuffer object;
	};

	struct BindGroupLayout
	{
		void setLabel (WGPUStringView label);
		void setLabel (const char* label) WGPU_XIN_EXTRA;
		void addRef   ();
		void release  ();

		WGPUBindGroupLayout object;
	};

	struct PipelineLayout
	{
		void setLabel (WGPUStringView label);
		void setLabel (const char* label) WGPU_XIN_EXTRA;
		void addRef   ();
		void release  ();

		WGPUPipelineLayout object;
	};

	struct BindGroup
	{
		void setLabel (WGPUStringView label);
		void setLabel (const char* label) WGPU_XIN_EXTRA;
		void addRef   ();
		void release  ();

		WGPUBindGroup object;
	};

	struct TextureView
	{
		void setLabel (WGPUStringView label);
		void setLabel (const char* label) WGPU_XIN_EXTRA;
		void addRef   ();
		void release  ();

		WGPUTextureView object;
	};

	struct CommandBuffer
	{
		void setLabel (WGPUStringView label);
		void setLabel (const char* label) WGPU_XIN_EXTRA;
		void addRef   ();
		void release  ();

		WGPUCommandBuffer object;
	};
}




namespace CharUtil
{
	bool IsSpace         (char c);
	bool IsDigit         (char c);
	bool IsArithmeticSign(char c);
	bool IsNewline       (char c);
	bool IsTab           (char c);
	bool IsDot           (char c);
}

namespace OBJParser
{
	struct Vec3LineResult
	{
		Vec3        vector;
		const char* reader;
	};

	struct Vec3ILineResult
	{
		Vec3I vector;
		const char* reader;
	};

	struct OBJFileResult
	{

	};

	Vec3LineResult parseVec3Line(FileReader& fileReader);
	Vec3ILineResult parseFaceLine(FileReader& fileReader);
}


void						    Win32_WGPU_GetDefaultBindingLayout(WGPUBindGroupLayoutEntry& bindingLayout);
uint32                          Win32_WGPU_Util_CeilToNextMultiple(uint32 Value, uint32 Multiple);
void                            Win32_WGPU_Util_Initialize();

WGPUDeviceLostCallbackInfo      Win32_WGPU_Callback_DeviceLost();
WGPUUncapturedErrorCallbackInfo Win32_WGPU_Callback_UncapturedError();


const char*                     Win32_Util_Stringify_WGPUDeviceLostReason(WGPUDeviceLostReason Reason);
const char*                     Win32_Util_Stringify_WGPUErrorType(WGPUErrorType Err);
ReadFileResult                  Win32_Util_ReadFile(const char* Filename, GameMemory* Memory);
MeshAsset                       Win32_Util_ReadFile_OBJ(const char* Filename, GameMemory* Memory);
uint32                          Win32_Util_SafeTruncate_uin64(uint64 Value);
char*                           Win32_Util_AllocateReadFileMemory(GameMemory* Memory, size_t Size);
real32                          Win32_Util_ConvertStringToFloat(const char* String, uint8 Size);
real32                          Win32_Util_ConvertStringToFloat(const String& String);
int                             Win32_Util_ConvertStringToInt(const char* String, uint8 Size);
int                             Win32_Util_ConvertStringToInt(const String& String);
uint8                           Win32_Util_ConvertCharToDigit(char Char);

void                            Win32_ProcessPendingMessages();


enum DataType
{
	INTEGER = 0, 
	REAL32,
};

struct ParseNumberResult
{
	union
	{
		int i;
		real32 r32;
	} number;

	bool valid;
};
ParseNumberResult Win32_Util_ParseNumber(const char* reader, DataType dataType, char endChar);
