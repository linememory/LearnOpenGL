#ifndef CUBE_H
#define CUBE_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include "Model.h"
#include "Mesh.h"
#include "Shader.h"


class Cube : public Model {

private:
    Texture loadTexture(std::string path, TextureType type);
    static const std::vector<Vertex> Vertices;
public:
    Cube(glm::vec3 position  = glm::vec3(0.0f), glm::vec3 size = glm::vec3(1.0f), glm::vec3 rotation = glm::vec3(0.0f));
    void create(std::string diffuseTexture, std::string specularTexture = "");
    void create(glm::vec4 &color);
};

#endif