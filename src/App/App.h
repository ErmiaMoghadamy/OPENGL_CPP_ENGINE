#pragma once
#include "Scene.h"
#include "config.h"


class App {
public:
    App();
    ~App();

    void handleResize();
    void handleInput();
    void handleMouse();
    void handleKeyboard();
    void run();

private:
    GLFWwindow* m_Window;
    Scene m_scene;

    unsigned int last_w;
    unsigned int last_h;

    // mouse
    float mouse_lastX = 400.0f;
    float mouse_lastY = 300.0f;
    bool m_firstMouse = true;
    bool m_navMouse = false;
};
