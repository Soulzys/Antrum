#pragma once



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
