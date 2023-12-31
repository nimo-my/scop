#include "program.h"
#include <iostream>

ProgramUPtr Program::Create(const std::vector<ShaderPtr>& shaders)
{
    auto program = ProgramUPtr(new Program());
    if (!program->Link(shaders))
        return nullptr;
    return std::move(program);
}

ProgramUPtr Program::Create(const std::string& vertShaderFilename, const std::string& fragShaderFilename) 
{
    ShaderPtr vs = Shader::CreateFromFile(vertShaderFilename, GL_VERTEX_SHADER);
    ShaderPtr fs = Shader::CreateFromFile(fragShaderFilename, GL_FRAGMENT_SHADER);
    if (!vs || !fs) 
        return nullptr;
    return std::move(Create({vs, fs}));
}

bool Program::Link(const std::vector<ShaderPtr>& shaders)
{
    m_program = glCreateProgram();

    // 쉐이더의 id값을 하나하나 세팅해줌
    // C++11 부터 이런 for 문 사용 가능! C++ STL Collection class(vector, set, map과 같은 iterator가 있는 애들)은 사용 가능!
    // shader 안에 shaders가 하나하나 들어옴..
    
    for (auto& shader: shaders)
        glAttachShader(m_program, shader->Get());

    // 링크 시도
    glLinkProgram(m_program);
    
    int success = 0;
    // 성공하면 success가 1이 됨!
    glGetProgramiv(m_program, GL_LINK_STATUS, &success);
    if (!success)
    {
        char infoLog[1024];
        glGetProgramInfoLog(m_program, 1024, nullptr, infoLog);
        SPDLOG_ERROR("failed to link program: \"{}\"", infoLog);
        return false;
    }
    return true;
}

Program::~Program()
{
    if (m_program)
    {
        glDeleteProgram(m_program);
    }
}

// 2. 오브젝트를 그리고 싶을 때 우리가 생성한 shader program을 사용
void Program::Use() const 
{
    glUseProgram(m_program);
}

void Program::SetUniform(const std::string& name, int value) const 
{
    auto loc = glGetUniformLocation(m_program, name.c_str());
    glUniform1i(loc, value);
}

void Program::SetUniform(const std::string& name, const ft::mat4& value) const 
{
    auto loc = glGetUniformLocation(m_program, name.c_str());
    glUniformMatrix4fv(loc, 1, GL_FALSE, ft::value_ptr(value));
}

void Program::SetUniform(const std::string& name, float value) const 
{
    auto loc = glGetUniformLocation(m_program, name.c_str());
    glUniform1f(loc, value);
}

void Program::SetUniform(const std::string& name, const ft::vec3& value) const 
{
    auto loc = glGetUniformLocation(m_program, name.c_str());
    glUniform3fv(loc, 1, ft::value_ptr(value));
}

void Program::SetUniform(const std::string& name, const ft::vec4& value) const 
{
  auto loc = glGetUniformLocation(m_program, name.c_str());
  glUniform4fv(loc, 1, ft::value_ptr(value));
}