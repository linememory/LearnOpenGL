#ifndef TEXTURE_LOADER_H
#define TEXTURE_LOADER_H

#include "Mesh.h"
#include "stb_image.h"

class TextureLoader{
private:
    static std::vector<Texture> texturesLoaded; 
    static unsigned int textureFromFile(const char *path);
public:
    static Texture loadTexture(std::string path, TextureType type);
};

#endif