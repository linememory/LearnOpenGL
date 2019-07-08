#ifndef TERRAIN_H
#define TERRAIN_H

#include "Mesh.h"
#include "Shader.h"
#include "noise/FastNoise.h"

class Terrain{
private:
    std::vector<Mesh> m_meshes;
    FastNoise m_noise;
    void generateTerain(float dimensionX, float dimensionY);
    void generateTerain2(float dimensionX, float dimensionY);
public:
    Terrain(float dimensionX, float dimensionY);
    void draw(Shader shader);
};

#endif