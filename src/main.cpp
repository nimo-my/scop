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
    std::cout << "Initialize glfw" << std::endl;
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

    // make window
    auto window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME, nullptr, nullptr);
    if (!window) 
    {
        std::cout << "failed to create glfw window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // set context
    glfwMakeContextCurrent(window);

    // glad를 이용한 OpenGL 함수 로딩
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) 
    {
        std::cout << "failed to initialize glad" << std::endl;
        glfwTerminate();
        return -1;
    }

    // [컨텍스트 포기화 부분] 쉐이더 파일 받아오기! 하나씩 하나씩 받아오고, 아이디 번호도 가져올수 있음!
    ShaderPtr vertShader = Shader::CreateFromFile("./shader/simple.vs", GL_VERTEX_SHADER);
    ShaderPtr fragShader = Shader::CreateFromFile("./shader/simple.fs", GL_FRAGMENT_SHADER);
    std::cout << "vertex shader id : " << vertShader->Get() << std::endl;
    std::cout << "fragment shader id : " << fragShader->Get() << std::endl;

    // vector 는 {} 로 묶어서 쓸 수 있음.
    auto program = Program::Create({fragShader, vertShader});
    std::cout << "program id : " << program->Get() << std::endl;

    auto imguiContext = ImGui::CreateContext();
    ImGui::SetCurrentContext(imguiContext);
    ImGui_ImplGlfw_InitForOpenGL(window, false); //callback false
    ImGui_ImplOpenGL3_Init(); // 3.3 renderer initialize
    ImGui_ImplOpenGL3_CreateFontsTexture();
    ImGui_ImplOpenGL3_CreateDeviceObjects(); // shader

    auto context = Context::Create();
    if (!context) {
        SPDLOG_ERROR("failed to create context");
        glfwTerminate();
        return -1;
    }
    glfwSetWindowUserPointer(window, context.get());

    glfwSetFramebufferSizeCallback(window, OnFramebufferSizeChange);
    glfwSetKeyCallback(window, OnKeyEvent);
    glfwSetCursorPosCallback(window, OnCursorPos);
    glfwSetMouseButtonCallback(window, OnMouseButton);

    // 메인 while 문
    while (!glfwWindowShouldClose(window)) {
        
        glfwPollEvents();
	    ImGui_ImplGlfw_NewFrame(); // imgui draws things every frame.. everytime they loop, they need to know that typicall frame is the new frame.
        ImGui::NewFrame();

        context->ProcessInput(window);
        context->Render();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }

    context.reset(); // 방법1. context 에 담긴 내용들 모두 리셋 
    // context = nullptr; // 방법2. 소유권이 없어지면서 메모리 해제를 해줌. 

    ImGui_ImplOpenGL3_DestroyFontsTexture();
    ImGui_ImplOpenGL3_DestroyDeviceObjects();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext(imguiContext);

    glfwTerminate();
    return 0;
}


