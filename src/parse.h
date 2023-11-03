#ifndef __PARSE_H__
#define __PARSE_H__

#include "common.h"
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/ext.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>

struct Vertex {
    glm::vec3 vertexPosition;
    glm::vec3 normal;
    glm::vec2 texCoord;
};

struct Face {
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
	std::string mtlInfo {0}; // .mtl file name
    std::size_t vertexNormalIdx = 0;
	std::size_t vertexTexIdx = 0;
    std::string typePrefix = "";
    std::size_t rangeLimit = 0;
    // std::vector<std::vector<int>> vertexIndex;
    // std::vector<std::vector<int>> normalIndex;
    // std::vector<std::vector<int>> texCoordIndex;

};

#endif // __PARSE_H__