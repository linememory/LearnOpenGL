#include "ModelImporter.h"
#include "stb_image.h"

unsigned int TextureFromFile(const char *path, const std::string &directory);


void ModelImporter::loadModel(std::string const &path, Model &model){
    Assimp::Importer import;
    const aiScene *scene = import.ReadFile(path, aiProcess_FlipUVs | aiProcess_Triangulate);
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode){
        std::cerr << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
        return;
        //return m_meshes;
    }
    m_directory = path.substr(0, path.find_last_of('/'));
    processNode(scene->mRootNode, scene);
    model.setMeshes(m_meshes);
    model.boundingBox = boundingBox;
    //return m_meshes;
}

void ModelImporter::processNode(aiNode const *node, const aiScene *scene){
   for (unsigned int i = 0; i < node->mNumMeshes; i++){
       aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
       m_meshes.push_back(processMesh(mesh, scene));
    }
    for (int i = 0; i < node->mNumChildren; i++){
        processNode(node->mChildren[i], scene);
    }
}

Mesh ModelImporter::processMesh(aiMesh const *mesh, const aiScene *scene){
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;
    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        glm::vec3 vector;
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.position = vector;

        // set the bounding box
        boundingBox.min.x = (boundingBox.min.x > mesh->mVertices[i].x) ? mesh->mVertices[i].x : boundingBox.min.x;
        boundingBox.min.y = (boundingBox.min.y > mesh->mVertices[i].y) ? mesh->mVertices[i].y : boundingBox.min.y;
        boundingBox.min.z = (boundingBox.min.z > mesh->mVertices[i].z) ? mesh->mVertices[i].z : boundingBox.min.z;
        boundingBox.max.x = (boundingBox.max.x < mesh->mVertices[i].x) ? mesh->mVertices[i].x : boundingBox.max.x;
        boundingBox.max.y = (boundingBox.max.y < mesh->mVertices[i].y) ? mesh->mVertices[i].y : boundingBox.max.y;
        boundingBox.max.z = (boundingBox.max.z < mesh->mVertices[i].z) ? mesh->mVertices[i].z : boundingBox.max.z;

        vector.x = mesh->mNormals[i].x;
        vector.y = mesh->mNormals[i].y;
        vector.z = mesh->mNormals[i].z;
        vertex.normal = vector;
        if(mesh->mTextureCoords[0]){
            vertex.texCoords = glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
        } else {
            vertex.texCoords = glm::vec2(0.0f);
        }
        vertices.push_back(vertex);
    }

    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        for(unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }
    
    if(mesh->mMaterialIndex >= 0){
        aiMaterial const *material = scene->mMaterials[mesh->mMaterialIndex];
        std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, TextureType::DIFFUSE);
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
        std::vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, TextureType::SPECULAR);
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    }
    
    return Mesh(vertices, indices, textures);
}

std::vector<Texture> ModelImporter::loadMaterialTextures(aiMaterial const *mat, aiTextureType type, TextureType typeName){
    std::vector<Texture> textures;
    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++){
        aiString str;
        mat->GetTexture(type, i, &str);
        bool skip = false;
        for (unsigned int j = 0; j < m_texturesLoaded.size(); j++)
        {
            if(std::strcmp(m_texturesLoaded[j].path.c_str(), str.C_Str()) == 0){
                textures.push_back(m_texturesLoaded[j]);
                skip = true;
                break;
            }
        }
        if(!skip){
            Texture texture;
            texture.id = TextureFromFile(str.C_Str(), m_directory);
            texture.type = typeName;
            texture.path = str.C_Str();
            textures.push_back(texture);
            m_texturesLoaded.push_back(texture);
        }
    }
    return textures;
}

unsigned int TextureFromFile(const char *path, const std::string &directory){
    std::string filename = directory + "/" + path;
    unsigned int ID = 0;
	glGenTextures(1, &ID);
	int width, height, nrComponents;
	unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
	if(data){
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;
		glBindTexture(GL_TEXTURE_2D, ID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	} else {
		std::cerr << "Failed to load texture at path: " << filename.c_str() << std::endl;
	}
	stbi_image_free(data);
	return ID;
}
