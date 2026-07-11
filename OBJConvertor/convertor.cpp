#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>


#define ASSERT(Expression) if (!(Expression)) {*(int*)0 = 0;}
#define START_POSITIONS_LINE 2
#define START_NORMALS_LINE 3
#define START_TEXTURES_LINE 3
#define START_FACES_LINE 2


int toInt(const std::string& str);


struct FileData
{
	std::vector<std::string> positions;
	std::vector<std::string> textures;
	std::vector<std::string> normals;
	std::vector<std::string> faces;
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






int main(int argc, char* argv[])
{
	std::ifstream file("../resource/Cube_Tri.obj");

	if (!file.is_open())
	{
		std::cout << "Failed to open file\n";
		return 1;
	}



	FileData fileData = {};

	// Load data
	{
		std::string line;
		size_t lineCount = 0;
		while (std::getline(file, line))
		{
			if (line.size() < 2)
			{
				std::cout << "Line[" << lineCount << "] is invalid !\n";
				lineCount++;
				continue;
			}

			char c0 = line[0];
			char c1 = line[1];

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

		file.close();
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

					std::string vertexLine =  fileData.positions[key.p - 1] + "|";
					            vertexLine += fileData.textures [key.t - 1] + "|";
					            vertexLine += fileData.normals  [key.n - 1];
					vertexLines.push_back(vertexLine);
				}
				else
				{
					indices.push_back(iterator->second);
				}
			}
		}
	}


	// Debug
	{
		size_t lineCount = 0;
		for (const std::string& str : vertexLines)
		{
			std::cout << "line[" << lineCount << "] : " << str << std::endl;
			lineCount++;
		}

		size_t indiceCount = 0;
		for (uint32_t index : indices)
		{
			std::cout << "indice[" << indiceCount << "] : " << index << std::endl;
			indiceCount++;
		}
	}


	return 0;
}