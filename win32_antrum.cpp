#include "antrum.h"

#include "windows.h"
#include "win32_antrum.h"

#include <vector>



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

XARGS(const char* filename, GameMemory* memory)
PLATFORM_READ_FILE(ReadFile)
{
	ReadFileResult res = {};

	HANDLE fileHandle = CreateFile(filename, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0);
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
	res.content = Win32_Util_AllocateReadFileMemory(memory, fileSize32);
	if (!res.content)
	{
		res.message = "ERROR | Win32_Util_ReadFile() | Your file is too big !\n";
		return res;
	}

	DWORD bytesRead;
	if (!ReadFile(fileHandle, res.content, fileSize32, &bytesRead, 0))
	{
		res.message = "ERROR | Win32_Util_ReadFile() | Could not read the file !\n";
		memory->readFileChunk.offset -= fileSize32; // Deallocate
		return res;
	}
	if (bytesRead != fileSize32)
	{
		res.message = "ERROR | Win32_Util_ReadFile() | We did not read all of the bytes we expected !\n";
		memory->readFileChunk.offset -= fileSize32; // Deallocate
		return res;
	}

	res.contentSize = fileSize32;

	// Deallocate
	//Memory->ReadFileMemory.offset = 0;
	//Memory->ReadFileMemory.memory = nullptr;

	CloseHandle(fileHandle);

	return res;
}

XARGS(const char* message)
PLATFORM_LOG(FLog)
{
	OutputDebugString(message);
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


void Win32_ProcessPendingMessages(GameState* gameState)
{
	MSG msg = {};
	while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
	{
		switch (msg.message)
		{
			case WM_QUIT:
			{
				gameState->quit = true;
			} break;

			case WM_SYSKEYDOWN:
			case WM_SYSKEYUP:
			case WM_KEYDOWN:
			case WM_KEYUP:
			{
				uint32 vkCode = (uint32)msg.wParam;
				if (vkCode == 'A') OutputDebugString("A KEY PRESSED !\n");
				if (vkCode == 'D') OutputDebugString("D KEY PRESSED !\n");
				if (vkCode == VK_ESCAPE) gameState->quit = true;
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

	if (Message == WM_NCCREATE)
	{
		CREATESTRUCT* cs = (CREATESTRUCT*)LParam;
		GameState* gameState = (GameState*)cs->lpCreateParams;
		SetWindowLongPtr(Window, GWLP_USERDATA, (LONG_PTR)gameState);
	}

	switch (Message)
	{
		case WM_DESTROY:
		case WM_CLOSE:
		{
			GameState* gameState = (GameState*)(GetWindowLongPtr(Window, GWLP_USERDATA));
			gameState->quit = true;
		} break;
		default:
		{
			result = DefWindowProc(Window, Message, WParam, LParam);
		} break;
	}

	return result;
}

struct Win32GameDLL
{
	HMODULE          DLL;
	game_update*     update;
	game_initialize* initialize;
	game_quit*       quit;
};

Win32GameDLL Win32_LoadGameDLL()
{
	Win32GameDLL game = {};
	game.DLL = LoadLibrary("antrum.dll");
	ASSERT(game.DLL)

	game.update = (game_update*)(GetProcAddress(game.DLL, "Game_Update"));
	ASSERT(game.update);

	game.initialize = (game_initialize*)(GetProcAddress(game.DLL, "Game_Initialize"));
	ASSERT(game.initialize);

	game.quit = (game_quit*)(GetProcAddress(game.DLL, "Game_Quit"));
	ASSERT(game.quit);

	return game;
}

int CALLBACK WinMain(HINSTANCE Instance, HINSTANCE PrevInstance, LPSTR CmdLine, int CmdShow)
{
	Win32GameDLL gameDLL = Win32_LoadGameDLL();	

	WNDCLASS wndClass      = {};
	wndClass.style         = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	wndClass.hInstance     = Instance;
	wndClass.lpfnWndProc   = Win32_MainWindowCallback;
	wndClass.lpszClassName = "Antrum";

	bool32 success = RegisterClass(&wndClass);
	if (!success) return 0;



	GameState gameState = {};

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
		&gameState
	);

	GameMemory gameMemory           = {};
	gameMemory.fattyChunk.size      = MEMSIZE_GAME;
	gameMemory.fattyChunk.memory    = static_cast<char*>(VirtualAlloc(0, gameMemory.fattyChunk.size, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE));
	gameMemory.readFileChunk.size   = MEMSIZE_READ_FILE;
	gameMemory.readFileChunk.memory = gameMemory.fattyChunk.memory;
	gameMemory.assetsChunk.size     = MEMSIZE_ASSETS;
	gameMemory.assetsChunk.memory   = gameMemory.readFileChunk.memory + gameMemory.readFileChunk.size;


	PlatformFunctions platformFunctions = {};
	platformFunctions.readFile = ReadFile;
	platformFunctions.log = FLog;



	AssetManager assetManager = {};
	MeshAsset asset = {};
	WebGPUStorage webGPUStorage = {};


	gameDLL.initialize(&gameMemory, &gameState, &platformFunctions, &asset, &webGPUStorage, wndHandle, wndClass.hInstance);

	while (!gameState.quit)
	{
		Win32_ProcessPendingMessages(&gameState);

		gameDLL.update(&gameMemory, &gameState, &platformFunctions, &webGPUStorage, &asset);
	}

	gameDLL.quit(&webGPUStorage);

	return 0;
}
