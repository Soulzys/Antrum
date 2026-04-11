#pragma once

#include "include/webgpu.h"
#include "windows.h"
#include <stdint.h>



/* 
	# TODO
	~~~~~~

	Start from the most basic data brick before climbing up.

	1. For parsing, using arrays of real32 and uint16 directly, not Vec3 / Vec3I.
	   It is always easier to go from real32 to Vec3 than the opposite.
	   We need to feed an array of real32 to the GPU anyway.

	2. Refactors the parsing function properly (esp the 'v') function

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

struct WGPUMaster
{
	WGPUInstance        instance;
	WGPUAdapter         adapter;
	WGPUDevice          device;
	WGPUSurface         surface;
	WGPUTextureFormat   surfaceFormat;
	WGPUShaderModule    shaderModule;
	WGPUPipelineLayout  pipelineLayout;
	WGPUBindGroupLayout bindGroupLayout;
	WGPUBindGroup       bindGroup;
	WGPURenderPipeline  renderPipeline;
	WGPUQueue           queue;
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


namespace WGPU
{
	struct Device
	{
		WGPUShaderModule createShaderModule(WGPUShaderModuleDescriptor const* descriptor);
		WGPUBindGroupLayout createBindGroupLayout(WGPUBindGroupLayoutDescriptor const* descriptor);
		WGPUPipelineLayout createPipelineLayout(WGPUPipelineLayoutDescriptor const* descriptor);
		WGPURenderPipeline createRenderPipeline(WGPURenderPipelineDescriptor const* descriptor);
		WGPUQueue getQueue();
		WGPUBuffer createBuffer(WGPUBufferDescriptor const* descriptor);
		WGPUBindGroup createBindGroup(WGPUBindGroupDescriptor const* descriptor);
		WGPUCommandEncoder createCommandEncoder(WGPU_NULLABLE WGPUCommandEncoderDescriptor const* descriptor);
		void tick();

		WGPUDevice device;
	};

	struct Adapter
	{
		WGPUFuture requestDevice (WGPU_NULLABLE WGPUDeviceDescriptor const* descriptor, WGPURequestDeviceCallbackInfo callbackInfo);
		WGPUStatus getLimits     (WGPULimits* limits);
		void release();

		WGPUAdapter adapter;
	};

	struct Instance
	{
		WGPUFuture requestAdapter(WGPU_NULLABLE WGPURequestAdapterOptions const* options, WGPURequestAdapterCallbackInfo callbackInfo);
		WGPUSurface createSurface(WGPUSurfaceDescriptor const* descriptor);

		WGPUInstance instance;
	};

	struct Surface
	{
		WGPUStatus getCapabilities(WGPUAdapter adapter, WGPUSurfaceCapabilities* capabilities);
		void configure(WGPUSurfaceConfiguration const* config);
		void getCurrentTexture(WGPUSurfaceTexture* surfaceTexture);
		WGPUStatus present();

		WGPUSurface surface;
	};

	struct Texture
	{
		WGPUTextureFormat getFormat();
		WGPUTextureView createView(WGPU_NULLABLE WGPUTextureViewDescriptor const* descriptor);
		void release();

		WGPUTexture texture;
	};

	struct ShaderModule
	{
		void release();

		WGPUShaderModule shaderModule;
	};

	struct Queue
	{
		void writeBuffer(WGPUBuffer buffer, uint64_t bufferOffset, void const* data, size_t size);
		void submit(size_t commandCount, WGPUCommandBuffer const* commands);

		WGPUQueue queue;
	};

	struct CommandEncoder
	{
		WGPURenderPassEncoder beginRenderPass(WGPURenderPassDescriptor const* descriptor);
		WGPUCommandBuffer finish(WGPU_NULLABLE WGPUCommandBufferDescriptor const* descriptor);
		void release();

		WGPUCommandEncoder commandEncoder;
	};

	struct RenderPassEncoder
	{
		void setPipeline(WGPURenderPipeline pipeline);
		void setVertexBuffer(uint32_t slot, WGPU_NULLABLE WGPUBuffer buffer, uint64_t offset, uint64_t size);
		void setIndexBuffer(WGPUBuffer buffer, WGPUIndexFormat format, uint64_t offset, uint64_t size);
		void setBindGroup(uint32_t groupIndex, WGPU_NULLABLE WGPUBindGroup group, size_t dynamicOffsetCount, uint32_t const* dynamicOffsets);
		void drawIndexed(uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t baseVertex, uint32_t firstInstance);
		void end();
		void release();

		WGPURenderPassEncoder renderPassEncoder;
	};

	Instance createInstance(WGPU_NULLABLE WGPUInstanceDescriptor const* descriptor);
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


void                            Win32_WGPU_GetInstance(WGPUInstance& OutInstance);
void                            Win32_WGPU_GetAdapter(WGPUInstance Instance, WGPUAdapter& OutAdapter);
void                            Win32_WGPU_GetDevice(WGPUAdapter Adapter, WGPUDevice& OutDevice);
void                            Win32_WGPU_GetSurface(WNDCLASS* WndClass, HWND WndHandle, WGPUInstance Instance, WGPUSurface& OutSurface);
void                            Win32_WGPU_GetSurfaceFormat(WGPUSurface Surface, WGPUAdapter Adapter, WGPUTextureFormat& OutSurfaceFormat);
void                            Win32_WGPU_GetShaderModule(WGPUDevice Device, WGPUShaderModule& OutShaderModule, GameMemory* Memory);
void                            Win32_WGPU_GetPipelineLayout(WGPUDevice Device, WGPUBindGroupLayout BindGroupLayout, WGPUPipelineLayout& PipelineLayout);
void                            Win32_WGPU_GetBindGroupLayout(WGPUDevice Device, WGPUBindGroupLayout& BindGroupLayout);
void                            Win32_WGPU_GetRenderPipeline(WGPUDevice Device, WGPUShaderModule ShaderModule, WGPUTextureFormat SurfaceFormat, WGPUBindGroupLayout BindGroupLayout, WGPUPipelineLayout PipelineLayout, WGPURenderPipeline& OutRenderPipeline);
void						    Win32_WGPU_GetDefaultBindingLayout(WGPUBindGroupLayoutEntry& bindingLayout);
uint32                          Win32_WGPU_Util_CeilToNextMultiple(uint32 Value, uint32 Multiple);

WGPUAdapter                     Win32_WGPU_Sync_RequestAdapter(WGPUInstance Instance, WGPURequestAdapterOptions const* Options);
WGPUDevice                      Win32_WGPU_Sync_RequestDevice(WGPUAdapter Adapter, const WGPUDeviceDescriptor* Descriptor);

WGPUDeviceLostCallbackInfo      Win32_WGPU_Callback_DeviceLost();
WGPUUncapturedErrorCallbackInfo Win32_WGPU_Callback_UncapturedError();


WGPULimits                      Win32_WGPU_GetDefaultLimits(WGPUAdapter Adapter);
void                            Win32_WGPU_ConfigureSurface(WGPUSurface Surface, WGPUTextureFormat SurfaceFormat, WGPUDevice Device, WGPUAdapter Adapter);
WGPUTextureView                 Win32_WGPU_GetNextSurfaceTextureView(WGPUSurface Surface);

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
