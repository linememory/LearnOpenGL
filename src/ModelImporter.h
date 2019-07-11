#ifndef IMPORTMODEL_H
#define IMPORTMODEL_H

#include <string>
#include <vector>
#include "Mesh.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class ModelImporter{
private:
    std::vector<Mesh> m_meshes;
    std::vector<unsigned int> m_indices;
    std::vector<Texture> m_textures;
    std::vector<Texture> m_texturesLoaded;
    std::string m_directory;

    void processNode(aiNode const *node, const aiScene *scene);
    Mesh processMesh(aiMesh const *mesh, const aiScene *scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial const *mat, aiTextureType type, TextureType typeName);
public:
    std::vector<Mesh> loadModel(std::string const &path);
};

#endif
