#include "parse.h"

// https://www.cs.cmu.edu/~mbz/personal/graphics/obj.html

Parse::Parse() : mtlInfo(""), typePrefix(""), vertexNormalIdx(0), vertexTexIdx(0), rangeLimit(0)
{
}

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

        if (typePrefix == "v") // vertex positions
        {
            float vert1 = 0.0f, vert2 = 0.0f, vert3 = 0.0f;
            ss >> vert1 >> vert2 >> vert3;
            glm::vec3 buffer;

            buffer[0] = vert1;
            buffer[1] = vert2;
            buffer[2] = vert3;
            rangeLimit++;
            vertexPosition.push_back(buffer);
        }
        else if (typePrefix == "f") // vertex face information
        {
            std::size_t vertexIdx1 = 0, vertexIdx2 = 0, vertexIdx3 = 0, vertexIdx4 = 0;
            ss >> vertexIdx1 >> vertexIdx2 >> vertexIdx3 >> vertexIdx4;
            
            std::cout << ":::: vertexData : (" << vertexIdx1 <<","<< vertexIdx2 <<","<< vertexIdx3 <<","<< vertexIdx4 << ")" << std::endl;
            glm::vec3 vertexBuffer;
            
            if (!ss >> vertexIdx4)
            {
                vertexBuffer = {vertexIdx1 - 1, vertexIdx2 - 1, vertexIdx3 - 1};
                this->faces.push_back(vertexBuffer);
            }
            else
            {
                this->faces.push_back(glm::vec3{vertexIdx1 - 1, vertexIdx2 - 1, vertexIdx3 - 1});
                this->faces.push_back(glm::vec3{vertexIdx1 - 1, vertexIdx3 - 1, vertexIdx4 - 1});
            }

            // if (vertexIdxInfoStream.peek() == '/') // .peek() : 스트림에서 빼오지는 않고 읽기만 한다
            // {
            //     vertexIdxInfoStream.ignore();
            //     if (vertexIdxInfoStream.peek() != '/') // Vertex Normal
            //     {
            //         vertexIdxInfoStream >> textureIdx;
            //         vertexBuffer.push_back(textureIdx - 1);
            //     }
            //     if (vertexIdxInfoStream.peek() == '/') // Vertex Texture
            //     {
            //         vertexIdxInfoStream.ignore();
            //         vertexIdxInfoStream >> normalIdx;
            //         vertexBuffer.push_back(normalIdx - 1);
            //     }
            // }

        }
        else if (typePrefix == "mtllib")
            parseMtlFile();
        typePrefix = ""; // typePrefix 초기화
    }
    file.close();

    std::ifstream file2(filename);
    if (!file2.is_open())
    {
        std::cout << "Error! :: " << filename << " can't be opened.";
        exit(1);
    }
    line = "";
    while (std::getline(file2, line))
    {
        std::istringstream ss(line);
        ss >> typePrefix;
        if (!this->vertexPosition.empty())
        {
            if (typePrefix == "vn") // vertex normals
            {
                float vn1 = 0.0f, vn2 = 0.0f, vn3 = 0.0f;
                ss >> vn1 >> vn2 >> vn3;
                if (rangeLimit == vertexNormalIdx)
                    break;
                else
                {
                    glm::vec3 buffer;
                    buffer[0] = vn1;
                    buffer[1] = vn2;
                    buffer[2] = vn3;
                    this->vertexNormal.push_back(buffer);
                    vertexNormalIdx++;
                }
            }
            else if (typePrefix == "vt") // vertex textures
            {
                float vt1 = 0.0f, vt2 = 0.0f, vt3 = 0.0f;
                ss >> vt1 >> vt2 >> vt3;
                if (rangeLimit == vertexTexIdx)
                    break;
                else
                {
                    glm::vec3 buffer;
                    buffer[0] = vt1;
                    buffer[1] = vt2;
                    buffer[2] = vt3;
                    this->vertexTexCoord.push_back(buffer);
                    vertexTexIdx++;
                }
            }
        }
        typePrefix = ""; // typePrefix 초기화
    }

    file2.close();
    printVertexInfo(); // FIXME : for debug
    makeVBO();
    // texture
}

void Parse::parseMtlFile()
{
    std::string mtlFileName = this->filename;
    mtlFileName += ".mtl";
    std::ifstream file(mtlFileName);
    if (!file.is_open())
    {
        std::cout << "Error! :: " << mtlFileName << " can't be opened.";
        exit(1);
    }
    std::string line = "";
    while (std::getline(file, line))
    {
        std::istringstream ss(line);
        ss >> typePrefix;

        if (typePrefix == "Ka") // vertex positions
        {
            float vert1, vert2, vert3;
            ss >> vert1 >> vert2 >> vert3;
            attribute[0] = vert1;
            attribute[1] = vert2;
            attribute[2] = vert3;
            rangeLimit++;
        }
        else if (typePrefix == "Kd") // vertex face information
        {
            float vert1, vert2, vert3;
            ss >> vert1 >> vert2 >> vert3;
            diffuse[0] = vert1;
            diffuse[1] = vert2;
            diffuse[2] = vert3;
        }
        else if (typePrefix == "Ks")
        {
            float vert1, vert2, vert3;
            ss >> vert1 >> vert2 >> vert3;
            specular[0] = vert1;
            specular[1] = vert2;
            specular[2] = vert3;
        }
        typePrefix = "";
    }
}

void Parse::makeVBO()
{
    normals.resize(faces.size());
    for (glm::vec3 line : faces)
    {
        normalizing(line); // make vertex normal
    }
}

void Parse::normalizing(glm::vec3 facesLine)
{
    glm::vec3 v1 = vertexPosition[facesLine[0]];
    glm::vec3 v2 = vertexPosition[facesLine[1]];
    glm::vec3 v3 = vertexPosition[facesLine[2]];

    glm::vec3 vec1 = {v2[0] - v1[0], v2[1] - v1[1], v2[2] - v1[2]};
    glm::vec3 vec2 = {v3[0] - v1[0], v3[1] - v1[1], v3[2] - v1[2]};

    glm::vec3 crossed = glm::cross(vec1, vec2);
    glm::vec3 normal = glm::normalize(crossed);
    // std::cout << glm::to_string(normal) << std::endl;
    
    normals[facesLine[0]] = glm::normalize(normal + v1);
    normals[facesLine[1]] = glm::normalize(normal + v2);
    normals[facesLine[2]] = glm::normalize(normal + v3);
}

void Parse::printVertexInfo()
{
    // std::cout << "*** VERTICES **** :: \n";
    // std::vector<float>::iterator iter;
    // std::cout << "1) vertex Position : ";
    // for (iter = vertexPosition.begin(); iter != vertexPosition.end(); ++iter)
    // {
    //     std::cout << *iter << " ";
    // }
    // std::cout << "\n2) vertex Normal : ";
    // std::vector<float>::iterator iter2;
    // for (iter2 = vertexNormal.begin(); iter2 != vertexNormal.end(); ++iter2)
    // {
    //     std::cout << *iter2 << " ";
    // }
    // std::cout << "\n3) vertex Texture coord : ";
    // std::vector<float>::iterator iter3;
    // for (iter3 = vertexTexCoord.begin(); iter3 != vertexTexCoord.end(); ++iter3)
    // {
    //     std::cout << *iter3 << " ";
    // }
    // std::cout << "\n4) vertex idx : ";
    // std::vector<float>::iterator iter7;
    // for (iter7 = attribute.begin(); iter7 != attribute.end(); ++iter7)
    // {
    //     std::cout << *iter7 << " ";
    // }

    // std::cout << "\n8) diffuse idx : ";
    // std::vector<float>::iterator iter8;
    // for (iter8 = diffuse.begin(); iter8 != diffuse.end(); ++iter8)
    // {
    //     std::cout << *iter8 << " ";
    // }
    // std::cout << "\n9) specular idx : ";
    // std::vector<float>::iterator iter9;
    // for (iter9 = specular.begin(); iter9 != specular.end(); ++iter9)
    // {
    //     std::cout << *iter9 << " ";
    // }
}

void Parse::setFileName(std::string name)
{
    this->filename = name;
}

std::string Parse::getFileName()
{
    return (this->filename);
}