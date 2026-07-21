#pragma once

#include <stdint.h>
#include "meshes_macro.h"

/*
	# TODO
	~~~~~~

	1. Move to 3D
	2. Add inputs
	3. Profit

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


#define KILOBYTES(Value) ((Value)          * 1024LL)
#define MEGABYTES(Value) (KILOBYTES(Value) * 1024LL)
#define GIGABYTES(Value) (MEGABYTES(Value) * 1024LL)

#define ASSERT(Expression) if (!(Expression)) {*(int*)0 = 0;}











#define STRING_MAX_LENGTH 10000
#define WINDOW_WIDTH      1200
#define WINDOW_HEIGHT     800
#define MEMSIZE_GAME      MEGABYTES(64)
#define MEMSIZE_READ_FILE MEGABYTES(4)
#define MEMSIZE_ASSETS    MEGABYTES(12)
#define ASSET_MAX_POINTS  3000

#define XIN_FILE__CLOSE_CHAR 'x'
#define XIN_FILE__INDICE_CHAR 'I'




constexpr float PI = 3.14159265358979323846f;



struct MemoryChunk
{
	void* allocate(size_t amount);

	uint64 size;
	uint64 offset;
	char* memory;
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

struct GameState
{
	bool initialized;
	bool quit;
};

template<typename T>
struct Vec3
{
	T x;
	T y;
	T z;
};

template<typename T>
struct Vec2
{
	T x;
	T y;
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
		ASSERT(m_index < N);
		
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

private:
	T m_arr[N];
	size_t m_index = 0;
};

struct Vertex
{
	Vec3<real32> position;
	Vec3<real32> normal;
	Vec2<real32> uv;
};

struct MeshAsset
{
	Vector<Vertex, ASSET_MAX_POINTS> vertices;
	Vector<uint32, ASSET_MAX_POINTS> indices;
};

struct MeshAsset2
{
	Vector<real32, ASSET_MAX_POINTS> vertices;
	Vector<real32, ASSET_MAX_POINTS> normals;
	Vector<uint16, ASSET_MAX_POINTS> indexes; // >TODO: find a more efficient way to calculate the minimum amount of indexes
};


// Platform-specific structs & functions
//
struct ReadFileResult
{
	uint32      contentSize;
	void*       content;
	const char* message;
};

#define PLATFORM_READ_FILE(name) ReadFileResult name(const char* filename, GameMemory* memory)
typedef PLATFORM_READ_FILE(read_file);

#define PLATFORM_LOG(name) void name(const char* message)
typedef PLATFORM_LOG(flog);


struct PlatformFunctions
{
	read_file* readFile;
	flog* log;
};



//struct Vec3I
//{
//	uint16 a;
//	uint16 b;
//	uint16 c;
//};

struct M4
{
	static M4 identity ();
	static M4 translate(real32 x, real32 y, real32 z);
	static M4 scale    (real32 x, real32 y, real32 z);
	static M4 scale    (real32 v);
	static M4 rotateX  (real32 a);
	static M4 rotateY  (real32 a);
	static M4 rotateZ  (real32 a);

	real32*       operator[](uint8 i);
	const real32* operator[](uint8 i) const;
	M4            operator* (const M4& n);
	M4&           operator*=(const M4& n);

	real32 m[4][4] = {
	                     {1.0f, 0.0f, 0.0f, 0.0f}, 
	                     {0.0f, 1.0f, 0.0f, 0.0f}, 
	                     {0.0f, 0.0f, 1.0f, 0.0f}, 
	                     {0.0f, 0.0f, 0.0f, 1.0f}, 
	                 };
};



struct String
{
	const char* head;
	size_t size;
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

namespace XinParser
{
	Vertex parseVertexLine(const String& line);
}

namespace OBJParser
{
	template<typename T>
	struct LineResult
	{
		Vec3<T>     vector;
		const char* reader;
	};

	struct OBJFileResult
	{

	};

	LineResult<real32> parseVerticesLine(FileReader& fileReader);
	LineResult<uint16> parseFaceLine    (FileReader& fileReader);
}

namespace CharUtil
{
	bool  IsSpace         (char c);
	bool  IsDigit         (char c);
	bool  IsArithmeticSign(char c);
	bool  IsNewline       (char c);
	bool  IsTab           (char c);
	bool  IsDot           (char c);
	uint8 ToDigit         (char c);
}

namespace StringUtil
{
	real32 ToFloat(const char* string, uint8 size);
	real32 ToFloat(const String& string);
	int    ToInt(const char* string, uint8 size);
	int    ToInt(const String& string);
}


struct AssetManager
{
	Vector<MeshAsset*, 1> meshAssets;
};

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
ParseNumberResult ParseNumber(const char* reader, DataType dataType, char endChar);


struct ShaderUniform
{
	// When dealing with uniform offset, the formula is that for each struct member, its offset has to be a multiple of: offset * sizeof(memberType);
	M4 projectionMatrix;
	M4 viewMatrix;
	M4 modelMatrix;
	real32 color[4]; // offset = 0 * sizeof(vec4f) --> OK, 0 is a multiple of 16
	real32 time; // offset = 16 = 4 * sizeof(f32) --> OK, 16 is a multiple of 16

	// Makes it host-shareable by adding padding at the end of the struct so its total size if a multiple of its largest bit-field (here, a multiple of 16,
	// as its total size would then be 32 bytes).
	real32 __padding[3];
};
static_assert(sizeof(ShaderUniform) % sizeof(ShaderUniform::color) == 0);


#include "wgpu_layer.cpp"

struct WebGPUStorage
{
	wgpu::Instance instance;
	wgpu::Adapter adapter;
	wgpu::Device device;
	wgpu::Surface surface;
	wgpu::ShaderModule shaderModule;
	wgpu::BindGroupLayout bindGroupLayout;
	wgpu::PipelineLayout pipelineLayout;
	wgpu::RenderPipeline renderPipeline;
	wgpu::Queue queue;

	wgpu::Buffer pointBuffer;
	wgpu::Buffer normalBuffer;
	wgpu::Buffer indexBuffer;
	wgpu::Buffer uniformBuffer;

	wgpu::Texture depthTexture;
	wgpu::TextureView depthTextureView;

	wgpu::BindGroup bindGroup;


	ShaderUniform shaderUniform;
};



void InitializeWebGPU(WebGPUStorage* storage, void* wndHandle, void* hInstance, GameMemory* memory, MeshAsset* asset, PlatformFunctions* platformFunctions);


// Used to display the arguments of the macroed functions
#if !defined(XARG)
#define XARGS(arg)
#endif


#define GAME_INITIALIZE(name) void name  \
(                                        \
	GameMemory* memory,                  \
	GameState* gameState,                \
	PlatformFunctions* platformFunctions,\
	MeshAsset* asset,                    \
	WebGPUStorage* wgpuStorage,          \
	void* wndHandle,                     \
    void* hInstance                      \
)                                        \

typedef GAME_INITIALIZE(game_initialize);

#define GAME_UPDATE(name) void name(GameMemory* memory, GameState* gameState, PlatformFunctions* platformFunctions, WebGPUStorage* wgpuStorage, MeshAsset* asset)
typedef GAME_UPDATE(game_update);

#define GAME_QUIT(name) void name(WebGPUStorage* storage)
typedef GAME_QUIT(game_quit);




