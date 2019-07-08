#include "Cube.h"

Cube::Cube(glm::vec3 position, glm::vec3 size, glm::vec3 rotation) 
    : m_position{position}, m_size{size}, m_rotation{rotation}, m_shader{Shader{"data/shader/cube.vs", "data/shader/cube.fs"}}{
        createCube();
}

void Cube::setShader(std::string vertexShaderPath, std::string fragmentShaderPath){
    m_shader = Shader{vertexShaderPath.c_str(), fragmentShaderPath.c_str()};
}

void Cube::draw(glm::mat4 view, glm::mat4 projection){
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, m_position);
    model = glm::scale(model, m_size);
    //model = glm::rotate(model, )
    m_shader.use();
    m_shader.setMat4("model", glm::value_ptr(model));
    m_shader.setMat4("view", glm::value_ptr(view));
    m_shader.setMat4("projection", glm::value_ptr(projection));
    m_mesh.draw(m_shader);
}

void Cube::createCube(){
    m_vertices = {
        // front
        {{-0.5f,  0.5f, 0.5f}, {0.0f, 0.0f, 1.0f},},
        {{-0.5f, -0.5f, 0.5f}, {0.0f, 0.0f, 1.0f},},
        {{ 0.5f, -0.5f, 0.5f}, {0.0f, 0.0f, 1.0f},},
        {{-0.5f,  0.5f, 0.5f}, {0.0f, 0.0f, 1.0f},},
        {{ 0.5f, -0.5f, 0.5f}, {0.0f, 0.0f, 1.0f},},
        {{ 0.5f,  0.5f, 0.5f}, {0.0f, 0.0f, 1.0f},},
        // back
        {{ 0.5f,  0.5f, -0.5f}, {0.0f, 0.0f, -1.0f},},
        {{ 0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f},},
        {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f},},
        {{ 0.5f,  0.5f, -0.5f}, {0.0f, 0.0f, -1.0f},},
        {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f},},
        {{-0.5f,  0.5f, -0.5f}, {0.0f, 0.0f, -1.0f},},
        // left
        {{-0.5f,  0.5f,  0.5f}, {-1.0f, 0.0f, 0.0f},},
        {{-0.5f, -0.5f,  0.5f}, {-1.0f, 0.0f, 0.0f},},
        {{-0.5f, -0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f},},
        {{-0.5f,  0.5f,  0.5f}, {-1.0f, 0.0f, 0.0f},},
        {{-0.5f, -0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f},},
        {{-0.5f,  0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f},},
        // right
        {{0.5f,  0.5f, -0.5f}, {1.0f, 0.0f, 0.0f},},
        {{0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f},},
        {{0.5f, -0.5f,  0.5f}, {1.0f, 0.0f, 0.0f},},
        {{0.5f,  0.5f, -0.5f}, {1.0f, 0.0f, 0.0f},},
        {{0.5f, -0.5f,  0.5f}, {1.0f, 0.0f, 0.0f},},
        {{0.5f,  0.5f,  0.5f}, {1.0f, 0.0f, 0.0f},},
        // top
        {{-0.5f,  0.5f,  0.5f}, {0.0f, 1.0f, 0.0f},},
        {{-0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f},},
        {{ 0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f},},
        {{-0.5f,  0.5f,  0.5f}, {0.0f, 1.0f, 0.0f},},
        {{ 0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f},},
        {{ 0.5f,  0.5f,  0.5f}, {0.0f, 1.0f, 0.0f},},
        // bottom
        {{-0.5f, -0.5f, -0.5f}, {0.0f, 1.0f, 0.0f},},
        {{-0.5f, -0.5f,  0.5f}, {0.0f, 1.0f, 0.0f},},
        {{ 0.5f, -0.5f,  0.5f}, {0.0f, 1.0f, 0.0f},},
        {{-0.5f, -0.5f, -0.5f}, {0.0f, 1.0f, 0.0f},},
        {{ 0.5f, -0.5f,  0.5f}, {0.0f, 1.0f, 0.0f},},
        {{ 0.5f, -0.5f, -0.5f}, {0.0f, 1.0f, 0.0f},},
    };
    m_mesh = Mesh(m_vertices);
}