#pragma once
#include "Scene.h"
#include "../config.h"


class App {
public:
    void run();
    App();
    ~App();

private:
    GLFWwindow* m_Window;
    Scene m_scene;
};
