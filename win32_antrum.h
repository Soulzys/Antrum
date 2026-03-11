#pragma once

#include "include/webgpu.h"
#include "windows.h"
#include <stdint.h>


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


#define STRING_MAX_LENGTH 10000
#define WINDOW_WIDTH      1200
#define WINDOW_HEIGHT     800
#define MEMSIZE_GAME      MEGABYTES(64)
#define MEMSIZE_IO		  MEGABYTES(4)

struct WGPUMaster
{
	WGPUInstance        instance;
	WGPUAdapter         adapter;
	WGPUDevice          device;
	WGPUSurface         surface;
	WGPUTextureFormat   surfaceFormat;
	WGPUShaderModule    shaderModule;
	WGPUBindGroupLayout bindGroupLayout;
	WGPURenderPipeline  renderPipeline;
	WGPUQueue           queue;
};

struct GameMemory
{
	struct
	{
		uint64 size;
		uint64 offset;
		char*  memory;
	} IOMemory;

	uint64 size;
	uint64 offset;
	char*  memory;
};

struct ReadFileResult
{
	uint32      contentSize;
	void*       content;
	const char* message;
};



void                            Win32_WGPU_GetInstance(WGPUInstance& OutInstance);
void                            Win32_WGPU_GetAdapter(WGPUInstance Instance, WGPUAdapter& OutAdapter);
void                            Win32_WGPU_GetDevice(WGPUAdapter Adapter, WGPUDevice& OutDevice);
void                            Win32_WGPU_GetSurface(WNDCLASS* WndClass, HWND WndHandle, WGPUInstance Instance, WGPUSurface& OutSurface);
void                            Win32_WGPU_GetSurfaceFormat(WGPUSurface Surface, WGPUAdapter Adapter, WGPUTextureFormat& OutSurfaceFormat);
void                            Win32_WGPU_GetShaderModule(WGPUDevice Device, WGPUShaderModule& OutShaderModule, GameMemory* Memory);
void                            Win32_WGPU_GetBindGroupLayout(WGPUDevice Device, WGPUBindGroupLayout& BindGroupLayout);
void                            Win32_WGPU_GetRenderPipeline(WGPUDevice Device, WGPUShaderModule ShaderModule, WGPUTextureFormat SurfaceFormat, WGPUBindGroupLayout bindGroupLayout, WGPURenderPipeline& OutRenderPipeline);
void						    Win32_WGPU_GetDefaultBindingLayout(WGPUBindGroupLayoutEntry& bindingLayout);

WGPUAdapter                     Win32_WGPU_Sync_RequestAdapter(WGPUInstance Instance, WGPURequestAdapterOptions const* Options);
WGPUDevice                      Win32_WGPU_Sync_RequestDevice(WGPUAdapter Adapter, const WGPUDeviceDescriptor* Descriptor);

WGPUDeviceLostCallbackInfo      Win32_WGPU_Callback_DeviceLost();
WGPUUncapturedErrorCallbackInfo Win32_WGPU_Callback_UncapturedError();


WGPULimits                      Win32_WGPU_GetLimits(WGPUAdapter Adapter);
void                            Win32_WGPU_ConfigureSurface(WGPUSurface Surface, WGPUTextureFormat SurfaceFormat, WGPUDevice Device, WGPUAdapter Adapter);
WGPUTextureView                 Win32_WGPU_GetNextSurfaceTextureView(WGPUSurface Surface);

const char*                     Win32_Util_Stringify_WGPUDeviceLostReason(WGPUDeviceLostReason Reason);
const char*                     Win32_Util_Stringify_WGPUErrorType(WGPUErrorType Err);
size_t                          Win32_Util_StringSize(const char* Str);
ReadFileResult                  Win32_Util_ReadFile(const char* Filename, GameMemory* Memory);
uint32                          Win32_Util_SafeTruncate_uin64(uint64 Value);
char*                           Win32_Util_AllocateIOMemory(GameMemory* Memory, size_t Size);



void                            Win32_ProcessPendingMessages();
