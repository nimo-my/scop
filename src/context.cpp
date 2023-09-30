#include "context.h"

ContextUPtr Context::Create() 
{
    auto context = ContextUPtr(new Context());
    if (!context->Init())
        return nullptr;
    return std::move(context);
}

bool Context::Init() 
{
    float vertices[] = {
        
        0.5f, 0.5f, 0.0f, // top right
        0.5f, -0.5f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f, // bottom left
        -0.5f, 0.5f, 0.0f, // top left
    };

    uint32_t indices[] ={
        0, 1, 3,
        1, 2, 3,
    };

    // 순서 !!
    // [1] VAO binding :: vertex array obj 생성 & 바인딩
    m_vertexLayout = VertexLayout::Create();

    // [2] VBO binding :: 버텍스 버퍼 생성(generate)
    m_vertexBuffer = Buffer::CreateWithData(GL_ARRAY_BUFFER, GL_STATIC_DRAW, vertices, sizeof(float) * 12);



    // [3] Vertex attribute setting
    // vertices의 위치를 각각 어떻게 구성할것인지! layout = x의 x에 들어오는 값!
    // 정점 attribute 중 n번째를 사용하도록 (0번 attribute를 사용할거다!)
    m_vertexLayout->SetAttrib(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);


    m_indexBuffer = Buffer::CreateWithData(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW, indices, sizeof(float) * 6);

    ShaderPtr vertShader = Shader::CreateFromFile("./shader/simple.vs", GL_VERTEX_SHADER);
    ShaderPtr fragShader = Shader::CreateFromFile("./shader/simple.fs", GL_FRAGMENT_SHADER);

    if (!vertShader || !fragShader)
        return false;
    SPDLOG_INFO("vertex shader id: {}", vertShader->Get());
    SPDLOG_INFO("fragment shader id: {}", fragShader->Get());

    m_program = Program::Create({fragShader, vertShader});
    if (!m_program)
        return false;
    SPDLOG_INFO("program id: {}", m_program->Get());

    glClearColor(0.1f, 0.2f, 0.3f, 0.0f);

    // 정점 하나만 만들 때 사용했음,,! // vertex array 를 만들고 바인딩
    // uint32_t vao = 0;
    // glGenVertexArrays(1, &vao);
    // glBindVertexArray(vao);

    return true;

}

void Context::Render()
{
    // 색상버퍼 초기화
    glClear(GL_COLOR_BUFFER_BIT);

    // 그림그리는 코드
    m_program->Use();

    // glDrawArrays(GL_TRIANGLES, 0, 6);
    // glDrawArrays(GL_LINE_STRIP, 0, 3);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
