#pragma once

enum AssetType
{
	SHADER_CODE = 0, 
	MESH = 1
};


const char*                     Win32_Util_Stringify_WGPUDeviceLostReason(WGPUDeviceLostReason Reason);
const char*                     Win32_Util_Stringify_WGPUErrorType(WGPUErrorType Err);
uint32                          Win32_Util_SafeTruncate_uin64(uint64 Value);
char*                           Win32_Util_AllocateReadFileMemory(GameMemory* Memory, size_t Size);

void                            Win32_ProcessPendingMessages();
