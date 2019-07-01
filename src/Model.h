#ifndef MODEL_H
#define MODEL_H

#include <iostream>
#include <vector>
#include <string>
#include "Shader.h"
#include "Mesh.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <glm/glm.hpp>



class Model 
{
private:
    std::vector<Mesh> m_meshes;
    std::string m_directory;
    std::vector<Texture> m_textures_loaded;
    bool m_gammaCorrection;

    void loadModel(std::string const &path);
    void processNode(aiNode const *node, const aiScene *scene);
    Mesh processMesh(aiMesh const *mesh, const aiScene *scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial const *mat, aiTextureType type, std::string typeName);
public:
    Model(std::string const &path, bool gammaCorrection = false);
    void draw(Shader shader);
};

#endif