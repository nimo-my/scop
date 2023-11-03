#include "shader.h"
// #include "spdlog/spdlog.h"

ShaderUPtr Shader::CreateFromFile(const std::string& filename, GLenum shaderType)
{
    auto shader = std::unique_ptr<Shader>(new Shader());
    if (!shader->LoadFile(filename, shaderType))
        return nullptr;
    return std::move(shader); // 소유권 이전! 포인터를 밖으로 넘긴다!
}

Shader::~Shader()
{
    if (m_shader)
    {
        glDeleteShader(m_shader);
    }
}

bool Shader::LoadFile(const std::string& filename, GLenum shaderType)
{
    // file loading (return : optional, 값이 있을수도 있고 없을 수도 있음!)
    auto result = LoadTextFile(filename);
    if (!result.has_value())
        return false;
    
    // value에 뭐가 얼마나 들어올지 모르니까 레퍼런스 붙여주기!
    auto& code = result.value();
    const char* codePtr = code.c_str();
    int32_t codeLength = (int32_t)code.length();

    // [create & compile shader]
    m_shader = glCreateShader(shaderType);
    glShaderSource(m_shader, 1, (const GLchar* const*)&codePtr, &codeLength);
    glCompileShader(m_shader);

    // [check compile shader]
    int success = 0;
    // 쉐이더 정보 얻어오는 함수 i - int, v - vector(뒤에 포인터가 들어감)
    glGetShaderiv(m_shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char infoLog[1024];
        glGetShaderInfoLog(m_shader, 1024, nullptr, infoLog);
        // SPDLOG_ERROR("failed to compile shader: \"{}\"", filename);
        // SPDLOG_ERROR("reason: {}", infoLog);
        return false;
    }
    return true;
}