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

class Model{
protected:
    std::vector<Mesh> m_meshes;
    Shader m_shader;
    Shader m_outlineShader;
    glm::vec3 m_position;
    glm::vec3 m_size;
    glm::quat m_rotation;
    bool m_outline = false;
public:
    Model(glm::vec3 position  = glm::vec3(0.0f), glm::vec3 size = glm::vec3(1.0f), glm::quat rotation = glm::quat());
    void setMeshes(std::vector<Mesh> meshes);
    void addMesh(Mesh mesh);
    void setShader(std::string vertexShaderPath, std::string fragmentShaderPath);
    void loadTexture(std::string path, TextureType type);
    void draw(glm::mat4 view, glm::mat4 projection);
    void drawOutline(bool outline);
};

#endif