#include "antrum.h"

bool CharUtil::IsDigit(char c)
{
	int cInt = (int)c;
	return (cInt >= 48 && cInt <= 57);
}

bool CharUtil::IsNewline(char c)
{
	return c == '\n';
}

bool CharUtil::IsTab(char c)
{
	return c == '\t';
}

bool CharUtil::IsSpace(char c)
{
	return c == ' ';
}

bool CharUtil::IsArithmeticSign(char c)
{
	return (c == '+' || c == '-' || c == '/' || c == '*');
}

bool CharUtil::IsDot(char c)
{
	return c == '.';
}

uint8 CharUtil::ToDigit(char c)
{
	return uint8(c - '0');
}


M4 M4::identity()
{
	M4 o = {};
	o.m[0][0] = 1.0f; o.m[0][1] = 0.0f; o.m[0][2] = 0.0f; o.m[0][3] = 0.0f;
	o.m[1][0] = 0.0f; o.m[1][1] = 1.0f; o.m[1][2] = 0.0f; o.m[1][3] = 0.0f;
	o.m[2][0] = 0.0f; o.m[2][1] = 0.0f; o.m[2][2] = 1.0f; o.m[2][3] = 0.0f;
	o.m[3][0] = 0.0f; o.m[3][1] = 0.0f; o.m[3][2] = 0.0f; o.m[3][3] = 1.0f;

	return o;
}

M4 M4::translate(real32 x, real32 y, real32 z)
{
	M4 o = {};
	o.m[0][0] = 1.0f; o.m[0][1] = 0.0f; o.m[0][2] = 0.0f; o.m[0][3] = 0.0f;
	o.m[1][0] = 0.0f; o.m[1][1] = 1.0f; o.m[1][2] = 0.0f; o.m[1][3] = 0.0f;
	o.m[2][0] = 0.0f; o.m[2][1] = 0.0f; o.m[2][2] = 1.0f; o.m[2][3] = 0.0f;
	o.m[3][0] =    x; o.m[3][1] =    z; o.m[3][2] =   -y; o.m[3][3] = 1.0f;

	return o;
}

M4 M4::scale(real32 x, real32 y, real32 z)
{
	M4 o = {};
	o.m[0][0] =    x; o.m[0][1] = 0.0f; o.m[0][2] = 0.0f; o.m[0][3] = 0.0f;
	o.m[1][0] = 0.0f; o.m[1][1] =    y; o.m[1][2] = 0.0f; o.m[1][3] = 0.0f;
	o.m[2][0] = 0.0f; o.m[2][1] = 0.0f; o.m[2][2] =    z; o.m[2][3] = 0.0f;
	o.m[3][0] = 0.0f; o.m[3][1] = 0.0f; o.m[3][2] = 0.0f; o.m[3][3] = 1.0f;

	return o;
}

M4 M4::scale(real32 v)
{
	M4 o = {};
	o.m[0][0] =    v; o.m[0][1] = 0.0f; o.m[0][2] = 0.0f; o.m[0][3] = 0.0f;
	o.m[1][0] = 0.0f; o.m[1][1] =    v; o.m[1][2] = 0.0f; o.m[1][3] = 0.0f;
	o.m[2][0] = 0.0f; o.m[2][1] = 0.0f; o.m[2][2] =    v; o.m[2][3] = 0.0f;
	o.m[3][0] = 0.0f; o.m[3][1] = 0.0f; o.m[3][2] = 0.0f; o.m[3][3] = 1.0f;

	return o;
}

M4 M4::rotateX(real32 a)
{
	a *= PI * 1.0f / 180.0f;

	M4 o = {};
	o.m[0][0] = 1.0f; o.m[0][1] =             0.0f; o.m[0][2] =              0.0f; o.m[0][3] = 0.0f;
	o.m[1][0] = 0.0f; o.m[1][1] =   (real32)cos(a); o.m[1][2] = (real32)(-sin(a)); o.m[1][3] = 0.0f;
	o.m[2][0] = 0.0f; o.m[2][1] = (real32)(sin(a)); o.m[2][2] =    (real32)cos(a); o.m[2][3] = 0.0f;
	o.m[3][0] = 0.0f; o.m[3][1] =             0.0f; o.m[3][2] =              0.0f; o.m[3][3] = 1.0f;

	return o;
}

M4 M4::rotateY(real32 a)
{
	a *= PI * 1.0f / 180.0f; // -1 is to align with Blender

	// Z rotation matrix. We set it to Y to have our Z up.
	M4 o = {};
	o.m[0][0] =   (real32)cos(a); o.m[0][1] = (real32)(-sin(a)); o.m[0][2] = 0.0f; o.m[0][3] = 0.0f;
	o.m[1][0] = (real32)(sin(a)); o.m[1][1] =    (real32)cos(a); o.m[1][2] = 0.0f; o.m[1][3] = 0.0f;
	o.m[2][0] =             0.0f; o.m[2][1] =              0.0f; o.m[2][2] = 1.0f; o.m[2][3] = 0.0f;
	o.m[3][0] =             0.0f; o.m[3][1] =              0.0f; o.m[3][2] = 0.0f; o.m[3][3] = 1.0f;
	
	return o;
}

M4 M4::rotateZ(real32 a)
{
	a *= PI * 1.0f / 180.0f;

	// Y rotation matrix. We set it to Z to have our Y forward.
	M4 o = {};
	o.m[0][0] =    (real32)cos(a); o.m[0][1] = 0.0f; o.m[0][2] = (real32)(sin(a)); o.m[0][3] = 0.0f;
	o.m[1][0] =              0.0f; o.m[1][1] = 1.0f; o.m[1][2] =             0.0f; o.m[1][3] = 0.0f;
	o.m[2][0] = (real32)(-sin(a)); o.m[2][1] = 0.0f; o.m[2][2] =   (real32)cos(a); o.m[2][3] = 0.0f;
	o.m[3][0] =              0.0f; o.m[3][1] = 0.0f; o.m[3][2] =             0.0f; o.m[3][3] = 1.0f;	
	
	return o;
}

M4 M4::orthographic(real32 top, real32 bottom, real32 left, real32 right, real32 near, real32 far)
{
	M4 o = {};
	o.m[0][0] =            2.0f / (right - left); o.m[0][1] =                             0.0f; o.m[0][2] =                         0.0f; o.m[0][3] = 0.0f;
	o.m[1][0] =                             0.0f; o.m[1][1] =            2.0f / (top - bottom); o.m[1][2] =                         0.0f; o.m[1][3] = 0.0f;
	o.m[2][0] =                             0.0f; o.m[2][1] =                             0.0f; o.m[2][2] =         -2.0f / (far - near); o.m[2][3] = 0.0f;
	o.m[3][0] = -(right + left) / (right - left); o.m[3][1] = -(top + bottom) / (top - bottom); o.m[3][2] = -(far + near) / (far - near); o.m[3][3] = 1.0f;

	return o;
}

M4 M4::perspective(real32 angleOfView, real32 near, real32 far)
{
	const real32 scale = 1.0f / (real32)((tan(angleOfView * 0.5f * PI / 180.0f)));
	
	M4 o = {};
	o.m[0][0] = scale; o.m[0][1] =  0.0f; o.m[0][2] =                  0.0f; o.m[0][3] =                           0.0f;
	o.m[1][0] =  0.0f; o.m[1][1] = scale; o.m[1][2] =                  0.0f; o.m[1][3] =                           0.0f;
	o.m[2][0] =  0.0f; o.m[2][1] =  0.0f; o.m[2][2] = -(far / (far - near)); o.m[2][3] = -((far * near) / (far - near));
	o.m[3][0] =  0.0f; o.m[3][1] =  0.0f; o.m[3][2] =                 -1.0f; o.m[3][3] =                           0.0f;

	return o;
}

M4& M4::transpose()
{
	swap(m[0][1], m[1][0]);
	swap(m[0][2], m[2][0]);
	swap(m[0][3], m[3][0]);
	swap(m[1][3], m[3][1]);
	swap(m[2][3], m[3][2]);
	swap(m[1][2], m[2][1]);

	return *this;
}

void M4::swap(real32& a, real32& b)
{
	real32 t = a;
	a = b;
	b = t;
}

real32* M4::operator[](uint8 i)
{
	return m[i];
}

const real32* M4::operator[](uint8 i) const
{
	return m[i];
}

M4 M4::operator*(const M4& n)
{
	M4 o;

	for (uint8 i = 0; i < 4; i++)
	{
		for (uint8 j = 0; j < 4; j++)
		{
			o[i][j] = m[i][0] * n[0][j] + 
					  m[i][1] * n[1][j] + 
					  m[i][2] * n[2][j] + 
					  m[i][3] * n[3][j] ;
		}
	}

	return o;
}

M4& M4::operator*=(const M4& n)
{
	*this = *this * n;
	return *this;
}


//GPURectangle Rectangle::toGPU() const
//{
//	GPURectangle r = {};
//
//	//r.points[0] = { origin.x        , origin.y          }; // Top Left
//	//r.points[1] = { origin.x        , origin.y + height }; // Bottom Left
//	//r.points[2] = { origin.x + width, origin.y + height }; // Bottom Right
//	//r.points[3] = r.points[0];  
//	//r.points[4] = r.points[2];  
//	//r.points[5] = { origin.x + width, origin.y }; // Top Right
//
//	r.points[0] = { 0.0f        , 0.0f }; // Top Left
//	r.points[1] = { height        , origin.y + height }; // Bottom Left
//	r.points[2] = { origin.x + width, origin.y + height }; // Bottom Right
//	r.points[3] = r.points[0];
//	r.points[4] = r.points[2];
//	r.points[5] = { origin.x + width, origin.y }; // Top Right
//
//	return r;
//}
//
//Point Rectangle::getCenter() const
//{
//	Point p = {};
//	p.x = origin.x + width  / 2.0f;
//	p.y = origin.y + height / 2.0f;
//
//	return p;
//}
//
//Vec2<real32> Rectangle::getHalfSize() const
//{
//	return { width / 2.0f, height / 2.0f };
//}




ParseNumberResult ParseNumber(const char* reader, DataType dataType, char endChar)
{
	ParseNumberResult result = {};
	bool negative = false;
	if (*reader == '-')
	{
		negative = true;
		reader++;
	}

	switch (dataType)
	{
		case DataType::INTEGER:
		{
			while (*reader != endChar)
			{
				if (!CharUtil::IsDigit(*reader)) return result;

				result.number.i = result.number.i * 10 + CharUtil::ToDigit(*reader);
				reader++;
			}

			if (negative)
			{
				result.number.i *= -1;
			}
		} break;


		case DataType::REAL32:
		{
			bool hitDot = false;
			real32 divider = 0.f;

			while (*reader != endChar)
			{
				if (!CharUtil::IsDigit(*reader) && !CharUtil::IsDot(*reader)) return result;

				if (*reader == '.')
				{
					hitDot = true;
					reader++;
					continue;
				}

				if (hitDot)
				{
					divider *= 10.f;
				}

				result.number.r32 = result.number.r32 * 10.f + CharUtil::ToDigit(*reader);
				reader++;
			}

			result.number.r32 /= divider;

			if (negative)
			{
				result.number.r32 *= -1.f;
			}
		} break;
	}

	result.valid = true;
	return result;
}

OBJParser::LineResult<uint16> OBJParser::parseFaceLine(FileReader& fileReader)
{
	LineResult<uint16> res = {};

	fileReader += 2;// +2 is the offset, so we start right onto the correct char
	bool hitSpace = true; // We start with true because we're onto the first char's number
	uint8 inputCounter = 0;

	while (*fileReader.reader != '\n')
	{
		if (hitSpace)
		{
			ParseNumberResult parsingRes = ParseNumber(fileReader.reader, DataType::INTEGER, '/');
			if (!parsingRes.valid) return res;

			if (inputCounter == 0)
			{
				res.vector.x = (uint16)parsingRes.number.i;
				res.vector.x--;
			}
			else if (inputCounter == 1)
			{
				res.vector.y = (uint16)parsingRes.number.i;
				res.vector.y--;
			}
			else
			{
				res.vector.z = (uint16)parsingRes.number.i;
				res.vector.z--;
			}

			inputCounter++;
			hitSpace = false;
			continue;
		}

		if (*fileReader.reader == ' ')
		{
			hitSpace = true;
			fileReader++;
			continue;
		}

		fileReader++;
	}

	return res;
}

OBJParser::LineResult<real32> OBJParser::parseVerticesLine(FileReader& fileReader)
{
	LineResult<real32> res                  = {};
	String             floatString          = {};
	bool               isCurrentlyOntoFloat = false;
	int                floatHeadCounter     = 0;
	uint8              floatCounter         = 0;

	while (*fileReader.reader != '\n')
	{
		bool wasPreviouslyOntoFloat = isCurrentlyOntoFloat;
		isCurrentlyOntoFloat = (CharUtil::IsArithmeticSign(*fileReader.reader) || CharUtil::IsDigit(*fileReader.reader) || CharUtil::IsDot(*fileReader.reader));

		// First char of float number
		if (!wasPreviouslyOntoFloat && isCurrentlyOntoFloat)
		{
			floatString.data = fileReader.reader;
			floatHeadCounter = 0;
		}

		// Last char of float number
		if (wasPreviouslyOntoFloat && !isCurrentlyOntoFloat)
		{
			floatString.size = floatHeadCounter;
			switch (floatCounter)
			{
				case 0: res.vector.x = StringUtil::ToFloat(floatString); break;
				case 1: res.vector.y = StringUtil::ToFloat(floatString); break;
			}
			floatString = {};
			floatCounter++;
		}

		floatHeadCounter++;
		fileReader++;
	}

	// >NOTE: The last char of the line will have us exit the while loop so we finish setting the last float here instead
	floatString.size = floatHeadCounter;
	res.vector.z     = StringUtil::ToFloat(floatString);
	res.reader       = fileReader.reader;

	return res;
}

real32 StringUtil::ToFloat(const char* string, uint8 size)
{
	bool  negative = *string == '-';
	bool  reachedDot = false;
	int   integer = 0;
	int   divider = 1;
	uint8 counter = negative ? 1 : 0;

	for (counter; counter < size; counter++)
	{
		if (string[counter] == '.')
		{
			reachedDot = true;
			continue;
		}

		integer = integer * 10 + CharUtil::ToDigit(string[counter]);

		if (reachedDot)
		{
			divider *= 10;
		}
	}

	float res = (float)(integer) / divider;
	if (negative)
	{
		res *= -1.0f;
	}

	return res;
}

real32 StringUtil::ToFloat(const String& string)
{
	return StringUtil::ToFloat(string.data, (uint8)string.size);
}

int StringUtil::ToInt(const char* string, uint8 size)
{
	bool negative = *string == '-';
	int integer = 0;
	uint8 counter = negative ? 1 : 0;

	for (counter; counter < size; counter++)
	{
		integer = integer * 10 + CharUtil::ToDigit(string[counter]);
	}

	if (negative)
	{
		integer *= -1;
	}

	return integer;
}

int StringUtil::ToInt(const String& string)
{
	return StringUtil::ToInt(string.data, (uint8)string.size);
}


Vertex XinParser::parseVertexLine(const String& line)
{
	Vertex v = {};

	return v;
}

MeshAsset loadMesh(const char* filename, GameMemory* memory, PlatformFunctions* platformFunctions)
{
	MeshAsset      asset  = {};
	ReadFileResult file   = platformFunctions->readFile(filename, memory);
	const char*    reader = (const char*)file.content;

	// Parse vertices
	{
		auto parseFloat = [](const char*& reader, char separator) -> real32
			{
				const char* head = reader;
				uint8 counter = 0;

				while (*reader != separator)
				{
					reader++;
					counter++;
				}
			
				real32 result = StringUtil::ToFloat(head, counter);
				return result;
			};

		auto parsePosition = [parseFloat](const char*& reader) -> Vec3<real32>
			{
				real32 x, y, z;

				x = parseFloat(reader, ' '); reader++; // Additional increment to get us right onto the next's float char
				y = parseFloat(reader, ' '); reader++;
				z = parseFloat(reader, '|'); reader++;

				return { x, y, z };
			};

		auto parseUV = [parseFloat](const char*& reader) -> Vec2<real32>
			{
				real32 x, y;

				x = parseFloat(reader, ' '); reader++;
				y = parseFloat(reader, '|'); reader++;

				return { x, y };
			};

		auto parseNormals = [parseFloat](const char*& reader) -> Vec3<real32>
			{
				real32 x, y, z;

				x = parseFloat(reader, ' ' ); reader++;
				y = parseFloat(reader, ' ' ); reader++;
				z = parseFloat(reader, '\r'); reader++;

				return { x, y, z };
			};

		auto parseVertexLine = [parsePosition, parseUV, parseNormals](const char*& reader) -> Vertex
			{
				Vertex v = {};

				v.position = parsePosition(reader);
				v.uv       = parseUV      (reader);
				v.normal   = parseNormals (reader);

				reader++; // Every line ends with two characters (CR and LF) (Carriage Return (\r), Line Feed (\n))
				return v;
			};

		while (*reader != XIN_FILE__INDICE_CHAR)
		{
			Vertex v = parseVertexLine(reader);
			asset.vertices.push(v);
		}
	}


	// Moves reader to the 1st char of the indices serie
	{
		reader++;
		reader++;
		reader++;
	}


	// Parse indices
	{
		struct ParseIntResult
		{
			uint32 integer;
			bool reachedEndFile;
		};

		auto parseInt = [](const char*& reader, char separator) -> ParseIntResult
			{
				const char* head = reader;
				uint8 counter = 0;

				while (*reader != separator && *reader != XIN_FILE__CLOSE_CHAR)
				{
					if (*reader == '\r') 
					{
						// Gets us on next char, which is supposed to be '\n'
						// We then advance on next char again in the for loop, which is supposed to get us on next index's 1st char
						reader++; 
						break;
					}

					reader++;
					counter++;
				}

				uint32 result = StringUtil::ToInt(head, counter);
				return { result,  *reader == XIN_FILE__CLOSE_CHAR };
			};

		for (;;)
		{
			ParseIntResult result = parseInt(reader, '|');
			asset.indices.push(result.integer);

			if (result.reachedEndFile)
				break;

			reader++;
		}
	}

	return asset;
}


uint32 CeilToNextMultiple(uint32 value, uint32 multiple)
{
	uint32 step = value / multiple + (value % multiple == 0 ? 0 : 1);
	return step * multiple;
}

void String2::print(flog* log)
{
	log(content);
}

void InitializeWebGPU(WebGPUStorage* storage, void* wndHandle, void* hInstance, GameMemory* memory, MeshAsset* asset, PlatformFunctions* platformFunctions)
{
	storage->instance = wgpu::helper::createInstance();
	storage->adapter = wgpu::helper::createAdapter(storage->instance);
	storage->device = wgpu::helper::createDevice(storage->adapter, platformFunctions->log);
	storage->surface = wgpu::helper::createSurface(wndHandle, hInstance, storage->instance);

	String2 str = {};
	str.content = "Hello there";
	str.print(platformFunctions->log);

	ReadFileResult file = platformFunctions->readFile("../resource/shaders/game.sha", memory);
	ASSERT(file.content);
	WGPUStringView shaderCode = {};
	shaderCode.data = (const char*)file.content;
	shaderCode.length = file.contentSize;
	storage->gameShaderModule = wgpu::helper::createShaderModule(storage->device, shaderCode, "Game Shader Module");

	file = platformFunctions->readFile("../resource/shaders/ui.sha", memory);
	ASSERT(file.content);
	shaderCode = {};
	shaderCode.data = (const char*)file.content;
	shaderCode.length = file.contentSize;
	storage->uiShaderModule = wgpu::helper::createShaderModule(storage->device, shaderCode, "UI Shader Module");

	storage->gameBindGroupLayout = wgpu::helper::createGameBindGroupLayout(storage->device, sizeof(GameShaderUniform), "Game Bind Group Layout-san");
	storage->uiBindGroupLayout = wgpu::helper::createUIBindGroupLayout(storage->device, sizeof(UIShaderUniform), "UI Bind Group Layout-san");
	storage->globalBindGroupLayout = wgpu::helper::createGlobalBindGroupLayout(storage->device, sizeof(GlobalUniform), "Global Bind Group Layout-san");
	storage->gamePipelineLayout = wgpu::helper::createPipelineLayout(storage->device, storage->gameBindGroupLayout, "Game Pipeline Layout-san");
	storage->uiLayouts[0] = storage->uiBindGroupLayout.object;
	storage->uiLayouts[1] = storage->globalBindGroupLayout.object;
	storage->uiPipelineLayout = wgpu::helper::createPipelineLayout(storage->device, storage->uiLayouts, "UI Pipeline Layout-san");
	storage->gamePipeline = wgpu::helper::createGameRenderPipeline(storage->device, storage->gameShaderModule, storage->surface.getFormat(storage->adapter), storage->gamePipelineLayout, "Game Pipeline-san");
	storage->uiPipeline = wgpu::helper::createUIRenderPipeline(storage->device, storage->uiShaderModule, storage->surface.getFormat(storage->adapter), storage->uiPipelineLayout, "UI Pipeline-san");

	WGPUSurfaceConfiguration config = {};
	config.nextInChain = nullptr;
	config.width = WINDOW_WIDTH;
	config.height = WINDOW_HEIGHT;
	config.format = storage->surface.getFormat(storage->adapter);
	config.viewFormatCount = 0;
	config.viewFormats = nullptr;
	config.usage = WGPUTextureUsage_RenderAttachment;
	config.device = storage->device.object;
	config.presentMode = wgpu::PresentMode::Fifo;
	config.alphaMode = wgpu::CompositeAlphaMode::Auto;
	storage->surface.configure(&config);

	storage->adapter.release();
	storage->gameShaderModule.release();
	storage->uiShaderModule.release();

	storage->queue = storage->device.getQueueHelper();



	WGPUTextureFormat depthTextureFormat = wgpu::TextureFormat::Depth24Plus;
	WGPUTextureDescriptor depthTextureDesc = {};
	depthTextureDesc.dimension = wgpu::TextureDimension::_2D;
	depthTextureDesc.format = depthTextureFormat;
	depthTextureDesc.mipLevelCount = 1;
	depthTextureDesc.sampleCount = 1;
	depthTextureDesc.size = { WINDOW_WIDTH , WINDOW_HEIGHT, 1 };
	depthTextureDesc.usage = WGPUTextureUsage_RenderAttachment;
	depthTextureDesc.viewFormatCount = 1;
	depthTextureDesc.viewFormats = &depthTextureFormat;
	storage->depthTexture = storage->device.createTextureHelper(&depthTextureDesc);

	WGPUTextureViewDescriptor depthTextureViewDesc = {};
	depthTextureViewDesc.aspect = wgpu::TextureAspect::DepthOnly;
	depthTextureViewDesc.baseArrayLayer = 0;
	depthTextureViewDesc.arrayLayerCount = 1;
	depthTextureViewDesc.baseMipLevel = 0;
	depthTextureViewDesc.mipLevelCount = 1;
	depthTextureViewDesc.dimension = wgpu::TextureViewDimension::_2D;
	depthTextureViewDesc.format = depthTextureFormat;
	storage->depthTextureView = storage->depthTexture.createViewHelper(&depthTextureViewDesc);




	//
	// Game
	//

	GameShaderUniform gameShaderUniform = {};

	//shaderUniform.projectionMatrix = M4::orthographic(1.0f, -1.0f, -1.0f, 1.0f, -100.0f, 100.0f);
	gameShaderUniform.projectionMatrix = M4::perspective(45.0f, 1.00f, 100.0f);
	gameShaderUniform.viewMatrix       = M4::identity() * M4::translate(0.0f, 5.0f, 0.0f);
	gameShaderUniform.modelMatrix      = M4::identity();

	gameShaderUniform.time = 0.0f;
	gameShaderUniform.color[0] = 0.0f;
	gameShaderUniform.color[1] = 1.0f;
	gameShaderUniform.color[2] = 0.0f;
	gameShaderUniform.color[3] = 1.0f;

	storage->gameShaderUniform = gameShaderUniform; // >TODO: put this inside memory


	// Vertices buffer
	WGPUBufferDescriptor bufferDesc = {};
	bufferDesc.size = asset->vertices.getElementsSize();
	bufferDesc.usage = WGPUBufferUsage_Vertex | WGPUBufferUsage_CopyDst;

	storage->vertexBuffer = storage->device.createBufferHelper(&bufferDesc, "Vertices Buffer");
	storage->queue.writeBuffer(storage->vertexBuffer, 0, asset->vertices.dataPtr(), bufferDesc.size);


	// Indices buffer
	bufferDesc.size = asset->indices.getElementsSize();
	bufferDesc.usage = WGPUBufferUsage_Index | WGPUBufferUsage_CopyDst;

	storage->indexBuffer = storage->device.createBufferHelper(&bufferDesc, "Indices Buffer");
	storage->queue.writeBuffer(storage->indexBuffer, 0, asset->indices.dataPtr(), bufferDesc.size);

	

	//
	// UI
	//

	//Rectangle r1 = {};
	//r1.width = 500.0f;
	//r1.height = 200.0f;
	//r1.origin = { 50.0f, 200.0f };
	//
	//Rectangle r2 = {};
	//r2.width = 500.0f;
	//r2.height = 200.0f;
	//r2.origin = { 600.0f, 200.0f };

	UIShaderUniform uiShaderUniform = {};
	uiShaderUniform.color[0] = 1.0f;
	uiShaderUniform.color[1] = 0.0f;
	uiShaderUniform.color[2] = 0.0f;
	uiShaderUniform.color[3] = 1.0f;
	uiShaderUniform.radius = 4.0f;
	//uiShaderUniform.center = { 0.0f, 0.0f };
	//uiShaderUniform.halfSize = { 0.5f, 0.5f };
	//uiShaderUniform.center = r1.getCenter();
	//uiShaderUniform.halfSize = r1.getHalfSize();

	storage->uiShaderUniform = uiShaderUniform;


	GlobalUniform globalUniform = {};
	globalUniform.windowSize = { (real32)WINDOW_WIDTH, (real32)WINDOW_HEIGHT };
	storage->globalShaderUniform = globalUniform;



	GPURectangleModel recModel = {};

	GPURectangleInstance rectangles[4] = {};
	rectangles[0].position = { 50.0f, 100.0f };
	rectangles[0].size     = { 400.0f, 150.0f };
	rectangles[1].position = { 50.0f, 500.0f };
	rectangles[1].size     = { 400.0f, 150.0f };
	rectangles[2].position = { 500.0f, 100.0f };
	rectangles[2].size     = { 400.0f, 150.0f };
	rectangles[3].position = { 500.0f, 500.0f };
	rectangles[3].size     = { 400.0f, 150.0f };
	 
	// Points buffer
	//GPURectangle rect[2] = {};
	//rect[0] = r1.toGPU();
	//rect[1] = r2.toGPU();
	//GPUInstance rectInstance = { 50.0f, 100.0f };
	
	//rect.points[0] = {-0.5f, 0.5f}; // Top Left
	//rect.points[1] = {0.5f, 0.5f}; // Top Right
	//rect.points[2] = {0.5f, -0.5f}; // Bottom Right
	//rect.points[3] = {-0.5f, -0.5f}; // Bottom Left
	//rect.points[0] = {-300.f, 200.0f}; // Top Left
	//rect.points[1] = {300.f, 200.0f}; // Top Right
	//rect.points[2] = {300.f, -200.0f}; // Bottom Right
	//rect.points[3] = {-300.f, -200.0f}; // Bottom Left
	//rect.points[0] = { r.origin.x, r.origin.y }; // Top Left
	//rect.points[1] = { r.origin.x, r.origin.y + r.height }; //  Bottom Left
	//rect.points[2] = { r.origin.x + r.width, r.origin.y + r.height }; // Bottom Right
	//rect.points[3] = { r.origin.x + r.width, r.origin.y }; // Top Right
	bufferDesc.size = sizeof(GPURectangleModel);
	bufferDesc.usage = WGPUBufferUsage_Vertex | WGPUBufferUsage_CopyDst;
	storage->rectangleModelBuffer = storage->device.createBufferHelper(&bufferDesc, "Rectangle Model Buffer");
	storage->queue.writeBuffer(storage->rectangleModelBuffer, 0, &recModel, bufferDesc.size);

	bufferDesc.size = sizeof(GPURectangleInstance) * 4;
	bufferDesc.usage = WGPUBufferUsage_Vertex | WGPUBufferUsage_CopyDst;
	storage->rectangleInstanceBuffer = storage->device.createBufferHelper(&bufferDesc, "Rectangle Instance Buffer");
	storage->queue.writeBuffer(storage->rectangleInstanceBuffer, 0, &rectangles, bufferDesc.size);


	//bufferDesc.size = sizeof(uint16) * 6;
	//bufferDesc.usage = WGPUBufferUsage_Index | WGPUBufferUsage_CopyDst;
	//storage->rectangleIndexBuffer = storage->device.createBufferHelper(&bufferDesc, "Rectangle Indices Buffer");
	//storage->queue.writeBuffer(storage->rectangleIndexBuffer, 0, rect.indices, bufferDesc.size);


	//WGPUBufferDescriptor bufferDesc = {};
	//bufferDesc.nextInChain = nullptr;
	//bufferDesc.usage = WGPUBufferUsage_CopyDst | WGPUBufferUsage_Vertex;
	//bufferDesc.size = asset->vertices.getElementsSize();
	//bufferDesc.size = (bufferDesc.size + 3) & ~3;
	//bufferDesc.mappedAtCreation = false;
	//storage->vertexBuffer = storage->device.createBufferHelper(&bufferDesc, "Vertex Buffer);
	//storage->queue.writeBuffer(storage->vertexBuffer, 0, asset->vertices.dataPtr(), bufferDesc.size);

	//bufferDesc.usage = WGPUBufferUsage_CopyDst | WGPUBufferUsage_Vertex;
	//bufferDesc.size = asset->normals.getElementsSize();
	//bufferDesc.size = (bufferDesc.size + 3) & ~3;
	//bufferDesc.mappedAtCreation = false;
	//storage->normalBuffer = storage->device.createBufferHelper(&bufferDesc, "Normal buffer");
	//storage->queue.writeBuffer(storage->normalBuffer, 0, asset->normals.dataPtr(), bufferDesc.size);

	//bufferDesc.usage = WGPUBufferUsage_CopyDst | WGPUBufferUsage_Index;
	//bufferDesc.size = asset->indexes.getElementsSize();
	//bufferDesc.size = (bufferDesc.size + 3) & ~3; // From right to left, dummy
	//bufferDesc.mappedAtCreation = false;
	//storage->indexBuffer = storage->device.createBufferHelper(&bufferDesc, "Index buffer");
	//storage->queue.writeBuffer(storage->indexBuffer, 0, asset->indexes.dataPtr(), bufferDesc.size);

	WGPULimits supportedLimits = storage->adapter.getDefaultLimits();

	// 
	// Game bindings
	//

	uint32 uniformBufferStride = CeilToNextMultiple((uint32)sizeof(GameShaderUniform), (uint32)supportedLimits.minUniformBufferOffsetAlignment);
	bufferDesc.size = uniformBufferStride + sizeof(GameShaderUniform);
	bufferDesc.usage = WGPUBufferUsage_CopyDst | WGPUBufferUsage_Uniform;
	bufferDesc.mappedAtCreation = false;
	storage->gameUniformBuffer = storage->device.createBufferHelper(&bufferDesc, "Game Uniform Buffer");
	storage->queue.writeBuffer(storage->gameUniformBuffer, 0, &storage->gameShaderUniform, sizeof(GameShaderUniform));

	WGPUBindGroupEntry gameBinding = {};
	gameBinding.nextInChain = nullptr;
	gameBinding.binding = 0; // The index of the binding
	gameBinding.buffer = storage->gameUniformBuffer.object;
	gameBinding.offset = 0; // A buffer can contain multiple uniforms
	gameBinding.size = sizeof(GameShaderUniform);
	WGPUBindGroupDescriptor bindGroupDesc = {};
	bindGroupDesc.nextInChain = nullptr;
	bindGroupDesc.layout = storage->gameBindGroupLayout.object;
	bindGroupDesc.entryCount = 1;
	bindGroupDesc.entries = &gameBinding;
	storage->gameBindGroup = storage->device.createBindGroupHelper(&bindGroupDesc, "Game Bind group-san");


	// 
	// UI bindings
	//

	//uniformBufferStride = CeilToNextMultiple((uint32)sizeof(UIShaderUniform), (uint32)supportedLimits.minUniformBufferOffsetAlignment);
	bufferDesc.size = /*uniformBufferStride + */ sizeof(UIShaderUniform);
	bufferDesc.usage = WGPUBufferUsage_CopyDst | WGPUBufferUsage_Uniform;
	bufferDesc.mappedAtCreation = false;
	storage->uiUniformBuffer = storage->device.createBufferHelper(&bufferDesc, "UI Uniform Buffer");
	storage->queue.writeBuffer(storage->uiUniformBuffer, 0, &storage->uiShaderUniform, sizeof(UIShaderUniform));

	bufferDesc.size = sizeof(GlobalUniform);
	bufferDesc.usage = WGPUBufferUsage_CopyDst | WGPUBufferUsage_Uniform;
	bufferDesc.mappedAtCreation = false;
	storage->globalUniformBuffer = storage->device.createBufferHelper(&bufferDesc, "Global Uniform Buffer");
	storage->queue.writeBuffer(storage->globalUniformBuffer, 0, &storage->globalShaderUniform, sizeof(GlobalUniform));

	WGPUBindGroupEntry uiEntry = {};
	uiEntry.nextInChain = nullptr;
	uiEntry.binding = 0;
	uiEntry.buffer = storage->uiUniformBuffer.object;
	uiEntry.offset = 0;
	uiEntry.size = sizeof(UIShaderUniform);

	bindGroupDesc = {};
	bindGroupDesc.nextInChain = nullptr;
	bindGroupDesc.layout = storage->uiBindGroupLayout.object;
	bindGroupDesc.entryCount = 1;
	bindGroupDesc.entries = &uiEntry;
	storage->uiBindGroup = storage->device.createBindGroupHelper(&bindGroupDesc, "UI Bind Group-san");


	WGPUBindGroupEntry globalEntry = {};
	globalEntry.nextInChain = nullptr;
	globalEntry.binding = 0;
	globalEntry.buffer = storage->globalUniformBuffer.object;
	globalEntry.offset = 0;
	globalEntry.size = sizeof(GlobalUniform);

	bindGroupDesc = {};
	bindGroupDesc.nextInChain = nullptr;
	bindGroupDesc.layout = storage->globalBindGroupLayout.object;
	bindGroupDesc.entryCount = 1;
	bindGroupDesc.entries = &globalEntry;
	storage->globalBindGroup = storage->device.createBindGroupHelper(&bindGroupDesc, "Global Bind Group-san");
}


void updateGame(GameMemory* memory, GameState* gameState, PlatformFunctions* platformFunctions, WebGPUStorage* wgpuStorage, MeshAsset* asset, GameInputController* inputs)
{
	// Object
	M4 S  = M4::scale(0.4f);
	M4 T1 = M4::translate(0.0f, 0.0f, 0.0f);
	M4 R1 = M4::rotateZ(wgpuStorage->gameShaderUniform.time);
	wgpuStorage->gameShaderUniform.modelMatrix = R1 * T1 * S;

	// View
	//M4 T2 = M4::translate(0.0f, 1.0f, 0.0f);
	//M4 R2 = M4::rotateX(0.0f);
	//wgpuStorage->gameShaderUniform.viewMatrix = T2;

	const real32 moveIncrement = 0.01f;
	const real32 rotateIncrement = 1.0f;
	
	if (inputs->moveLeft.state == DOWN)
	{
		M4 move = M4::translate(moveIncrement, 0.0f, 0.0f);
		wgpuStorage->gameShaderUniform.viewMatrix *= move;
	}
	if (inputs->moveRight.state == DOWN)
	{
		M4 move = M4::translate(-moveIncrement, 0.0f, 0.0f);
		wgpuStorage->gameShaderUniform.viewMatrix *= move;
	}
	if (inputs->moveForward.state == DOWN)
	{
		M4 move = M4::translate(0.0f, -moveIncrement, 0.0f);
		wgpuStorage->gameShaderUniform.viewMatrix *= move;
	}
	if (inputs->moveBackward.state == DOWN)
	{
		M4 move = M4::translate(0.0f, moveIncrement, 0.0f);
		wgpuStorage->gameShaderUniform.viewMatrix *= move;
	}
	if (inputs->rotateLeft.state == DOWN)
	{
		M4 rotate = M4::rotateZ(rotateIncrement);
		wgpuStorage->gameShaderUniform.viewMatrix *= rotate;
	}
	if (inputs->rotateRight.state == DOWN)
	{
		M4 rotate = M4::rotateZ(-rotateIncrement);
		wgpuStorage->gameShaderUniform.viewMatrix *= rotate;
	}
	if (inputs->rotateFront.state == DOWN)
	{
		M4 rotate = M4::rotateX(rotateIncrement);
		wgpuStorage->gameShaderUniform.viewMatrix *= rotate;
	}
	if (inputs->rotateBack.state == DOWN)
	{
		M4 rotate = M4::rotateX(-rotateIncrement);
		wgpuStorage->gameShaderUniform.viewMatrix *= rotate;
	}

	// Update the uniform time 
	wgpuStorage->queue.writeBuffer(wgpuStorage->gameUniformBuffer, offsetof(GameShaderUniform, GameShaderUniform::time),
		&wgpuStorage->gameShaderUniform.time, sizeof(GameShaderUniform::time));

	wgpuStorage->queue.writeBuffer(wgpuStorage->gameUniformBuffer, offsetof(GameShaderUniform, GameShaderUniform::projectionMatrix),
		&wgpuStorage->gameShaderUniform.projectionMatrix, sizeof(GameShaderUniform::projectionMatrix));

	wgpuStorage->queue.writeBuffer(wgpuStorage->gameUniformBuffer, offsetof(GameShaderUniform, GameShaderUniform::viewMatrix),
		&wgpuStorage->gameShaderUniform.viewMatrix, sizeof(GameShaderUniform::viewMatrix));

	wgpuStorage->queue.writeBuffer(wgpuStorage->gameUniformBuffer, offsetof(GameShaderUniform, GameShaderUniform::modelMatrix),
		&wgpuStorage->gameShaderUniform.modelMatrix, sizeof(GameShaderUniform::modelMatrix));


	// Update the uniform color
	//wgpuStorage->queue.writeBuffer(wgpuStorage->gameUniformBuffer, offsetof(ShaderUniform, ShaderUniform::color), 
	//	&wgpuStorage->shaderUniform.color, sizeof(ShaderUniform::color));
}



XARGS(GameMemory* memory, GameState* gameState, PlatformFunctions* platformFunctions, MeshAsset* asset, WebGPUStorage* wgpuStorage, void* wndHandle, void* hInstance)
extern "C" GAME_INITIALIZE(Game_Initialize)
{
	// Load assets
	//
	*asset = loadMesh("../resource/meshes/clean/Suzy.xin", memory, platformFunctions);

	// Load wgpu
	//
	InitializeWebGPU(wgpuStorage, wndHandle, hInstance, memory, asset, platformFunctions);


	gameState->initialized = true;
}


XARGS(GameMemory* memory, GameState* gameState, PlatformFunctions* platformFunctions, WebGPUStorage* wgpuStorage, MeshAsset* asset, GameInputController* inputs)
extern "C" GAME_UPDATE(Game_Update)
{
	if (!gameState->initialized)
	{
		gameState->quit = true;
		return;
	}

	//wgpuStorage->shaderUniform.time += 0.01f;

	updateGame(memory, gameState, platformFunctions, wgpuStorage, asset, inputs);
	

	

	wgpu::TextureView targetView = wgpuStorage->surface.getCurrentTextureView();
	ASSERT(targetView.object);

	WGPUCommandEncoderDescriptor encoderDesc = {};
	encoderDesc.nextInChain = nullptr;
	wgpu::CommandEncoder encoder = wgpuStorage->device.createCommandEncoderHelper(&encoderDesc, "Sexy Command Encoder (SCE)");


	// Describe Game Render Pass
	//
	WGPURenderPassColorAttachment gameRenderPassColorAttachment = {};
	gameRenderPassColorAttachment.view = targetView.object;
	gameRenderPassColorAttachment.resolveTarget = nullptr;
	gameRenderPassColorAttachment.loadOp = wgpu::LoadOp::Clear;
	gameRenderPassColorAttachment.storeOp = wgpu::StoreOp::Store;
	gameRenderPassColorAttachment.clearValue = WGPUColor{ 0.15, 0.2, 0.33, 1.0f };
	gameRenderPassColorAttachment.depthSlice = WGPU_DEPTH_SLICE_UNDEFINED;

	WGPURenderPassDepthStencilAttachment depthStencilAttachment = {};
	depthStencilAttachment.view = wgpuStorage->depthTextureView.object;
	depthStencilAttachment.depthClearValue = 1.0f;
	depthStencilAttachment.depthLoadOp = wgpu::LoadOp::Clear;
	depthStencilAttachment.depthStoreOp = wgpu::StoreOp::Store;
	depthStencilAttachment.depthReadOnly = wgpu::OptionalBool::False;
	depthStencilAttachment.stencilClearValue = 0;
	depthStencilAttachment.stencilLoadOp = wgpu::LoadOp::Undefined; // Dawn specific
	depthStencilAttachment.stencilStoreOp = wgpu::StoreOp::Undefined; // Dawn specific
	depthStencilAttachment.stencilReadOnly = wgpu::OptionalBool::True;

	WGPURenderPassDescriptor gameRenderPassDesc = {};
	gameRenderPassDesc.colorAttachmentCount = 1;
	gameRenderPassDesc.colorAttachments = &gameRenderPassColorAttachment;
	gameRenderPassDesc.nextInChain = nullptr;
	gameRenderPassDesc.depthStencilAttachment = &depthStencilAttachment;
	gameRenderPassDesc.timestampWrites = nullptr;

	wgpu::RenderPassEncoder gameRenderPass = encoder.beginRenderPassHelper(&gameRenderPassDesc, "Game Render Pass Encoder-san");

	// Use Game Render Pass
	//
	uint32 dynamicOffset = 0;
	WGPULimits supportedLimits = wgpuStorage->adapter.getDefaultLimits();
	uint32 uniformBufferStride = CeilToNextMultiple((uint32)sizeof(GameShaderUniform), (uint32)supportedLimits.minUniformBufferOffsetAlignment);
	dynamicOffset = 0 * uniformBufferStride;
	gameRenderPass.setPipeline(wgpuStorage->gamePipeline);
	gameRenderPass.setVertexBuffer(0, wgpuStorage->vertexBuffer, 0, wgpuStorage->vertexBuffer.getSize());
	gameRenderPass.setIndexBuffer(wgpuStorage->indexBuffer, wgpu::IndexFormat::Uint32, 0, wgpuStorage->indexBuffer.getSize());
	gameRenderPass.setBindGroup(0, wgpuStorage->gameBindGroup, 1, &dynamicOffset);
	gameRenderPass.drawIndexed((uint32)(asset->indices.getElementsLength()), 1, 0, 0, 0);
	gameRenderPass.end();
	gameRenderPass.release();


	// Describe UI Render Pass
	//
	WGPURenderPassColorAttachment uiRenderPassColorAttachment = {};
	uiRenderPassColorAttachment.view = targetView.object;
	uiRenderPassColorAttachment.loadOp = wgpu::LoadOp::Load; // !!! We don't clear, we keep what was drawn above !!!
	uiRenderPassColorAttachment.storeOp = wgpu::StoreOp::Store;
	uiRenderPassColorAttachment.depthSlice = WGPU_DEPTH_SLICE_UNDEFINED;

	WGPURenderPassDescriptor uiRenderPassDesc = {};
	uiRenderPassDesc.colorAttachmentCount = 1;
	uiRenderPassDesc.colorAttachments = &uiRenderPassColorAttachment;
	uiRenderPassDesc.nextInChain = nullptr;
	uiRenderPassDesc.depthStencilAttachment = nullptr; 
	uiRenderPassDesc.timestampWrites = nullptr;

	wgpu::RenderPassEncoder uiRenderPass = encoder.beginRenderPassHelper(&uiRenderPassDesc, "UI Render Pass Encoder-san");



	// UI Render Pass

	//uniformBufferStride = CeilToNextMultiple((uint32)sizeof(UIShaderUniform), (uint32)supportedLimits.minUniformBufferOffsetAlignment);
	uiRenderPass.setPipeline(wgpuStorage->uiPipeline);
	uiRenderPass.setVertexBuffer(0, wgpuStorage->rectangleModelBuffer, 0, wgpuStorage->rectangleModelBuffer.getSize());
	uiRenderPass.setVertexBuffer(1, wgpuStorage->rectangleInstanceBuffer, 0, wgpuStorage->rectangleInstanceBuffer.getSize());
	//uiRenderPass.setIndexBuffer(wgpuStorage->rectangleIndexBuffer, WGPUIndexFormat_Uint16, 0, wgpuStorage->rectangleIndexBuffer.getSize());
	uiRenderPass.setBindGroup(0, wgpuStorage->uiBindGroup, 0, &dynamicOffset);

	// Window resizing
	// >NOTE: as soon as we start resizing the window with a drag, Windows gets stuck within the WM_SIZE and never call gameUpdate()	
	if (wgpuStorage->globalShaderUniform.windowSize.x != gameState->windowSize.x ||
		wgpuStorage->globalShaderUniform.windowSize.y != gameState->windowSize.y)
	{
		wgpuStorage->globalShaderUniform.windowSize = gameState->windowSize;

		wgpuStorage->queue.writeBuffer(wgpuStorage->globalUniformBuffer, 0,
			&wgpuStorage->globalShaderUniform, sizeof(GlobalUniform));
	}
	uiRenderPass.setBindGroup(1, wgpuStorage->globalBindGroup, 0, &dynamicOffset);
	uiRenderPass.draw(6, 4, 0, 0);
	//uiRenderPass.drawIndexed(6, 1, 0, 0, 0);
	uiRenderPass.end();
	uiRenderPass.release();

	WGPUCommandBufferDescriptor commandBufferDesc = {};
	commandBufferDesc.nextInChain = nullptr;
	wgpu::CommandBuffer commandBuffer = encoder.finishHelper(&commandBufferDesc, "Command Buffer-san");
	encoder.release();

	wgpuStorage->queue.submit(1, &commandBuffer.object);
	commandBuffer.release();
	targetView.release();
	wgpuStorage->surface.present();
	wgpuStorage->device.tick();
}

XARGS(WebGPUStorage* storage)
extern "C" GAME_QUIT(Game_Quit)
{
	storage->gamePipeline.release();
	storage->surface.unconfigure();
	storage->queue.release();
	storage->surface.release();
	storage->gamePipelineLayout.release();
	storage->uiPipelineLayout.release();
	storage->gameBindGroup.release();
	storage->uiBindGroup.release();
	storage->gameBindGroupLayout.release();
	storage->uiBindGroupLayout.release();
	storage->vertexBuffer.release();
	storage->indexBuffer.release();
	storage->rectangleInstanceBuffer.release();
	storage->rectangleModelBuffer.release();
	storage->gameUniformBuffer.release();
	storage->uiUniformBuffer.release();
}