#include "Terrain.h"


Terrain::Terrain(float dimensionX, float dimensionY){
    generateTerain(dimensionX, dimensionY);
}

void Terrain::draw(Shader shader){
    for(auto m : m_meshes){
        m.draw(shader);
    }
}


void Terrain::generateTerain(float dimensionX, float dimensionY){
	m_noise.SetNoiseType(FastNoise::SimplexFractal);
	dimensionX++;
	dimensionY++;
	std::vector<Vertex> vertices;
	float quadSize = 1.0f;
	glm::mat4 center = glm::mat4(1.0f);
	glm::vec3 move{-dimensionX/2.0f, 0.0f, -dimensionY/2.0f};
	center = glm::translate(center, move);
	for (unsigned int y = 0; y < dimensionY; y++) {
		for (unsigned int x = 0; x < dimensionX; x++) {
			Vertex vertex;
			float multiplier = 1.5f;
			glm::vec4 position = center * glm::vec4(x, m_noise.GetNoise(x*multiplier, y*multiplier)*10, y, 1.0f);
			vertex.position = glm::vec3(position);
			vertices.push_back(vertex);
		}
	}

	std::vector<unsigned int> indices;
	unsigned int y = 0;
	for (unsigned int i = 0; i < dimensionX * (dimensionY-1); i++){
		if((i+1) % (unsigned int)(dimensionX) != 0){
			indices.push_back(i);
			indices.push_back(i + 1);
			indices.push_back(i + dimensionX + 1);

			indices.push_back(i);
			indices.push_back(i + dimensionX + 1);
			indices.push_back(i + dimensionX);
		} 
	}
	m_meshes.push_back(Mesh(vertices, indices, std::vector<Texture>()));
}