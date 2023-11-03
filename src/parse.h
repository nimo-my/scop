#ifndef __PARSE_H__
#define __PARSE_H__

#include "common.h"
#define GLM_ENABLE_EXPERIMENTAL // TODO: to_string 안쓰게 되면 지우기
#include "glm/ext.hpp"          // TODO: to_string 안쓰게 되면 지우기
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

struct Vertex
{
    glm::vec3 vertexPosition;
    glm::vec3 normal;
    glm::vec2 texCoord;
};

struct Face
{
    std::vector<int> vertexIndex;
    std::vector<int> normalIndex;
    std::vector<int> texCoordIndex;
};

CLASS_PTR(Parse)
class Parse
{
  public:
    // Parse() {};
    void Parser(std::string filename, std::vector<Vertex> vertices, std::vector<Face> faces);
    void printVertexInfo(std::vector<Vertex> vertices);
    void printFaceInfo(std::vector<Face> faces);

  private:
    // TODO: 초기화 하는 부분 다듬기
    std::string mtlInfo{0}; // .mtl file name
    std::size_t vertexNormalIdx = 0;
    std::size_t vertexTexIdx = 0;
    std::string typePrefix = "";
    std::size_t rangeLimit = 0;
};

#endif // __PARSE_H__