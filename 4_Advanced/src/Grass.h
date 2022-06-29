#ifndef GRASS_H
#define GRASS_H

#include "Model.h"

class Grass : public Model{
private:

public:
    Grass(const std::string texture = "data/img/grass.png");
    Texture loadTexture(std::string path, TextureType type);
};

#endif