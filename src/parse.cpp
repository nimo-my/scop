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
            ft::vec3 buffer;

            // for center 맞추기(1)
            getMinMaxValue(vert1, vert2, vert3);
            buffer[0] = vert1;
            buffer[1] = vert2;
            buffer[2] = vert3;

            vertexPosition.push_back(buffer);
        }
        else if (typePrefix == "vn") // vertex normals
        {
            float vn1 = 0.0f, vn2 = 0.0f, vn3 = 0.0f;
            ss >> vn1 >> vn2 >> vn3;
            ft::vec3 buffer;
            buffer[0] = vn1;
            buffer[1] = vn2;
            buffer[2] = vn3;
            this->vertexNormal.push_back(buffer);
        }
        else if (typePrefix == "vt") // vertex textures
        {
            float vt1 = 0.0f, vt2 = 0.0f;
            ss >> vt1 >> vt2;

            ft::vec2 buffer;
            buffer[0] = vt1;
            buffer[1] = vt2;
            this->vertexTexCoord.push_back(buffer);
        }
        else if (typePrefix == "f") // vertex face information
        {
            std::string vertexIdx1 = "", vertexIdx2 = "", vertexIdx3 = "", vertexIdx4 = "";
            ss >> vertexIdx1 >> vertexIdx2 >> vertexIdx3 >> vertexIdx4;

            removeSlash(vertexIdx1, vertexIdx2, vertexIdx3, vertexIdx4);

            // faces가 3개인 경우와 4개인 경우 분기점
            if (vertexIdx4 == "")
            {
                this->faces.push_back(ft::vec3{stof(vertexIdx1), stof(vertexIdx2), stof(vertexIdx3)});
            }
            else
            {
                this->faces.push_back(ft::vec3{stof(vertexIdx1), stof(vertexIdx2), stof(vertexIdx3)});
                this->faces.push_back(ft::vec3{stof(vertexIdx1), stof(vertexIdx3), stof(vertexIdx4)});
            }
        }
        else if (typePrefix == "mtllib")
            parseMtlFile();
        typePrefix.clear();
    }

    // center 맞추기(2)
    auto xDist = ((vertexXMax + vertexXMin) / 2.0f);
    auto yDist = ((vertexYMax + vertexYMin) / 2.0f);
    auto zDist = ((vertexZMax + vertexZMin) / 2.0f);
    centerizeObj(xDist, yDist, zDist);

    file.close();
    return (makeVBO());
}

void Parse::centerizeObj(float xDist, float yDist, float zDist)
{
    for (size_t i = 0; i < vertexPosition.size(); i++)
    {
        vertexPosition[i].x -= xDist;
        vertexPosition[i].y -= yDist;
        vertexPosition[i].z -= zDist;
    }
}

void Parse::getMinMaxValue(float vertexX, float vertexY, float vertexZ)
{
    vertexXMin = vertexXMin < vertexX ? vertexXMin : vertexX;
    vertexXMax = vertexXMax > vertexX ? vertexXMax : vertexX;

    vertexYMin = vertexYMin < vertexY ? vertexYMin : vertexY;
    vertexYMax = vertexYMax > vertexY ? vertexYMax : vertexY;

    vertexZMin = vertexZMin < vertexZ ? vertexZMin : vertexZ;
    vertexZMax = vertexZMax > vertexZ ? vertexZMax : vertexZ;
}

std::vector<size_t> Parse::splitSlash(std::string chunk)
{
    std::vector<size_t> buffer;
    buffer.clear();

    std::string index = "";
    for (size_t i = 0; i < chunk.length(); i++)
    {
        if (chunk[i] == '/')
        {
            buffer.push_back(stoi(index));
            index.clear();
            i++;
        }
        else
            index += chunk[i];
    }

    return (buffer);
}

bool Parse::isSlash(std::string str)
{
    for (int i = 0; i < str.size(); i++)
    {
        if (str[i] == '/')
            return true;
        else
            return false;
    }
}

void Parse::removeSlash(std::string &s1, std::string &s2, std::string &s3, std::string &s4)
{
    std::vector<size_t> bufferSplited;

    std::vector<std::string> loop = {s1, s2, s3, s4};

    for (int i = 1; i <= 4; i++)
    {
        if (isSlash(loop[i - 1])) // '/' 가 string 안에 있는 지 확인
        {
            bufferSplited = splitSlash(loop[i]);
            if (bufferSplited.size())
                loop[i] = bufferSplited[0];
        }
    }
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
            float vert1 = 0.0f, vert2 = 0.0f, vert3 = 0.0f;
            ss >> vert1 >> vert2 >> vert3;
            attribute[0] = vert1;
            attribute[1] = vert2;
            attribute[2] = vert3;
        }
        else if (typePrefix == "Kd") // vertex face information
        {
            float vert1 = 0.0f, vert2 = 0.0f, vert3 = 0.0f;
            ss >> vert1 >> vert2 >> vert3;
            diffuse[0] = vert1;
            diffuse[1] = vert2;
            diffuse[2] = vert3;
        }
        else if (typePrefix == "Ks")
        {
            float vert1 = 0.0f, vert2 = 0.0f, vert3 = 0.0f;
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
    ft::vec2 max = ft::vec2();
    ft::vec2 min = ft::vec2();

    // y 축 하나 없애기 -> x의 Min, max, z의 min, max 구하기 (vertex 돌면서)
    for (ft::vec3 vec : vertexPosition)
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

    // 나온 값을 정규화(클리핑) 공식에 대입하기 (min-max scaler)
    // 나온 값을 vertexTexture 에 넣기
    vertexTexCoord.clear();
    vertexTexCoord.assign(vertexPosition.size(), ft::vec2());
    for (int vertexIdx = 0; vertexIdx < vertexPosition.size(); vertexIdx++)
    {
        vertexTexCoord[vertexIdx].x = (vertexPosition[vertexIdx].x - xMin) / xLength;
        vertexTexCoord[vertexIdx].y = (vertexPosition[vertexIdx].y - yMin) / yLength;
    }
}

void Parse::makeVertexNormal()
{
    vertexNormal.clear();
    vertexNormal.assign(vertexPosition.size(), ft::vec3());

    for (ft::vec3 line : faces) // line : v의 index number(삼각형으로 쪼개준 상태)
    {
        normalizing(line); // make vertex normal
    }
    for (ft::vec3 &vn : vertexNormal)
    {
        vn = ft::normalize(vn);
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
        }
    }

    return (std::move(VBO));
}

void Parse::normalizing(ft::vec3 facesLine) // v 5 7 1
{
    // 점 3개
    ft::vec3 v1 = vertexPosition[facesLine[0] - 1];
    ft::vec3 v2 = vertexPosition[facesLine[1] - 1];
    ft::vec3 v3 = vertexPosition[facesLine[2] - 1];

    // 두 점끼리 이어서 벡터를 만듦
    ft::vec3 vec1 = {v2[0] - v1[0], v2[1] - v1[1], v2[2] - v1[2]};
    ft::vec3 vec2 = {v3[0] - v1[0], v3[1] - v1[1], v3[2] - v1[2]};

    ft::vec3 normal = ft::normalize(ft::cross(vec1, vec2));

    vertexNormal[facesLine[0] - 1] += normal;
    vertexNormal[facesLine[1] - 1] += normal;
    vertexNormal[facesLine[2] - 1] += normal;
}