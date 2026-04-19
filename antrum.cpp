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

OBJParser::Vec3ILineResult OBJParser::parseFaceLine(FileReader& fileReader)
{
	Vec3ILineResult res = {};

	//counter += 2;
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
				res.vector.a = (uint16)parsingRes.number.i;
				res.vector.a--;
			}
			else if (inputCounter == 1)
			{
				res.vector.b = (uint16)parsingRes.number.i;
				res.vector.b--;
			}
			else
			{
				res.vector.c = (uint16)parsingRes.number.i;
				res.vector.c--;
			}

			inputCounter++;
			hitSpace = false;
			continue;
		}

		if (*fileReader.reader == ' ')
		{
			hitSpace = true;
			//counter++;
			//reader++;
			fileReader++;
			continue;
		}

		//counter++;
		//reader++;
		fileReader++;
	}

	return res;
}

OBJParser::Vec3LineResult OBJParser::parseVec3Line(FileReader& fileReader)
{
	Vec3LineResult res = {};
	String         floatString = {};
	bool           isCurrentlyOntoFloat = false;
	int            floatHeadCounter = 0;
	uint8          floatCounter = 0;

	while (*fileReader.reader != '\n')
	{
		bool wasPreviouslyOntoFloat = isCurrentlyOntoFloat;
		isCurrentlyOntoFloat = (CharUtil::IsArithmeticSign(*fileReader.reader) || CharUtil::IsDigit(*fileReader.reader) || CharUtil::IsDot(*fileReader.reader));

		// First float char
		if (!wasPreviouslyOntoFloat && isCurrentlyOntoFloat)
		{
			floatString.head = fileReader.reader;
			floatHeadCounter = 0;
		}

		// Last float char
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
	floatString.size = floatHeadCounter - 1;
	res.vector.z = StringUtil::ToFloat(floatString);
	res.reader = fileReader.reader;

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
	return StringUtil::ToFloat(string.head, (uint8)string.size);
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
	return StringUtil::ToInt(string.head, (uint8)string.size);
}

void ReadFile_OBJ(const char* Filename, GameMemory* Memory, PlatformStorage* platformStorage, MeshAsset& outAsset)
{
	//ReadFileResult res = Win32_Util_ReadFile(Filename, Memory);
	ReadFileResult res = platformStorage->readFile(Filename, Memory);

	//OutputDebugString("--------------------------\n");
	//OutputDebugString(static_cast<const char*>(res.content));
	//OutputDebugString("--------------------------\n");

	OBJParser::OBJFileResult fileRes = {};

	Vec3 vec = {};
	Vec3I indexes = {};
	FileReader fileReader = {};
	fileReader.reader = (const char*)res.content;
	
	OBJParser::Vec3LineResult lineRes = {};
	OBJParser::Vec3ILineResult lineResFaces = {};

	while (fileReader.counter < res.contentSize)
	{
		if (*fileReader.reader == 'v')
		{
			char nextChar = *(fileReader.reader + 1);
			if (CharUtil::IsSpace(nextChar))
			{
				lineRes = OBJParser::parseVec3Line(fileReader);
				outAsset.vertices.push(lineRes.vector.x);
				outAsset.vertices.push(lineRes.vector.y);
				outAsset.vertices.push(lineRes.vector.z);
			}
		}
		else if (*fileReader.reader == 'f')
		{
			lineResFaces = OBJParser::parseFaceLine(fileReader);
			outAsset.indexes.push(lineResFaces.vector.a);
			outAsset.indexes.push(lineResFaces.vector.b);
			outAsset.indexes.push(lineResFaces.vector.c);
		}

		fileReader++;
	}
}




XARGS(GameMemory* memory, GameState* gameState, PlatformStorage* platformStorage, MeshAsset* asset)
extern "C" GAME_INITIALIZE(Game_Initialize)
{
	// Load mesh asset
	ReadFile_OBJ("../resource/TestOBJ.obj", memory, platformStorage, *asset);

	gameState->initialized = true;
}


XARGS(GameMemory* memory, GameState* gameState, PlatformStorage* platformStorage)
extern "C" GAME_UPDATE(Game_Update)
{
	if (!gameState->initialized)
	{
		gameState->quit = true;
		return;
	}


	if (gameState->quit)
	{
		int a = 2;
	}
}