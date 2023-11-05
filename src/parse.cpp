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
            while (ss >> vertexData)
            {
                std::istringstream vertexIdxInfoStream(vertexData);
                float vertexIdx, textureIdx, normalIdx;
                char separator;

                vertexIdxInfoStream >> vertexIdx; // 공백을 기준으로 문자열을 parsing하고, 변수 형식에
                                                    // 맞게 변환
                this->faceVertexIndex.push_back(vertexIdx - 1);

                if (vertexIdxInfoStream.peek() == '/') // .peek() : 스트림에서 빼오지는 않고 읽기만 한다
                {
                    vertexIdxInfoStream.ignore();
                    if (vertexIdxInfoStream.peek() != '/') // Vertex Normal
                    {
                        vertexIdxInfoStream >> textureIdx;
                        faceTexCoordIndex.push_back(textureIdx - 1);
                    }
                    if (vertexIdxInfoStream.peek() == '/') // Vertex Texture
                    {
                        vertexIdxInfoStream.ignore();
                        vertexIdxInfoStream >> normalIdx;
                        faceNormalIndex.push_back(normalIdx - 1);
                    }
                }
            }
        }
        else if (typePrefix == "mtllib")
            parseMtlFile();
        typePrefix = ""; // typePrefix 초기화
    }
    
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
    // TODO : need to implement code.
}

void Parse::printVertexInfo()
{
    std::cout << "*** VERTICES **** :: \n";
    std::vector<float>::iterator iter;
    // std::cout << "1) vertex Position : ";
    // for (iter = vertexPosition.begin(); iter != vertexPosition.end(); ++iter)
    // {
    //    std::cout << *iter << " ";
    // }
    // std::cout << "\n2) vertex Normal : ";
    // std::vector<float>::iterator iter2;
    // for (iter2 = vertexNormal.begin(); iter2 != vertexNormal.end(); ++iter2)
    // {
    //    std::cout << *iter2 << " ";
    // }
    // std::cout << "\n3) vertex Texture coord : ";
    // std::vector<float>::iterator iter3;
    // for (iter3 = vertexTexCoord.begin(); iter3 != vertexTexCoord.end(); ++iter3)
    // {
    //    std::cout << *iter3 << " ";
    // }
    // std::cout << "\n4) vertex idx : ";
    // std::vector<size_t>::iterator iter4;
    // for (iter4 = faceVertexIndex.begin(); iter4 != faceVertexIndex.end(); ++iter4)
    // {
    //    std::cout << *iter4 << " ";
    // }
    // std::cout << "\n5) normal idx : ";
    // std::vector<size_t>::iterator iter5;
    // for (iter5 = faceNormalIndex.begin(); iter5 != faceNormalIndex.end(); ++iter5)
    // {
    //    std::cout << *iter5 << " ";
    // }
    // std::cout << "\n6) textcoord idx : ";
    // std::vector<size_t>::iterator iter6;
    // for (iter6 = faceTexCoordIndex.begin(); iter6 != faceTexCoordIndex.end(); ++iter6)
    // {
    //    std::cout << *iter6 << " ";
    // }
    std::cout << "\n7) attribute idx : ";
    std::vector<float>::iterator iter7;
    for (iter7 = attribute.begin(); iter7 != attribute.end(); ++iter7)
    {
       std::cout << *iter7 << " ";
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