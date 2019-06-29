#ifndef MESH_H
#define MESH_H

#include <vector>
#include <string>
#include <iostream>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "Shader.h"


struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec3 texCoords;
};

struct Texture{
    unsigned int id;
    std::string type;
};


class Mesh 
{
private:
    unsigned int VAO, VBO, EBO;
    std::vector<Vertex> m_vertices;
    std::vector<unsigned int> m_indices;
    std::vector<Texture> m_textures;

    void setupMesh();

public:
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
    void draw(Shader shader);
};

#endif