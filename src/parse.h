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

// CLASS_PTR(Parse)
class Parse
{
  public:
    Parse();
    void Parser(std::string filename);
    void makeVBO();
    void parseMtlFile();
    void setFileName(std::string name);
    void normalizing(glm::vec3 facesLine);

    // for debug
    void printVertexInfo();
    std::string getFileName();

  private:
    std::string mtlInfo;
    std::string filename;

    // === PARSING =============================
    std::string typePrefix;
    std::size_t vertexNormalIdx;
    std::size_t vertexTexIdx;
    std::size_t rangeLimit;

    // VERTEX data
    std::vector<glm::vec3> vertexPosition; // 3
    std::vector<glm::vec3> vertexNormal;   // 3
    std::vector<glm::vec2> vertexTexCoord; // 2

    // FACE data
    std::vector<glm::vec3> faces;

    // === NORMALIZING =============================
    std::vector<glm::vec3> normals;

    // mtl file
    glm::vec3 attribute;
    glm::vec3 diffuse;
    glm::vec3 specular;

    // === GLM =============================
};

#endif // __PARSE_H__