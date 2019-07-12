#ifndef SPHERE_H
#define SPHERE_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include "Model.h"
#include "Mesh.h"
#include "Shader.h"

enum class SphereType{
    UV_SPHERE,
    NORMALIZED_CUBE,
    SPHERIFIED_CUBE,
    ICOSAHEDRON,
};

class Sphere : public Model{
private:
    void create(std::string diffuseTexture, std::string specularTexture = "");
    void create(glm::vec4 &color);
    void createNormCube(glm::vec4 &color);
    void createSpherifiedCube(glm::vec4 &color);
    void createIcosahedron(int subdivisions);
public:
    Sphere(SphereType type, int faces, const std::string &diffuseTexture, const std::string &specularTexture = "");
};

#endif