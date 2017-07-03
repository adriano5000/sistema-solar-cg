#pragma once
#include "transform.h"
#include "camera.h"
#include <GL/glew.h>
#include <fstream>
#include <iostream>
#include <string>

class shader
{
public:
    shader(const std::string& shader_file);
    ~shader();
    void Bind();
    void Update(const transform& trans, const Camera& cam);

private:
    static const unsigned int SHADER_LIST_SIZE = 2;
    enum
    {
        TRANSFORM,
        NORMAL,
        CAMERA,
        NUM_UNIFORMS
    };

    GLuint _shader_program;
    GLuint _shader_list[SHADER_LIST_SIZE];
    GLuint _uniforms[NUM_UNIFORMS];
};
