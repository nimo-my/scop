#ifndef __CONTEXT_H__
#define __CONTEXT_H__

#include "buffer.h"
#include "common.h"
#include "parse.h"
#include "program.h"
#include "shader.h"
#include "texture.h"
#include "vertex_layout.h"

struct Material
{
    std::string name;

    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float shininess;

    std::string ambientTexture;
    std::string diffuseTexture;
    std::string specularTexture;
    std::string shininessTexture;
};

CLASS_PTR(Context)
class Context
{
  public:
    static ContextUPtr Create();
    std::unique_ptr<Parse> Init();
    void MouseButton(int button, int action, double x, double y);
    void MouseMove(double x, double y);
    void ProcessInput(GLFWwindow *window);
    void Reshape(int width, int height);

    void Render(std::unique_ptr<Parse> &parse);

  private:
    Context()
    {
    }
    ProgramUPtr m_program;
    ProgramUPtr m_simpleProgram;

    VertexLayoutUPtr m_vertexLayout;
    BufferUPtr m_vertexBuffer;
    BufferUPtr m_indexBuffer;
    // TextureUPtr m_texture;
    // TextureUPtr m_texture2;

    // animation
    bool m_animation{false};
    bool m_texture{true};

    // camera parameter
    float m_cameraPitch{0.0f};
    float m_cameraYaw{0.0f};
    glm::vec3 m_cameraPos{glm::vec3(0.0f, 0.0f, 3.0f)};
    glm::vec3 m_cameraFront{glm::vec3(0.0f, 0.0f, -1.0f)};
    glm::vec3 m_cameraUp{glm::vec3(0.0f, 1.0f, 0.0f)};
    bool m_cameraControl{false};

    // light parameter
    glm::vec3 m_lightPos{glm::vec3(3.0f, 3.0f, 3.0f)};
    glm::vec3 m_lightColor{glm::vec3(1.0f, 1.0f, 1.0f)};
    glm::vec3 m_objectColor{glm::vec3(1.0f, 0.5f, 0.0f)};
    float m_ambientStrength{0.1f};
    float m_specularStrength{0.5f};
    float m_specularShininess{32.0f};

    // mouse
    glm::vec2 m_prevMousePos{glm::vec2(0.0f)};

    // window size init
    int m_width{WINDOW_WIDTH};
    int m_height{WINDOW_HEIGHT};

    // clear color
    glm::vec4 m_clearColor{glm::vec4(0.1f, 0.2f, 0.3f, 0.0f)};

    // light parameter
    struct Light
    {
        glm::vec3 position{glm::vec3(2.0f, 2.0f, 2.0f)};
        glm::vec3 direction{glm::vec3(-1.0f, -1.0f, -1.0f)};
        float cutoff{20.0f};   // 60도로 되어있는 각도 중 20도
        float distance{32.0f}; // 기본 거리
        glm::vec3 ambient{glm::vec3(0.1f, 0.1f, 0.1f)};
        glm::vec3 diffuse{glm::vec3(0.5f, 0.5f, 0.5f)};
        glm::vec3 specular{glm::vec3(1.0f, 1.0f, 1.0f)};
    };
    Light m_light;

    // material parameter
    struct TexMaterial
    {
        TextureUPtr texDiffuse;
        TextureUPtr texSpecular;
        Material attribute{"None", glm::vec3(0.3f), glm::vec3(0.6f), glm::vec3(0.5f), 1.0f, "", "", "", ""};
    };
    TexMaterial m_material;
};

#endif // __CONTEXT_H__