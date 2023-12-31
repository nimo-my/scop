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

    ft::vec3 ambient;
    ft::vec3 diffuse;
    ft::vec3 specular;
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

    // animation
    bool m_animation{false};
    bool m_texture{true};

    // camera parameter
    float m_cameraPitch{0.0f};
    float m_cameraYaw{0.0f};
    ft::vec3 m_cameraPos{ft::vec3(0.0f, 0.0f, 3.0f)};
    ft::vec3 m_cameraFront{ft::vec3(0.0f, 0.0f, -1.0f)};
    ft::vec3 m_cameraUp{ft::vec3(0.0f, 1.0f, 0.0f)};
    bool m_cameraControl{false};

    // light parameter
    ft::vec3 m_lightPos{ft::vec3(3.0f, 3.0f, 3.0f)};
    ft::vec3 m_lightColor{ft::vec3(1.0f, 1.0f, 1.0f)};
    ft::vec3 m_objectColor{ft::vec3(1.0f, 0.5f, 0.0f)};
    float m_ambientStrength{0.1f};
    float m_specularStrength{0.5f};
    float m_specularShininess{32.0f};

    // mouse
    ft::vec2 m_prevMousePos{ft::vec2(0.0f)};

    // window size init
    int m_width{WINDOW_WIDTH};
    int m_height{WINDOW_HEIGHT};

    // clear color
    ft::vec4 m_clearColor{ft::vec4(0.1f, 0.2f, 0.3f, 0.0f)};

    // light parameter
    struct Light
    {
        ft::vec3 position{ft::vec3(2.0f, 2.0f, 2.0f)};
        ft::vec3 direction{ft::vec3(1.0f, 1.0f, 1.0f)};
        float cutoff{20.0f};   // 60도로 되어있는 각도 중 20도
        float distance{32.0f}; // 기본 거리
        ft::vec3 ambient{ft::vec3(0.5f, 0.5f, 0.5f)};
        ft::vec3 diffuse{ft::vec3(0.5f, 0.5f, 0.5f)};
        ft::vec3 specular{ft::vec3(1.0f, 1.0f, 1.0f)};
    };
    Light m_light;

    // material parameter
    struct TexMaterial
    {
        TextureUPtr texDiffuse;
        TextureUPtr texSpecular;
        Material attribute{"None", ft::vec3(0.3f), ft::vec3(0.6f), ft::vec3(0.5f), 1.0f, "", "", "", ""};
    };
    TexMaterial m_material;
};

#endif // __CONTEXT_H__