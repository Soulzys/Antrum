#pragma once

uint32 Win32_Util_SafeTruncate_uin64(uint64 Value);
char*  Win32_Util_AllocateReadFileMemory(GameMemory* Memory, size_t Size);

void   Win32_ProcessPendingMessages(GameState* gameState);
