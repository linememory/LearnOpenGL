#ifndef CUBE_H
#define CUBE_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include "Mesh.h"
#include "Shader.h"

class Cube {
private:
    Mesh m_mesh;
    Shader m_shader, m_outlineShader;
    std::vector<Vertex> m_vertices;
    std::vector<Texture> m_textures;
    glm::vec3 m_position;
    glm::vec3 m_size;
    glm::vec3 m_rotation;
    bool m_outline;
    bool m_meshCreated = false;

    void createCube();
    void createMesh();

public:
    Cube(glm::vec3 position  = glm::vec3(0.0f), glm::vec3 size = glm::vec3(1.0f), glm::vec3 rotation = glm::vec3(0.0f));
    void setShader(std::string vertexShaderPath, std::string fragmentShaderPath);
    void loadTexture(std::string path, TextureType type);
    void draw(glm::mat4 view, glm::mat4 projection);
    void enableOutline(bool outline);
};

#endif