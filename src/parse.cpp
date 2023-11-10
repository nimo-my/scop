#include "parse.h"

// https://www.cs.cmu.edu/~mbz/personal/graphics/obj.html

Parse::Parse()
: mtlInfo(""), typePrefix(""), vertexNormalIdx(0), vertexTexIdx(0), rangeLimit(0)
{}

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
            vertexPosition.push_back(vert1);
            vertexPosition.push_back(vert2);
            vertexPosition.push_back(vert3);
            rangeLimit++;
        }
        else if (typePrefix == "f") // vertex face information
        {
            std::string vertexData;
            std::vector<size_t> vertexBuffer;
            while (ss >> vertexData)
            {
                std::cout << vertexData << std::endl;
                std::istringstream vertexIdxInfoStream(vertexData);
                float vertexIdx, textureIdx, normalIdx;

                vertexIdxInfoStream >> vertexIdx; // 공백을 기준으로 문자열을 parsing
                vertexBuffer.push_back(vertexIdx - 1); // while문 돌면서 f 뒤에 오는 인자 하나씩 넣어주기
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
            if (vertexBuffer.size() == 3)
                this->faces.push_back(vertexBuffer);
            else if (vertexBuffer.size() == 4)
            {
                this->faces.push_back(std::vector<size_t>{vertexBuffer[0], vertexBuffer[1], vertexBuffer[2]});
                this->faces.push_back(std::vector<size_t>{vertexBuffer[0], vertexBuffer[2], vertexBuffer[3]});
                
            }
            vertexBuffer.clear();
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
                    this->vertexNormal.push_back(vn1);
                    this->vertexNormal.push_back(vn2);
                    this->vertexNormal.push_back(vn3);
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
                    this->vertexTexCoord.push_back(vt1);
                    this->vertexTexCoord.push_back(vt2);
                    this->vertexTexCoord.push_back(vt3);
                    vertexTexIdx++;
                }
            }
        }
        typePrefix = ""; // typePrefix 초기화
    }

    file2.close();
    printVertexInfo(); // FIXME : for debug
    makeVBO();
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
            attribute.push_back(vert1);
            attribute.push_back(vert2);
            attribute.push_back(vert3);
            rangeLimit++;
        }
        else if (typePrefix == "Kd") // vertex face information
        {
            float vert1, vert2, vert3;
            ss >> vert1 >> vert2 >> vert3;
            diffuse.push_back(vert1);
            diffuse.push_back(vert2);
            diffuse.push_back(vert3);
        }
        else if (typePrefix == "Ks")
        {
            float vert1, vert2, vert3;
            ss >> vert1 >> vert2 >> vert3;
            specular.push_back(vert1);
            specular.push_back(vert2);
            specular.push_back(vert3);
        }
        typePrefix = "";
    }
}

void Parse::makeVBO()
{
    normalizing();
    // texture
    // TODO : need to implement code.
}

void Parse::normalizing()
{

}

void Parse::printVertexInfo()
{
    std::cout << "*** VERTICES **** :: \n";
    std::vector<float>::iterator iter;
    std::cout << "1) vertex Position : ";
    for (iter = vertexPosition.begin(); iter != vertexPosition.end(); ++iter)
    {
       std::cout << *iter << " ";
    }
    std::cout << "\n2) vertex Normal : ";
    std::vector<float>::iterator iter2;
    for (iter2 = vertexNormal.begin(); iter2 != vertexNormal.end(); ++iter2)
    {
       std::cout << *iter2 << " ";
    }
    std::cout << "\n3) vertex Texture coord : ";
    std::vector<float>::iterator iter3;
    for (iter3 = vertexTexCoord.begin(); iter3 != vertexTexCoord.end(); ++iter3)
    {
       std::cout << *iter3 << " ";
    }
    std::cout << "\n4) vertex idx : ";
    std::vector<float>::iterator iter7;
    for (iter7 = attribute.begin(); iter7 != attribute.end(); ++iter7)
    {
       std::cout << *iter7 << " ";
    }

    std::cout << "\n5) faces size: " << faces.size() << "\n";
    
    for (size_t i = 0; i < faces.size(); i++)
    {

    }

    std::cout << "\n8) diffuse idx : ";
    std::vector<float>::iterator iter8;
    for (iter8 = diffuse.begin(); iter8 != diffuse.end(); ++iter8)
    {
       std::cout << *iter8 << " ";
    }
    std::cout << "\n9) specular idx : ";
    std::vector<float>::iterator iter9;
    for (iter9 = specular.begin(); iter9 != specular.end(); ++iter9)
    {
       std::cout << *iter9 << " ";
    }
}

void Parse::setFileName(std::string name)
{
    this->filename = name;
}

std::string Parse::getFileName()
{
    return (this->filename);
}