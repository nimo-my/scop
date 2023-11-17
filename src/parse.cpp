#include "parse.h"

Parse::Parse() : mtlInfo(""), typePrefix("")
{
}

std::unique_ptr<float[]> Parse::Parser(std::string filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cout << "Error! :: " << filename << " can't be opened.";
        exit(1);
    }

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

            vertexPosition.push_back(buffer);
        }
        else if (typePrefix == "vn") // vertex normals
        {
            float vn1 = 0.0f, vn2 = 0.0f, vn3 = 0.0f;
            ss >> vn1 >> vn2 >> vn3;
            glm::vec3 buffer;
            buffer[0] = vn1;
            buffer[1] = vn2;
            buffer[2] = vn3;
            this->vertexNormal.push_back(buffer);
        }
        else if (typePrefix == "vt") // vertex textures
        {
            float vt1 = 0.0f, vt2 = 0.0f;
            ss >> vt1 >> vt2;

            glm::vec2 buffer;
            buffer[0] = vt1;
            buffer[1] = vt2;
            this->vertexTexCoord.push_back(buffer);
        }
        else if (typePrefix == "f") // vertex face information
        {
            std::size_t vertexIdx1 = 0, vertexIdx2 = 0, vertexIdx3 = 0, vertexIdx4 = 0;
            ss >> vertexIdx1 >> vertexIdx2 >> vertexIdx3 >> vertexIdx4;

            if (!ss >> vertexIdx4)
            {
                this->faces.push_back(glm::vec3{vertexIdx1, vertexIdx2, vertexIdx3});
            }
            else
            {
                this->faces.push_back(glm::vec3{vertexIdx1, vertexIdx2, vertexIdx3});
                this->faces.push_back(glm::vec3{vertexIdx1, vertexIdx3, vertexIdx4});
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
    return (makeVBO());
}

void Parse::parseMtlFile()
{
    // file이름 지정 및 파일 오픈
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

void Parse::makeTexture()
{
    glm::vec2 max = glm::vec2();
    glm::vec2 min = glm::vec2();

    // y 축 하나 없애기 -> x의 Min, max, z의 min, max 구하기 (vertex 돌면서)
    for (glm::vec3 vec : vertexPosition)
    {
        max[0] = max[0] > vec[0] ? max[0] : vec[0]; // x축 max
        max[1] = max[1] > vec[1] ? max[1] : vec[1]; // y축 max

        min[0] = min[0] < vec[0] ? min[0] : vec[0]; // x축 min
        min[1] = min[1] < vec[1] ? min[1] : vec[1]; // y축 min
    }

    float xLength = max[0] - min[0];
    float yLength = max[1] - min[1];
    float xMin = min[0];
    float yMin = min[1];

    std::cout << "(xLength :: " << xLength << ", yLength :: " << yLength << ", xMin :: " << xMin << ", yMin :: " << yMin
              << ") " << std::endl;

    // 나온 값을 정규화(클리핑) 공식에 대입하기 (min-max scaler)
    // 나온 값을 vertexTexture 에 넣기
    vertexTexCoord.clear();
    vertexTexCoord.assign(vertexPosition.size(), glm::vec2());
    for (int vertexIdx = 0; vertexIdx < vertexPosition.size(); vertexIdx++)
    {
        vertexTexCoord[vertexIdx].x = (vertexPosition[vertexIdx].x - xMin) / xLength;
        vertexTexCoord[vertexIdx].y = (vertexPosition[vertexIdx].y - yMin) / yLength;
    }
}

void Parse::makeVertexNormal()
{
    vertexNormal.clear();
    vertexNormal.assign(vertexPosition.size(), glm::vec3());

    for (glm::vec3 line : faces) // line : v의 index number(삼각형으로 쪼개준 상태)
    {
        normalizing(line); // make vertex normal
    }
    for (glm::vec3 &vn : vertexNormal)
    {
        vn = glm::normalize(vn);
    }
}

std::unique_ptr<float[]> Parse::makeVBO()
{
    // 만약 vertexNormal 이 존재하지 않으면, 만들어줌.
    if (!vertexNormal.size())
    {
        makeVertexNormal();
    }

    makeTexture(); // 텍스쳐 클리핑해서 넣기

    // vbo array 만들기
    size_t size = faces.size();
    auto VBO = std::unique_ptr<float[]>(new float[size * 8 * 3]);

    // FIXME
    std::string line;
    std::ofstream file("output.txt");

    if (file.is_open())
    {
        for (int LineIdx = 0; LineIdx < size; LineIdx++)
        {
            for (int idx = 0; idx < 3; idx++)
            {
                std::size_t vertexIdx = faces[LineIdx][idx];
                VBO[(LineIdx * 8 * 3) + (idx * 8)] = vertexPosition[vertexIdx - 1].x;
                VBO[(LineIdx * 8 * 3) + (idx * 8) + 1] = vertexPosition[vertexIdx - 1].y;
                VBO[(LineIdx * 8 * 3) + (idx * 8) + 2] = vertexPosition[vertexIdx - 1].z;

                VBO[(LineIdx * 8 * 3) + (idx * 8) + 3] = vertexNormal[vertexIdx - 1].x;
                VBO[(LineIdx * 8 * 3) + (idx * 8) + 4] = vertexNormal[vertexIdx - 1].y;
                VBO[(LineIdx * 8 * 3) + (idx * 8) + 5] = vertexNormal[vertexIdx - 1].z;

                VBO[(LineIdx * 8 * 3) + (idx * 8) + 6] = vertexTexCoord[vertexIdx - 1].x;
                VBO[(LineIdx * 8 * 3) + (idx * 8) + 7] = vertexTexCoord[vertexIdx - 1].y;

                file << VBO[(LineIdx * 8 * 3) + (idx * 8)] << "\n";
                file << VBO[(LineIdx * 8 * 3) + (idx * 8) + 1] << "\n";
                file << VBO[(LineIdx * 8 * 3) + (idx * 8) + 2] << "\n\n";

                // file << VBO[(LineIdx * 8 * 3) + (idx * 8) + 3] << "\n";
                // file << VBO[(LineIdx * 8 * 3) + (idx * 8) + 4] << "\n";
                // file << VBO[(LineIdx * 8 * 3) + (idx * 8) + 5] << "\n\n";

                // file << VBO[(LineIdx * 8 * 3) + (idx * 8) + 6] << "\n";
                // file << VBO[(LineIdx * 8 * 3) + (idx * 8) + 7] << "\n\n";
            }
        }
    }

    return (std::move(VBO));
}

void Parse::normalizing(glm::vec3 facesLine) // v 5 7 1
{
    // 점 3개
    glm::vec3 v1 = vertexPosition[facesLine[0] - 1];
    glm::vec3 v2 = vertexPosition[facesLine[1] - 1];
    glm::vec3 v3 = vertexPosition[facesLine[2] - 1];

    // 두 점끼리 이어서 벡터를 만듦
    glm::vec3 vec1 = {v2[0] - v1[0], v2[1] - v1[1], v2[2] - v1[2]};
    glm::vec3 vec2 = {v3[0] - v1[0], v3[1] - v1[1], v3[2] - v1[2]};

    glm::vec3 normal = glm::normalize(glm::cross(vec1, vec2));
    // std::cout << "normal : " << glm::to_string(normal) << std::endl;

    vertexNormal[facesLine[0] - 1] += normal;
    vertexNormal[facesLine[1] - 1] += normal;
    vertexNormal[facesLine[2] - 1] += normal;
}

void Parse::setFileName(std::string name)
{
    this->filename = name;
}

std::string Parse::getFileName()
{
    return (this->filename);
}