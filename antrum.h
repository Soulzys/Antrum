#pragma once

#include <stdint.h>

/*
	# TODO
	~~~~~~

	1. Create game layer
	2. Move to 3D
	3. Add inputs
	4. Profit

*/



typedef int8_t   int8;
typedef int16_t  int16;
typedef int32_t  int32;
typedef int64_t  int64;
typedef uint8_t  uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

typedef float    real32;
typedef double   real64;

typedef int32    bool32;

#include "wgpu_layer.cpp"



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



// Platform-specific structs & functions
//
//struct ReadFileResult
//{
//	uint32      contentSize;
//	void*       content;
//	const char* message;
//};
//
//#define PLATFORM_READ_FILE(name) ReadFileResult name(const char* fileName, GameMemory* memory)
//typedef PLATFORM_READ_FILE(platform_read_file);


//struct PlatformStorage
//{
//	platform_read_file* readFile;
//};


#define GAME_UPDATE_AND_RENDER(name) void name()
typedef GAME_UPDATE_AND_RENDER(game_update_and_render);