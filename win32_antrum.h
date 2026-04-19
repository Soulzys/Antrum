#pragma once



enum AssetType
{
	SHADER_CODE = 0, 
	MESH = 1
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



void						    Win32_WGPU_GetDefaultBindingLayout(WGPUBindGroupLayoutEntry& bindingLayout);
uint32                          Win32_WGPU_Util_CeilToNextMultiple(uint32 Value, uint32 Multiple);
void                            Win32_WGPU_Util_Initialize();

WGPUDeviceLostCallbackInfo      Win32_WGPU_Callback_DeviceLost();
WGPUUncapturedErrorCallbackInfo Win32_WGPU_Callback_UncapturedError();


const char*                     Win32_Util_Stringify_WGPUDeviceLostReason(WGPUDeviceLostReason Reason);
const char*                     Win32_Util_Stringify_WGPUErrorType(WGPUErrorType Err);
uint32                          Win32_Util_SafeTruncate_uin64(uint64 Value);
char*                           Win32_Util_AllocateReadFileMemory(GameMemory* Memory, size_t Size);

void                            Win32_ProcessPendingMessages();


