#include "Sphere.h"

Sphere::Sphere(glm::vec3 position  = glm::vec3(0.0f), glm::vec3 size = glm::vec3(1.0f), glm::vec3 rotation = glm::vec3(0.0f)) : 
    Model{position, size, rotation}{
    void create(std::string diffuseTexture, std::string specularTexture = "");
}
