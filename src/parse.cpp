#include "parse.h"

// https://www.cs.cmu.edu/~mbz/personal/graphics/obj.html

void Parse::Parser(std::string filename, std::vector<Vertex> vertices, std::vector<Face> faces)
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

        if (typePrefix == "v") // vertex positions
        {
            glm::vec3 vertex;
            ss >> vertex.x >> vertex.y >> vertex.z;
            // std::cout << "- vert :: " << to_string(vertex) << std::endl; //NOTE - for debug
            vertices.push_back({vertex, glm::vec3(0.0f), glm::vec2(0.0f)});
        }
        else if (typePrefix == "f") // vertex face information
        {
            Face face;
            std::string vertexData;
            while (ss >> vertexData)
            {
                std::istringstream vertexIdxInfoStream(vertexData);
                int vertexIndex, texCoordIndex, normalIndex;
                char separator;

                vertexIdxInfoStream >> vertexIndex; // 공백을 기준으로 문자열을 parsing하고, 변수 형식에
                                                    // 맞게 변환
                face.vertexIndex.push_back(vertexIndex - 1);

                if (vertexIdxInfoStream.peek() == '/') // .peek() : 스트림에서 빼오지는 않고 읽기만 한다
                {
                    vertexIdxInfoStream.ignore();
                    if (vertexIdxInfoStream.peek() != '/')
                    {
                        vertexIdxInfoStream >> texCoordIndex;
                        face.texCoordIndex.push_back(texCoordIndex - 1);
                    }
                    if (vertexIdxInfoStream.peek() == '/')
                    {
                        vertexIdxInfoStream.ignore();
                        vertexIdxInfoStream >> normalIndex;
                        face.normalIndex.push_back(normalIndex - 1);
                    }
                }
            }
            faces.push_back(face);
        }
    }
    line = "";
    std::cout << "NOTION : parse vn & vt.\n";
    while (std::getline(file, line))
    {
        if (!rangeLimit)
            break;
        std::istringstream ss(line);
        ss >> typePrefix;

        if (typePrefix == "vn") // vertex normals
        {
            if (!vertices.empty())
            {
                glm::vec3 normal;
                ss >> normal.x >> normal.y >> normal.z;
                // std::cout << "- norm :: " << to_string(normal) << std::endl; // NOTE - for debug
                vertices[vertexNormalIdx].normal = normal;
                vertexNormalIdx++;
            }
        }
        else if (typePrefix == "vt") // vertex textures
        {
            if (!vertices.empty())
            {
                glm::vec2 texCoord;
                ss >> texCoord.x >> texCoord.y;
                // std::cout << "- norm :: " << to_string(texCoord) << std::endl; // NOTE - for debug
                vertices[vertexTexIdx].texCoord = texCoord;
                vertexTexIdx++;
            }
        }

        this->rangeLimit--;
    }
    printVertexInfo(vertices); // FIXME : for debug
}

void Parse::makeVBO(std::vector<Vertex> vertices, std::vector<Face> faces)
{
    // TODO : need to implement code.
}

void Parse::printVertexInfo(std::vector<Vertex> vertices)
{
    std::cout << "*** VERTICES **** :: \n";
    std::vector<Vertex>::iterator iter;
    for (iter = vertices.begin(); iter != vertices.end(); ++iter)
    {
        std::cout << "( ";
        for (int i = 0; i != 3; i++)
        {
            std::cout << iter->vertexPosition[i] << ",";
        }
        std::cout << " / ";
        for (int i = 0; i != 3; i++)
        {
            std::cout << iter->normal[i] << ",";
        }
        std::cout << " / ";
        for (int i = 0; i != 2; i++)
        {
            std::cout << iter->texCoord[i] << ",";
        }
        std::cout << " )\n";
    }
}
