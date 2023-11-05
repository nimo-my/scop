#include "parse.h"

// https://www.cs.cmu.edu/~mbz/personal/graphics/obj.html

void Parse::Parser(std::string filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cout << "Error! :: " << filename << " can't be opened.";
        exit(1);
    }
    std::cout << "NOTION : open available.\n";

    std::cout << "NOTION : parse v & f.\n";
    std::string line = "";
    while (std::getline(file, line))
    {
        std::istringstream ss(line);
        ss >> typePrefix;

        std::cout << "****TYPE : " << typePrefix << "\n";
        if (typePrefix == "v") // vertex positions
        {
            glm::vec3 vertex;
            ss >> vertex.x >> vertex.y >> vertex.z;
            std::cout << "- vert :: " << to_string(vertex) << " // range limit :: "<< rangeLimit<< std::endl; //NOTE - for debug
            vertexPosition.push_back(vertex);
            rangeLimit++;
        }
        else if (typePrefix == "f") // vertex face information
        {
            std::string vertexData;
            while (ss >> vertexData)
            {
                std::istringstream vertexIdxInfoStream(vertexData);
                int vertexIndex, texCoordIndex, normalIndex;
                char separator;

                vertexIdxInfoStream >> vertexIndex; // 공백을 기준으로 문자열을 parsing하고, 변수 형식에
                                                    // 맞게 변환
                vertexIndex.push_back(vertexIndex - 1);

                if (vertexIdxInfoStream.peek() == '/') // .peek() : 스트림에서 빼오지는 않고 읽기만 한다
                {
                    vertexIdxInfoStream.ignore();
                    if (vertexIdxInfoStream.peek() != '/') // Vertex Normal
                    {
                        vertexIdxInfoStream >> texCoordIndex;
                        texCoordIndex.push_back(texCoordIndex - 1);
                    }
                    if (vertexIdxInfoStream.peek() == '/') // Vertex Texture
                    {
                        vertexIdxInfoStream.ignore();
                        vertexIdxInfoStream >> normalIndex;
                        normalIndex.push_back(normalIndex - 1);
                    }
                }
            }
        }
        typePrefix = ""; // typePrefix 초기화
    }
    std::ifstream file2(filename);
    if (!file2.is_open())
    {
        std::cout << "Error! :: " << filename << " can't be opened.";
        exit(1);
    }
    std::cout << "NOTION : open available.\n";
    line = "";
    std::cout << "NOTION : parse vn & vt, range limit :: " <<rangeLimit <<"\n";
    while (std::getline(file2, line))
    {
        if (!rangeLimit)
            break;
        std::istringstream ss(line);
        ss >> typePrefix;
        if (!vertices.empty())
        {
            if (typePrefix == "vn") // vertex normals
            {
                glm::vec3 normal;
                ss >> normal.x >> normal.y >> normal.z;
                // std::cout << "- norm :: " << to_string(normal) << std::endl; // NOTE - for debug
                this->normal = normal;
                vertexNormalIdx++;
            }
            else if (typePrefix == "vt") // vertex textures
            {
                glm::vec2 texCoord;
                ss >> texCoord.x >> texCoord.y;
                // std::cout << "- text :: " << to_string(texCoord) << std::endl; // NOTE - for debug
                this->texCoord = texCoord;
                vertexTexIdx++;
            }
        }
        this->rangeLimit--;
        typePrefix = ""; // typePrefix 초기화
    }
    // printVertexInfo(vertices); // FIXME : for debug
}

void Parse::makeVBO()
{
    // TODO : need to implement code.
}

// void Parse::printVertexInfo(std::vector<Vertex> vertices)
// {
//     std::cout << "*** VERTICES **** :: \n";
//     std::vector<Vertex>::iterator iter;
//     for (iter = vertices.begin(); iter != vertices.end(); ++iter)
//     {
//         std::cout << "( ";
//         for (int i = 0; i != 3; i++)
//         {
//             std::cout << iter->vertexPosition[i] << ",";
//         }
//         std::cout << " / ";
//         for (int i = 0; i != 3; i++)
//         {
//             std::cout << iter->normal[i] << ",";
//         }
//         std::cout << " / ";
//         for (int i = 0; i != 2; i++)
//         {
//             std::cout << iter->texCoord[i] << ",";
//         }
//         std::cout << " )\n";
//     }
// }
