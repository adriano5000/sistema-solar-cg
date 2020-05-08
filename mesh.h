#pragma once

#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include "obj_loader.h"

struct vertex
{
    glm::vec3 nor;
    glm::vec3 pos;
    glm::vec2 tex;
};

enum VertexBufferData
{
    POSITION,
    TEXTURE,
    NORMAL,
    INDEX,
    BUFFER_SIZE
};

class Mesh
{
public:
    Mesh(const std::string& file_name);
    Mesh(vertex* vertices, size_t vertices_size, unsigned int* indices, unsigned int indices_size);
    ~Mesh();
    void Draw();

private:
    void init_mesh(const IndexedModel& model);
    GLuint vao;
    GLuint vao_buffer[BUFFER_SIZE];
    size_t draw_count;
};
