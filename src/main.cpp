#include "config.h"
using std::cout;

int main() {
    GLFWwindow* window;

    if (!glfwInit()) { cout << "[INIT Err] Failed to initialize glfw\n"; return -1; }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);
    if (!window) { glfwTerminate(); return -1; }
}