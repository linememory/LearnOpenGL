#ifndef SPHERE_H
#define SPHERE_H

#include "Model.h"

class Sphere : Model{

public:
    Sphere(glm::vec3 position  = glm::vec3(0.0f), glm::vec3 size = glm::vec3(1.0f), glm::vec3 rotation = glm::vec3(0.0f));
    
};

#endif