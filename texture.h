#pragma once
#include <string>
#include <GL/glew.h>

class Texture
{
public:
    Texture(const std::string& file_name);
    ~Texture();
    void Bind(unsigned int unit);
private:
    GLuint _texture;
};
