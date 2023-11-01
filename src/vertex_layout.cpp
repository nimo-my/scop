#include "vertex_layout.h"

VertexLayoutUPtr VertexLayout::Create() 
{
    auto vertexLayout = VertexLayoutUPtr(new VertexLayout());
    vertexLayout->Init();
    return std::move(vertexLayout);
}

VertexLayout::~VertexLayout() 
{
    if (m_vertexArrayObject) 
    {
        glDeleteVertexArrays(1, &m_vertexArrayObject);
    }
}

// VAO binding
void VertexLayout::Bind() const 
{
    glBindVertexArray(m_vertexArrayObject);
}

// OpenGL이 vertex 데이터를 어떻게 해석해야하는지 지정
void VertexLayout::SetAttrib(uint32_t attribIndex, int count, uint32_t type, 
                                bool normalized, size_t stride, uint64_t offset) const 
{
    glEnableVertexAttribArray(attribIndex);
    glVertexAttribPointer(attribIndex, count,
        type, normalized, stride, (const void*)offset);
}

void VertexLayout::Init() 
{
    glGenVertexArrays(1, &m_vertexArrayObject);
    Bind();
}