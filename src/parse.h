#ifndef __PARSE_H__
#define __PARSE_H__

#include "common.h"
#define GLM_ENABLE_EXPERIMENTAL // FIXME: glm to_string 안쓰게 되면 지우기
#include "glm/ext.hpp"          // FIXME: glm to_string 안쓰게 되면 지우기
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

struct VBOElements
{
    ft::vec3 v;  // 3
    ft::vec3 vn; // 3
    ft::vec2 vt; // 2
};

class Parse
{
  public:
    Parse();
    std::unique_ptr<float[]> Parser(std::string filename);
    std::unique_ptr<float[]> makeVBO();
    void parseMtlFile();
    void makeTexture();
    void makeVertexNormal();
    std::vector<size_t> splitSlash(std::string chunk);
    bool isSlash(std::string str);
    void removeSlash(std::string &s1, std::string &s2, std::string &s3, std::string &s4);
    void normalizing(ft::vec3 facesLine);
    void getMinMaxValue(float vertexX, float vertexY, float vertexZ);
    void centerizeObj(float xDist, float yDist, float zDist);
    void setFileName(std::string name)
    {
        this->filename = name;
    }

    // getter
    std::string getFileName()
    {
        return (this->filename);
    }
    std::vector<ft::vec3> getFaces()
    {
        return faces;
    }
    std::vector<ft::vec3> getNormals()
    {
        return vertexNormal;
    }

  private:
    std::string mtlInfo;
    std::string filename;

    std::string typePrefix;

    // VERTEX data
    std::vector<ft::vec3> vertexPosition; // 3
    std::vector<ft::vec3> vertexNormal;   // 3
    std::vector<ft::vec2> vertexTexCoord; // 2

    // FACE data
    std::vector<ft::vec3> faces;

    // mtl file
    ft::vec3 attribute;
    ft::vec3 diffuse;
    ft::vec3 specular;

    // 센터 맞추기
    float vertexXMin;
    float vertexXMax;

    float vertexYMin;
    float vertexYMax;

    float vertexZMin;
    float vertexZMax;
};

#endif // __PARSE_H__