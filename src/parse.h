#ifndef __PARSE_H__
#define __PARSE_H__

#include "common.h"
// #define GLM_ENABLE_EXPERIMENTAL // FIXME: glm to_string 안쓰게 되면 지우기
// #include "glm/ext.hpp"          // FIXME: glm to_string 안쓰게 되면 지우기
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>


// CLASS_PTR(Parse)
class Parse
{
  public:
    Parse();
    void Parser(std::string filename);
    void makeVBO();
    void parseMtlFile();
    void setFileName(std::string name);
    void normalizing();

  // for debug
    void printVertexInfo();
    std::string getFileName();

  private:
    std::string mtlInfo;
    std::string filename;
    
    // parsing
    std::string typePrefix;
    std::size_t vertexNormalIdx;
    std::size_t vertexTexIdx;
    std::size_t rangeLimit;

    // VERTEX data 
    std::vector<float> vertexPosition; // 3
    std::vector<float> vertexNormal; // 3
    std::vector<float> vertexTexCoord; // 2

    // FACE data
    std::vector<std::vector<size_t>> faces; // 3개의 index가 vector<size_t> 형태로 들어가 있음

    // mtl file
    std::vector<float> attribute;
    std::vector<float> diffuse;
    std::vector<float> specular;
    
};

#endif // __PARSE_H__