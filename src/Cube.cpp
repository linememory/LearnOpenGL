#include "Cube.h"

std::vector<Vertex> generateCube();

Cube::Cube(const std::string &diffuseTexture, const std::string &specularTexture){
    create(diffuseTexture, specularTexture);
    boundingBox.min = glm::vec3(-0.5f, -0.5f, -0.5f);
    boundingBox.max = glm::vec3(0.5f, 0.5f, 0.5f);

}

void Cube::create(std::string diffuseTexture, std::string specularTexture){
    std::vector<Texture> textures;

    //textures.push_back(loadTexture(diffuseTexture, TextureType::DIFFUSE));
    textures.push_back(TextureLoader::loadTexture(diffuseTexture, TextureType::DIFFUSE));
    if(specularTexture.size() != 0)
        textures.push_back(TextureLoader::loadTexture(specularTexture, TextureType::SPECULAR));
        //textures.push_back(loadTexture(specularTexture, TextureType::SPECULAR));
    m_meshes.push_back(Mesh(Vertices, std::vector<unsigned int>(), textures));
}

void Cube::create(glm::vec4 &color){

}

const std::vector<Vertex> Cube::Vertices {
        // front
        {{-0.5f,  0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f},},
        {{-0.5f, -0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f},},
        {{ 0.5f, -0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f},},
        {{-0.5f,  0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f},},
        {{ 0.5f, -0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f},},
        {{ 0.5f,  0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f},},
        // back
        {{ 0.5f,  0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f},},
        {{ 0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f},},
        {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {1.0f, 0.0f},},
        {{ 0.5f,  0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f},},
        {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {1.0f, 0.0f},},
        {{-0.5f,  0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f},},
        // left
        {{-0.5f, -0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 0.0f},},
        {{-0.5f, -0.5f,  0.5f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 0.0f},},
        {{-0.5f,  0.5f,  0.5f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 1.0f},},
        {{-0.5f,  0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 1.0f},},
        {{-0.5f, -0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 0.0f},},
        {{-0.5f,  0.5f,  0.5f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 1.0f},},
        // right
        {{0.5f, -0.5f,  0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f},},
        {{0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f},},
        {{0.5f,  0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f},},
        {{0.5f,  0.5f,  0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f},},
        {{0.5f, -0.5f,  0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f},},
        {{0.5f,  0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f},},
        // top
        {{ 0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f},},
        {{-0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f},},
        {{-0.5f,  0.5f,  0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f},},
        {{ 0.5f,  0.5f,  0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f},},
        {{ 0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f},},
        {{-0.5f,  0.5f,  0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f},},
        // bottom
        {{ 0.5f, -0.5f,  0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f},},
        {{-0.5f, -0.5f,  0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f},},
        {{-0.5f, -0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f},},
        {{ 0.5f, -0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f},},
        {{ 0.5f, -0.5f,  0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f},},
        {{-0.5f, -0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f},},
    };