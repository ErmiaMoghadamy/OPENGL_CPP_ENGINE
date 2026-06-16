#include "../config.h"
#include "./App.h"
using std::cout;

namespace {
    constexpr float WINDOW_WIDTH  = 1920.0f;
    constexpr float WINDOW_HEIGHT = 1080.0f;
    constexpr char* WINDOW_TITLE  = "Balling Game";
}

App::App(): m_scene(WINDOW_WIDTH / WINDOW_HEIGHT) {
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

    glfwSwapInterval(1);
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);


    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glEnable(GL_BLEND);

}

App::~App() {
    // unique_ptr bulshit
    m_scene.~Scene();

    glfwDestroyWindow(m_Window);
    glfwTerminate();
}

void App::handleResize()
{
    int shape[2];
    glfwGetFramebufferSize(this->m_Window, &shape[0], &shape[1]);

    if (shape[0] == last_w && shape[1] == last_h)
        return;

    glViewport(0, 0, shape[0], shape[1]);

    float aspect =
        static_cast<float>(shape[0]) /
        static_cast<float>(shape[1]);

    this->m_scene.updateAspect(aspect);

    last_w = shape[0];
    last_h = shape[1];
}

void App::handleInput() {
    this->handleMouse();
    this->handleKeyboard();
}

void App::handleKeyboard() {
    const float moveSpeed = 0.1;

    if (glfwGetKey(m_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(m_Window, true);

    if (glfwGetKey(m_Window, GLFW_KEY_Q) == GLFW_PRESS)
        m_navMouse = !m_navMouse;

    if (glfwGetKey(m_Window, GLFW_KEY_W) == GLFW_PRESS)
        m_scene.m_camera.MoveForward(-moveSpeed);
    if (glfwGetKey(m_Window, GLFW_KEY_S) == GLFW_PRESS)
        m_scene.m_camera.MoveForward(moveSpeed); // Backwards

    if (glfwGetKey(m_Window, GLFW_KEY_D) == GLFW_PRESS)
        m_scene.m_camera.MoveRight(moveSpeed);
    if (glfwGetKey(m_Window, GLFW_KEY_A) == GLFW_PRESS)
        m_scene.m_camera.MoveRight(-moveSpeed); // Left

    if (glfwGetKey(m_Window, GLFW_KEY_SPACE) == GLFW_PRESS)
        m_scene.m_camera.MoveUp(moveSpeed);
    if (glfwGetKey(m_Window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        m_scene.m_camera.MoveUp(-moveSpeed); // Down
}

void App::handleMouse() {
    if (!m_navMouse) {
        glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        return;
    }

        glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


    double mouseX, mouseY;
    glfwGetCursorPos(m_Window, &mouseX, &mouseY);

    if (m_firstMouse) {
        mouse_lastX = static_cast<float>(mouseX);
        mouse_lastY = static_cast<float>(mouseY);
        m_firstMouse = false;
    }

    float dx = static_cast<float>(mouseX) - mouse_lastX;
    float dy = mouse_lastY - static_cast<float>(mouseY);

    mouse_lastX = static_cast<float>(mouseX);
    mouse_lastY = static_cast<float>(mouseY);

    if (dx != 0.0f || dy != 0.0f) {
        m_scene.m_camera.RotateMouse(dx, dy);
    }
}

void App::run() {
    this->handleResize();

    m_scene.boostrap();


    while (!glfwWindowShouldClose(m_Window)) {
        glfwPollEvents();

        this->handleResize();
        this->handleInput();

        m_scene.run();

        glfwSwapBuffers(m_Window);
    }
}
