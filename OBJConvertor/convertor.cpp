#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include "windows.h"


#define ASSERT(Expression) if (!(Expression)) {*(int*)0 = 0;}
#define START_POSITIONS_LINE 2
#define START_NORMALS_LINE 3
#define START_TEXTURES_LINE 3
#define START_FACES_LINE 2
#define IN_RESOURCE_PATH "C:\\Antrum\\resource\\meshes\\dirty\\"
#define OUT_RESOURCE_PATH "C:\\Antrum\\resource\\meshes\\clean\\"
#define INDICES_PER_LINE 50
#define CLOSE_FILE_CHAR 'x'
#define BUILD_PATH "C:\\Antrum\\build.bat"
#define BUILD_ANCHOR_BEGIN "set MeshFlags=^" // Used to find the end of the text to replace in Antrum's build.bat
#define BUILD_ANCHOR_END "::XIN_A" 
#define MESHES_MACRO_PATH "C:\\Antrum\\meshes_macro.h"
#define VERTICES_SIZE_APPENDIX "_V_SIZE"
#define INDICES_SIZE_APPENDIX "_I_SIZE"


int toInt(const std::string& str);


struct FileData
{
	std::vector<std::string> positions;
	std::vector<std::string> textures;
	std::vector<std::string> normals;
	std::vector<std::string> faces;

	std::string name;
};

struct Key
{
	int p;
	int t;
	int n;

	std::string toString() const
	{
		std::string res = "";		
		res += std::to_string(p) + "/";
		res += std::to_string(t) + "/";
		res += std::to_string(n);

		return res;
	}

	bool operator==(const Key& k) const
	{
		return p == k.p && t == k.t && n == k.n;
	}
};

struct KeyHash
{
	size_t operator()(const Key& key) const noexcept
	{
		size_t k1 = std::hash<int>{}(key.p);
		size_t k2 = std::hash<int>{}(key.t);
		size_t k3 = std::hash<int>{}(key.n);

		return k1 ^ (k2 << 1) ^ (k3 << 2);
	}
};

struct MeshSizeData
{
	uint32_t verticesCount;
	uint32_t indicesCount;
};

struct MeshData
{
	std::string name;
	MeshSizeData size;
};






// >NOTE: the string must be formatted so there are no trailing spaces!!
std::vector<std::string> split(const std::string& str, char separator)
{
	ASSERT(!str.empty() && str[str.size() - 1] != separator);

	std::vector<std::string> res;
	size_t pos = 0;
	size_t count = 0;
	for (size_t i = 0; i < str.size(); i++)
	{
		if (str[i] == separator)
		{
			res.push_back(str.substr(pos, count));
			pos = i + 1;
			count = 0;
			continue;
		}

		count++;
	}

	res.push_back(str.substr(pos, count));
	return res;
}

uint8_t toDigit(char c)
{
	return uint8_t(c - '0');
}

int toInt(const std::string& str)
{
	ASSERT(!str.empty());

	bool negative = str[0] == '-';
	int integer = 0;
	uint8_t counter = negative ? 1 : 0;

	for (counter; counter < str.size(); counter++)
	{
		integer = integer * 10 + toDigit(str[counter]);
	}

	if (negative)
	{
		integer *= -1;
	}

	return integer;
}


// >NOTE: has to be formatted as such: int/int/int, e.g. 2/43/8
//        will return Key as such: p/t/n
Key toKey(const std::string& str)
{
	std::vector<std::string> res = split(str, '/');
	int p = toInt(res[0]);
	int t = toInt(res[1]);
	int n = toInt(res[2]);
	
	return { p, t, n };
}

void toUpper(std::string& str)
{
	for (size_t i = 0; i < str.size(); i++)
	{
		str[i] = (char)std::toupper((int)str[i]);
	}
}


MeshSizeData convertFile(const std::string& fileName)
{
	std::ifstream inFile(std::string(IN_RESOURCE_PATH) + fileName);

	if (!inFile.is_open())
	{
		std::cout << "ERROR | Failed to open file\n";
		return { 0, 0 };
	}


	FileData fileData = {};

	// Load data
	{
		std::string line;
		size_t lineCount = 0;
		while (std::getline(inFile, line))
		{
			if (line.size() < 2)
			{
				std::cout << "Line[" << lineCount << "] is invalid !\n";
				lineCount++;
				continue;
			}

			const char c0 = line[0];
			const char c1 = line[1];

			if (c0 == 'v')
			{
				if (c1 == 'n')
				{
					fileData.normals.push_back(line.substr(START_NORMALS_LINE, line.size() - 1));
				}
				else if (c1 == 't')
				{
					fileData.textures.push_back(line.substr(START_TEXTURES_LINE, line.size() - 1));
				}
				else if (c1 == ' ')
				{
					fileData.positions.push_back(line.substr(START_POSITIONS_LINE, line.size() - 1));
				}
			}
			else if (c0 == 'f')
			{
				fileData.faces.push_back(line.substr(START_FACES_LINE, line.size() - 1));
			}


			lineCount++;
		}

		inFile.close();
	}



	std::unordered_map<Key, uint32_t, KeyHash> vertexMap; // Only used to check the uniqueness of face corners
	std::vector<std::string>                   vertexLines;
	std::vector<uint32_t>                      indices;

	// OBJ -> GPU representation
	// 
	// We extract and store as GPU vertices only the unique vertices described in the OBJ's faces data
	// On the other hand, we store one indice per OBJ face corner, including duplicates
	// 
	// Eventually, for a triangulated cube (12 faces, 8 vertices), we should obtain: 
	//		24 GPU vertices
	//		36 GPU indices
	{
		for (const std::string& faceLine : fileData.faces)
		{
			std::vector<std::string> faceCorners = split(faceLine, ' ');
			for (const std::string& corner : faceCorners)
			{
				Key key = toKey(corner);
				auto iterator = vertexMap.find(key);
				if (iterator == vertexMap.end())
				{
					const uint32_t index = (uint32_t)vertexLines.size();
					vertexMap.insert({ key, index });

					indices.push_back(index);

					std::string vertexLine = fileData.positions[key.p - 1] + "|";
					vertexLine            += fileData.textures [key.t - 1] + "|";
					vertexLine            += fileData.normals  [key.n - 1];
					vertexLines.push_back(vertexLine);
				}
				else
				{
					indices.push_back(iterator->second);
				}
			}
		}
	}


	// Write .xin file
	{
		// Swap obj for xin
		std::string xinFileName = fileName;
		const size_t strSize = xinFileName.size();
		xinFileName[strSize - 3] = 'x';
		xinFileName[strSize - 2] = 'i';
		xinFileName[strSize - 1] = 'n';

		std::string path = std::string(OUT_RESOURCE_PATH) + xinFileName;
		std::ofstream outFile(path);
		if (!outFile)
		{
			std::cout << "ERROR | Could not write into " << path << std::endl;
			return { 0, 0 };
		}

		if (outFile.is_open())
		{
			for (const std::string& vLine : vertexLines)
			{
				outFile << vLine << std::endl;
			}

			outFile << "I\n";

			for (uint32_t i = 0; i < indices.size(); i++)
			{
				if (i % INDICES_PER_LINE == 0)
				{
					if (i != 0)
					{
						outFile << "\n";
					}
				}
				else
				{
					outFile << "|";
				}

				outFile << indices[i];
			}
		}

		outFile << CLOSE_FILE_CHAR;
		outFile.close();
	}

	return { (uint32_t)vertexLines.size(), (uint32_t)indices.size() };
}





int main(int argc, char* argv[])
{
	std::vector<MeshData> meshes;

	// Convert files from .obj to .xin
	{
		std::string dirPath = std::string(IN_RESOURCE_PATH) + "*obj";
		WIN32_FIND_DATA findData = {};
		HANDLE findHandle = FindFirstFile(dirPath.c_str(), &findData);

		if (findHandle == INVALID_HANDLE_VALUE)
		{
			std::cout << "ERROR | Failed to open file (" << GetLastError() << ")\n";
			return 1;
		}

		do
		{
			MeshData mesh = {};
			mesh.name = findData.cFileName;
			mesh.name.resize(mesh.name.size() - 4); // Removes .obj
			toUpper(mesh.name);

			mesh.size = convertFile(findData.cFileName);

			meshes.push_back(mesh);
		} 
		while (FindNextFile(findHandle, &findData));
		FindClose(findHandle);
	}
	

	// >NOTASCOI: idk why I thought of this approach first when the second one is better is every possible way.
	//            Let this be a reminder of the proportions of my stupidity, and potentially some reusable code.
	// 
	// Rewrites the build file for Antrum to update the mesh size data
	/* {
		std::ifstream inFile(BUILD_PATH);
		if (!inFile.is_open())
		{
			std::cout << "ERROR | Failed to open Antrum's build.bat file\n";
			return 1;
		}

		std::stringstream buffer;
		buffer << inFile.rdbuf();
		std::string fileContent = buffer.str();
		inFile.close();


		std::string flags = "\n";
		for (size_t i = 0; i < meshes.size(); i++)
		{
			const MeshData& mesh = meshes[i];

			flags += "-D" + mesh.name + std::string(VERTICES_SIZE_APPENDIX) + "=" + std::to_string(mesh.size.verticesCount) + " ^ \n";

			// We don't want to add ^ at the last line
			if (i == meshes.size() - 1)
			{
				flags += "-D" + mesh.name + std::string(INDICES_SIZE_APPENDIX) + "=" + std::to_string(mesh.size.indicesCount) + "\n";
			}
			else
			{
				flags += "-D" + mesh.name + std::string(INDICES_SIZE_APPENDIX) + "=" + std::to_string(mesh.size.indicesCount) + " ^ \n";
			}
		}


		size_t beginAnchorPos = fileContent.find(std::string(BUILD_ANCHOR_BEGIN));
		if (beginAnchorPos == std::string::npos)
		{
			std::cout << "ERROR | Could not find " << BUILD_ANCHOR_BEGIN << " :(\n";
			return 1;
		}

		// Moving past the anchor
		beginAnchorPos += std::string(BUILD_ANCHOR_BEGIN).size();

		size_t endAnchorPos = fileContent.find(std::string(BUILD_ANCHOR_END), beginAnchorPos);
		if (endAnchorPos == std::string::npos)
		{
			std::cout << "ERROR | Could not find " << BUILD_ANCHOR_END << " :(\n";
			return 1;
		}

		// Replace everything between BUILD_ANCHOR_BEGIN and BUILD_ANCHOR_END with the content of flags
		fileContent.replace(beginAnchorPos, endAnchorPos - beginAnchorPos, flags);

		// Rewrite Antrum's build.bat
		std::ofstream outFile(BUILD_PATH, std::ios::binary);
		if (!outFile)
		{
			std::cout << "ERROR | Failed to rewrite Antrum's build.bat file\n";
			return 1;
		}

		outFile << fileContent;
		outFile.close();
	}*/



	// Rewrites mesh_macro.h for Antrum to update all the macro containing the meshes size data
	{
		std::ofstream outFile(MESHES_MACRO_PATH);
		if (!outFile.is_open())
		{
			std::cout << "ERROR | Failed to open " << std::string(MESHES_MACRO_PATH) << std::endl;
			return 1;
		}

		std::string content = "";
		for (const MeshData& mesh : meshes)
		{
			content += "#define " + mesh.name + std::string(VERTICES_SIZE_APPENDIX) + " " + std::to_string(mesh.size.verticesCount) + "\n";
			content += "#define " + mesh.name + std::string(INDICES_SIZE_APPENDIX)  + " " + std::to_string(mesh.size.indicesCount)  + "\n";
		}

		outFile << content;
		outFile.close();
	}
	

	return 0;
}