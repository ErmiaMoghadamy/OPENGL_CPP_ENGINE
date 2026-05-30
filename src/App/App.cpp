#include "../config.h"
#include "./App.h"
using std::cout;

App::App() {
    if (!glfwInit()) { throw std::runtime_error("[INIT Err] Failed to initialize glfw"); }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_Window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);
    if (!m_Window) { glfwTerminate(); throw std::runtime_error("[INIT Err] Failed to initialize glfw"); }

    glfwMakeContextCurrent(m_Window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        glfwTerminate();
        throw std::runtime_error("[GLAD Err] Failed to initialize GLAD");
    }
}

App::~App() {
    glfwTerminate();
}

void App::run() {
    m_scene.boostrap();
    while (!glfwWindowShouldClose(m_Window)) {
        glfwPollEvents();

        m_scene.run();

        glfwSwapBuffers(m_Window);
    }
}
