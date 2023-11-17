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
    glm::vec3 v;  // 3
    glm::vec3 vn; // 3
    glm::vec2 vt; // 2
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
    void setFileName(std::string name);
    void normalizing(glm::vec3 facesLine);

    // getter
    std::string getFileName();
    std::vector<glm::vec3> getFaces()
    {
        return faces;
    }
    std::vector<glm::vec3> getNormals()
    {
        return vertexNormal;
    }

  private:
    std::string mtlInfo;
    std::string filename;

    // === PARSING =============================
    std::string typePrefix;

    // VERTEX data
    std::vector<glm::vec3> vertexPosition; // 3
    std::vector<glm::vec3> vertexNormal;   // 3
    std::vector<glm::vec2> vertexTexCoord; // 2

    // FACE data
    std::vector<glm::vec3> faces;

    // === NORMALIZING =============================

    // mtl file
    glm::vec3 attribute;
    glm::vec3 diffuse;
    glm::vec3 specular;

    // === GLM =============================
};

#endif // __PARSE_H__