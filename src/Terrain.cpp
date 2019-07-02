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
	m_noise.SetNoiseType(FastNoise::NoiseType::ValueFractal);
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
			float multiplier = 0.5f;
			glm::vec4 position = center * glm::vec4(x, m_noise.GetNoise(x*multiplier, y*multiplier)*10, y, 1.0f);
			vertex.position = glm::vec3(position);
			vertex.normal = glm::vec3(-0.24f, -1, 0.31f);
			vertices.push_back(vertex);
		}
	}

	std::vector<unsigned int> indices, indices2;
	std::vector<Vertex> vertices2;
	unsigned int y = 0;
	for (unsigned int i = 0; i < dimensionX * (dimensionY-1); i++){
		if((i+1) % (unsigned int)(dimensionX) != 0){
			glm::vec3 normal, normal1, normal2;
			indices.push_back(i);
			indices.push_back(i + 1);
			indices.push_back(i + dimensionX + 1);
			normal1 = glm::cross(vertices[i + 1].position - vertices[i].position, vertices[i + dimensionX + 1].position - vertices[i].position);

			indices.push_back(i);
			indices.push_back(i + dimensionX + 1);
			indices.push_back(i + dimensionX);
			normal2 = glm::cross(vertices[i + 1].position - vertices[i].position, vertices[i + dimensionX + 1].position - vertices[i].position);
			vertices[i].normal = glm::normalize(normal1 + normal2);

			// Vertex vertexA, vertexB, vertexC;
			// vertexA.position = vertices[i].position;
			// vertexB.position = vertices[i+1].position;
			// vertexC.position = vertices[i + dimensionX + 1].position;
			// normal = glm::cross(vertexB.position - vertexA.position, vertexC.position - vertexA.position);
			// vertexA.normal = normal;
			// vertexB.normal = normal;
			// vertexC.normal = normal;
			// //std::cout << normal.x << normal.y << normal.z << std::endl;
			// vertices2.push_back(vertexA);
			// vertices2.push_back(vertexB);
			// vertices2.push_back(vertexC);
			// indices2.push_back(i);
			// indices2.push_back(i+1);
			// indices2.push_back(i+2);
			
			// vertexA.position = vertices[i].position;
			// vertexB.position = vertices[i + dimensionX + 1].position;
			// vertexC.position = vertices[i + dimensionX].position;
			// normal = glm::cross(vertexB.position - vertexA.position, vertexC.position - vertexA.position);
			// vertexA.normal = normal;
			// vertexB.normal = normal;
			// vertexC.normal = normal;
			// vertices2.push_back(vertexA);
			// vertices2.push_back(vertexB);
			// vertices2.push_back(vertexC);
			// indices2.push_back(i);
			// indices2.push_back(i+1);
			// indices2.push_back(i+2);
		} 
	}
	m_meshes.push_back(Mesh(vertices, indices, std::vector<Texture>()));
	//m_meshes.push_back(Mesh(vertices2, indices2, std::vector<Texture>()));
}