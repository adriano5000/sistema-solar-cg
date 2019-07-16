#include "mesh.h"
#include <vector>

void Mesh::init_mesh(const IndexedModel& model)
{
    draw_count = model.indices.size();
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(BUFFER_SIZE, vao_buffer);

    glBindBuffer(GL_ARRAY_BUFFER, vao_buffer[POSITION]);
    glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.positions[0]), &model.positions[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, vao_buffer[TEXTURE]);
    glBufferData(GL_ARRAY_BUFFER, model.texCoords.size() * sizeof(model.texCoords[0]), &model.texCoords[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, vao_buffer[NORMAL]);
    glBufferData(GL_ARRAY_BUFFER, model.normals.size() * sizeof(model.normals[0]), &model.normals[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vao_buffer[BUFFER_SIZE]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size() * sizeof(model.indices[0]), &model.indices[0], GL_STATIC_DRAW);

    glBindVertexArray(0);
}

Mesh::Mesh(const std::string& file_name) { init_mesh(OBJModel(file_name).ToIndexedModel()); }

Mesh::Mesh(vertex* vertices, size_t vertices_size, unsigned int* indices, unsigned int indices_size)
{
    IndexedModel model;
    model.positions.reserve(vertices_size);
    model.texCoords.reserve(vertices_size);
    model.normals.reserve(vertices_size);
    model.indices.reserve(indices_size);
    for(size_t i = 0; i < vertices_size; i++)
    {
        model.positions.push_back(vertices[i].pos);
        model.texCoords.push_back(vertices[i].tex);
        model.normals.push_back(vertices[i].nor);
    }

    for(size_t i = 0; i < indices_size; i++)
        model.indices.push_back(indices[i]);
    init_mesh(model);
}

Mesh::~Mesh()
{
    glDeleteBuffers(4, &vao);
    glDeleteVertexArrays(1, &vao);
}

void Mesh::Draw()
{
    glBindVertexArray(vao);
    glDrawElementsBaseVertex(GL_TRIANGLES, draw_count, GL_UNSIGNED_INT, 0, 0);
    glBindVertexArray(0);
}
