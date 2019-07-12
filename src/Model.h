#ifndef MODEL_H
#define MODEL_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <vector>
#include <iostream>
#include "Mesh.h"
#include "Shader.h"

struct Transform {
    glm::vec3 position;
    glm::vec3 size;
    glm::quat rotation;
};

class Model{
protected:
    std::vector<Mesh> m_meshes;
    Shader m_shader;
    Shader m_outlineShader;
    bool m_outline = false;
public:
    Transform transform;
    Model(glm::vec3 position  = glm::vec3(0.0f), glm::vec3 size = glm::vec3(1.0f), glm::quat rotation = glm::quat());
    void setMeshes(std::vector<Mesh> meshes);
    void addMesh(Mesh mesh);
    void setShader(const std::string &vertexShaderPath, const std::string &fragmentShaderPath);
    void draw(const glm::mat4 &view, const glm::mat4 &projection);
    void drawOutline(bool outline);
};

#endif