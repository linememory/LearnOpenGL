#ifndef CUBE_H
#define CUBE_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include "Mesh.h"
#include "Shader.h"

class Cube {
private:
    Mesh m_mesh;
    Shader m_shader;
    std::vector<Vertex> m_vertices;
    glm::vec3 m_position;
    glm::vec3 m_size;
    glm::vec3 m_rotation;

    void createCube();

public:
    Cube(glm::vec3 position  = glm::vec3(0.0f), glm::vec3 size = glm::vec3(1.0f), glm::vec3 rotation = glm::vec3(0.0f));
    void setShader(std::string vertexShaderPath, std::string fragmentShaderPath);
    void draw(glm::mat4 view, glm::mat4 projection);
};

#endif