#include "context.h"
#include <iostream>

// #include <glad/glad.h>
// #include <GLFW/glfw3.h>

// 키 입력!
void OnKeyEvent(GLFWwindow* window,
    int key, int scancode, int action, int mods) {
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


    auto context = Context::Create();
    if (!context) {
        SPDLOG_ERROR("failed to create context");
        glfwTerminate();
        return -1;
    }

    // window 크기와 배경 색상(맥에서는 문제 있음!!)
    // glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    // glfwSetFramebufferSizeCallback(window, OnFramebufferSizeChange);
    glfwSetKeyCallback(window, OnKeyEvent);

    // 메인 while 문
    while (!glfwWindowShouldClose(window)) {

        glfwPollEvents();
        context->Render(); // state using function
        glfwSwapBuffers(window);
    }

    context.reset(); // 방법1. context 에 담긴 내용들 모두 리셋 
    // context = nullptr; // 방법2. 소유권이 없어지면서 메모리 해제를 해줌. 
    glfwTerminate();
    return 0;
}


