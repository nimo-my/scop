#include "context.h"
#include "GLFW/glfw3.h"
#include "image.h"
#include "parse.h"
#include <imgui.h>
#include <iostream>

ContextUPtr Context::Create()
{
    auto context = ContextUPtr(new Context());
    return (std::move(context));
}

void Context::MouseButton(int button, int action, double x, double y)
{
    if (button == GLFW_MOUSE_BUTTON_RIGHT)
    {
        if (action == GLFW_PRESS)
        {
            // 마우스 조작 시작 시점에 현재 마우스 커서 위치 저장
            m_prevMousePos = glm::vec2((float)x, (float)y);
            m_cameraControl = true;
        }
        else if (action == GLFW_RELEASE)
        {
            m_cameraControl = false;
        }
    }
}

void Context::ProcessInput(GLFWwindow *window)
{
    const float cameraSpeed = 0.05f;
    if ((glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) || (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS))
        m_cameraPos += cameraSpeed * m_cameraFront;
    if ((glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) || (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS))
        m_cameraPos -= cameraSpeed * m_cameraFront;

    auto cameraRight = glm::normalize(glm::cross(m_cameraUp, -m_cameraFront));
    if ((glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) || (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS))
        m_cameraPos += cameraSpeed * cameraRight;

    if ((glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) || (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS))
        m_cameraPos -= cameraSpeed * cameraRight;

    auto cameraUp = glm::normalize(glm::cross(-m_cameraFront, cameraRight));
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        m_cameraPos += cameraSpeed * cameraUp;
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        m_cameraPos -= cameraSpeed * cameraUp;
}

void Context::Reshape(int width, int height)
{
    m_width = width;
    m_height = height;
    glViewport(0, 0, m_width, m_height);
}

std::unique_ptr<Parse> Context::Init()
{
    // ** PARSING ** //
    std::unique_ptr<Parse> parse(new Parse());

    std::string objFileName = "./resorces/";
    objFileName += "w_box"; // NOTE : insert file name
    parse->setFileName(objFileName);
    objFileName += ".obj";

    auto vertice = parse->Parser(objFileName); // 파싱부분

    // [1] VAO binding :: vertex array obj 생성 & 바인딩
    m_vertexLayout = VertexLayout::Create();

    // [2] VBO binding :: 버텍스 버퍼 생성(generate)
    m_vertexBuffer = Buffer::CreateWithData(GL_ARRAY_BUFFER, GL_STATIC_DRAW, vertice.get(),
                                            parse->getFaces().size() * sizeof(float) * 8 * 3);

    // [3] Vertex attribute setting
    // vertices의 위치를 각각 어떻게 구성할것인지!
    // void VertexLayout::SetAttrib(uint32_t attribIndex, 버텍스 속성의 크기, 데이터 타입, 정규화 여부, 연이은
    // vertex 속성 세트들 사이의 공백(stride), 버퍼에서 데이터) const
    m_vertexLayout->SetAttrib(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, 0);
    m_vertexLayout->SetAttrib(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, sizeof(float) * 3);
    m_vertexLayout->SetAttrib(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, sizeof(float) * 6);

    m_program = Program::Create("./shader/lighting.vs", "./shader/lighting.fs");
    if (!m_program)
        exit(1);

    glClearColor(0.7f, 0.7f, 0.7f, 0.0f); // background color

    m_material.texDiffuse = Texture::CreateFromImage(Image::Load("./image/green_pattern.jpeg").get()); // texture

    return (std::move(parse));
}

void Context::Render(std::unique_ptr<Parse> &parse)
{
    if (ImGui::Begin("ui window"))
    {
        if (ImGui::ColorEdit4("clear color", glm::value_ptr(m_clearColor)))
        {
            glClearColor(m_clearColor.x, m_clearColor.y, m_clearColor.z, m_clearColor.w);
        }
        ImGui::Separator();
        ImGui::DragFloat3("camera pos", glm::value_ptr(m_cameraPos), 0.01f);
        ImGui::DragFloat("camera yaw", &m_cameraYaw, 0.5f);
        ImGui::DragFloat("camera pitch", &m_cameraPitch, 0.5f, -89.0f, 89.0f);
        ImGui::Separator();
        if (ImGui::Button("reset camera"))
        {
            m_cameraYaw = 0.0f;
            m_cameraPitch = 0.0f;
            m_cameraPos = glm::vec3(0.0f, 0.0f, 10.0f);
        }
        if (ImGui::CollapsingHeader("light", ImGuiTreeNodeFlags_DefaultOpen))
        {
            ImGui::DragFloat3("l.position", glm::value_ptr(m_light.position), 0.01f);
            ImGui::DragFloat3("l.direction", glm::value_ptr(m_light.direction), 0.01f);
            ImGui::DragFloat("l.distance", &m_light.distance, 0.5f, 0.0f, 3000.0f);
            ImGui::ColorEdit3("l.ambient", glm::value_ptr(m_light.ambient));
            ImGui::ColorEdit3("l.diffuse", glm::value_ptr(m_light.diffuse));
            ImGui::ColorEdit3("l.specular", glm::value_ptr(m_light.specular));
        }

        if (ImGui::CollapsingHeader("material", ImGuiTreeNodeFlags_DefaultOpen))
        {
            ImGui::ColorEdit3("m.ambient", glm::value_ptr(m_material.attribute.ambient));
            ImGui::ColorEdit3("m.diffuse", glm::value_ptr(m_material.attribute.diffuse));
            ImGui::ColorEdit3("m.specular", glm::value_ptr(m_material.attribute.specular));
            ImGui::DragFloat("m.shininess", &m_material.attribute.shininess, 1.0f, 1.0f, 256.0f);
        }
        ImGui::Checkbox("animation", &m_animation);
        ImGui::Checkbox("texture", &m_texture);
    }
    ImGui::End();

    // 버퍼 초기화
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    m_cameraFront = glm::rotate(glm::mat4(1.0f), glm::radians(m_cameraYaw), glm::vec3(0.0f, 1.0f, 0.0f)) *
                    glm::rotate(glm::mat4(1.0f), glm::radians(m_cameraPitch), glm::vec3(1.0f, 0.0f, 0.0f)) *
                    glm::vec4(0.0f, 0.0f, -1.0f, 0.0f); // 방향벡터

    /* 카메라 파라미터! */
    auto projection = glm::perspective(glm::radians(45.0f), (float)m_width / (float)m_height, 0.01f, 50.0f);

    auto view = glm::lookAt(m_cameraPos, m_cameraPos + m_cameraFront, m_cameraUp);

    m_program->Use();
    m_program->SetUniform("viewPos", m_cameraPos);
    m_program->SetUniform("light.position", m_light.position);
    m_program->SetUniform("light.direction", m_light.direction);
    m_program->SetUniform("light.ambient", m_light.ambient);
    m_program->SetUniform("light.diffuse", m_light.diffuse);
    m_program->SetUniform("light.specular", m_light.specular);

    m_program->SetUniform("material.ambient", m_material.attribute.ambient);
    m_program->SetUniform("material.diffuse", m_material.attribute.diffuse);
    m_program->SetUniform("material.specular", m_material.attribute.specular);
    m_program->SetUniform("material.shininess", m_material.attribute.shininess);
    m_program->SetUniform("m_texture", m_texture);

    glActiveTexture(GL_TEXTURE0); // texture를 shader 통해서 active
    m_material.texDiffuse->Bind();

    auto model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -10.0f));
    auto angle = glm::radians((m_animation ? (float)glfwGetTime() : 0.0f) * 120.0f);

    model = glm::rotate(model, angle, glm::vec3(0.0f, 1.0f, 0.0f));
    auto transform = projection * view * model;

    m_program->SetUniform("transform", transform);
    m_program->SetUniform("modelTransform", model);
    glDrawArrays(GL_TRIANGLES, 0, parse->getFaces().size() * 8 * 3);
}
