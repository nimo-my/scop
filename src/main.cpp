#include "context.h"
#include <iostream>
#include <spdlog/spdlog.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>


void OnFramebufferSizeChange(GLFWwindow* window, int width, int height) {
  SPDLOG_INFO("framebuffer size changed: ({} x {})", width, height);
  auto context = reinterpret_cast<Context*>(glfwGetWindowUserPointer(window));
  context->Reshape(width, height);
}

// 키 입력!
void OnKeyEvent(GLFWwindow* window, int key, int scancode, int action, int mods) {
    ImGui_ImplGlfw_KeyCallback(window, key, scancode, action, mods);
    SPDLOG_INFO("key: {}, scancode: {}, action: {}, mods: {}{}{}",
        key, scancode,
        action == GLFW_PRESS ? "Pressed" :
        action == GLFW_RELEASE ? "Released" :
        action == GLFW_REPEAT ? "Repeat" : "Unknown",
        mods & GLFW_MOD_CONTROL ? "C" : "-",
        mods & GLFW_MOD_SHIFT ? "S" : "-",
        mods & GLFW_MOD_ALT ? "A" : "-");
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

void OnCharEvent(GLFWwindow* window, unsigned int ch) {
    ImGui_ImplGlfw_CharCallback(window, ch);
}

void OnScroll(GLFWwindow* window, double xoffset, double yoffset) {
    ImGui_ImplGlfw_ScrollCallback(window, xoffset, yoffset);
}

void OnCursorPos(GLFWwindow* window, double x, double y) {
    auto context = (Context*)glfwGetWindowUserPointer(window);
    context->MouseMove(x, y);
}

void OnMouseButton(GLFWwindow* window, int button, int action, int modifier) {
    ImGui_ImplGlfw_MouseButtonCallback(window, button, action, modifier);
    auto context = (Context*)glfwGetWindowUserPointer(window);
    double x, y;
    glfwGetCursorPos(window, &x, &y);
    context->MouseButton(button, action, x, y);
}

int main(int ac, char **av) {
    /* [1] Initialize the GLFW library */
    if (!glfwInit()) 
    {
        const char* description = NULL;
        glfwGetError(&description);
        std::cout << "Failed to initialize glfw: " << description << std::endl;
        return -1;
    }

    // version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    /* [2] Create a windowed mode window and its OpenGL context */
    auto window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME, nullptr, nullptr);
    if (!window) 
    {
        std::cout << "failed to create glfw window" << std::endl;
        glfwTerminate();
        return -1;
    }

    /* [3] Make the window's context current */
    glfwMakeContextCurrent(window);

    // GLAD를 이용한 OpenGL 함수 로딩
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) 
    {
        std::cout << "failed to initialize glad" << std::endl;
        glfwTerminate();
        return -1;
    }

    // [컨텍스트 초기화 부분] 쉐이더 파일 받아오기! 하나씩 하나씩 받아오고, 아이디 번호도 가져올수 있음!
    ShaderPtr vertShader = Shader::CreateFromFile("./shader/simple.vs", GL_VERTEX_SHADER);
    ShaderPtr fragShader = Shader::CreateFromFile("./shader/simple.fs", GL_FRAGMENT_SHADER);

    // vector 는 {} 로 묶어서 쓸 수 있음.
    // auto program = Program::Create({fragShader, vertShader});
    // std::cout << "program id : " << program->Get() << std::endl;

    auto imguiContext = ImGui::CreateContext();
    ImGui::SetCurrentContext(imguiContext);
    ImGui_ImplGlfw_InitForOpenGL(window, false); //callback false
    ImGui_ImplOpenGL3_Init(); // 3.3 renderer initialize
    ImGui_ImplOpenGL3_CreateFontsTexture();
    ImGui_ImplOpenGL3_CreateDeviceObjects(); // shader

    // create context 
    auto context = Context::Create();
    if (!context) {
        SPDLOG_ERROR("failed to create context");
        glfwTerminate();
        return -1;
    }

    glfwSetWindowUserPointer(window, context.get());
    glfwSetFramebufferSizeCallback(window, OnFramebufferSizeChange);
    glfwSetKeyCallback(window, OnKeyEvent);
    glfwSetCharCallback(window, OnCharEvent);
    glfwSetCursorPosCallback(window, OnCursorPos);
    glfwSetMouseButtonCallback(window, OnMouseButton);
    glfwSetScrollCallback(window, OnScroll);

    /* [4] Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) 
    {
        /* Render */
	    ImGui_ImplGlfw_NewFrame(); // 루프를 돌 때마다 새로운 frame을 로딩해준다
        ImGui::NewFrame();

        context->ProcessInput(window);
        context->Render();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        
        /* Swap front and back buffers :
            GLFW는 double buffering을 디폴트로 사용한다. front buffer(보여지는 버퍼, on display) & back buffer(rendering하는 버퍼)
            모든 프레임이 렌더링이 되면, 백버퍼가 프론트 버퍼로 스왑되면서 화면에 렌더링 결과물이 보여지게 된다.
        */
        glfwSwapBuffers(window);
        
        /* Poll for and process events :
            Event processing must be done regularly while you have visible windows 
            and is normally done each frame after buffer swapping.
            Processing pending events; polling & waiting.
        */
        glfwPollEvents();
    }

    /* [5] Cleanup functions */
    context.reset();

    ImGui_ImplOpenGL3_DestroyFontsTexture();
    ImGui_ImplOpenGL3_DestroyDeviceObjects();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext(imguiContext);

    glfwTerminate();
    return 0;
}


