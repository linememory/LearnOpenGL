#ifndef CUBE_H
#define CUBE_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include "Model.h"
#include "Mesh.h"
#include "Shader.h"
#include "TextureLoader.h"


class Cube : public Model {
private:
    //Texture loadTexture(std::string path, TextureType type);
    static const std::vector<Vertex> Vertices;
    void create(std::string diffuseTexture, std::string specularTexture = "");
    void create(glm::vec4 &color);
public:
    Cube(const std::string &diffuseTexture, const std::string &specularTexture = "");
};

#endif