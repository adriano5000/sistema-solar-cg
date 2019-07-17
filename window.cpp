#include "window.h"
#include <iostream>

Window::Window(size_t width, size_t height, const char* title, int vsync)
{
    if(!glfwInit())
        std::cerr << "error on glfwInit()";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    //    GLFWmonitor* display = glfwGetPrimaryMonitor();
    _window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    //   _window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    //    GLFWmonitor* monitor = glfwGetWindowMonitor(_window);
    //   const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    //  glfwSetWindowMonitor(_window, monitor, 0, 0, mode->width, mode->height,
    //  mode->refreshRate);
    if(!_window)
        std::cerr << "error creating the window\n";
    glfwMakeContextCurrent(_window);
    glfwSwapInterval(vsync);
    glewExperimental = GL_TRUE;
    GLuint err = glewInit();
    if(err != GLEW_OK)
        std::cerr << glewGetErrorString(err) << "\n";

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glEnable(GL_LIGHTING);
}

Window::~Window() { glfwTerminate(); }

void Window::Update()
{
    glfwSwapBuffers(_window);
    glfwPollEvents();
}
