#ifndef __PARSE_H__
#define __PARSE_H__

#include "common.h"
#define GLM_ENABLE_EXPERIMENTAL // FIXME: to_string 안쓰게 되면 지우기
#include "glm/ext.hpp"          // FIXME: to_string 안쓰게 되면 지우기
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>


CLASS_PTR(Parse)
class Parse
{
  public:
    // Parse() {};
    void Parser(std::string filename);
    void makeVBO();
    void printVertexInfo();

  private:
    // TODO: 초기화 하는 부분 다듬기
    std::string mtlInfo{0}; // .mtl file name
    
    // parsing
    std::string typePrefix = "";
    std::size_t vertexNormalIdx = 0;
    std::size_t vertexTexIdx = 0;
    std::size_t rangeLimit = 0;

    // VERTEX data 
    std::vector<int> vertexPosition; // 3
    std::vector<int> normal; // 3
    std::vector<int> texCoord; // 2

    // FACE data
    std::vector<int> vertexIndex;
    std::vector<int> normalIndex;
    std::vector<int> texCoordIndex;

};

#endif // __PARSE_H__