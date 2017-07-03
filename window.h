#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class window
{
private:
    GLFWwindow* _window;

public:
    window(size_t width, size_t height, const char* title, int vsync);
    GLFWwindow* GetWindow() { return _window; }
    void Update();
    ~window();
};
