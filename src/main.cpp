#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
#include "Camera.h"
#include <array>
#include <iostream>
#include "Model.h"
#include "Terrain.h"
#include "noise/FastNoise.h"


void processInput(GLFWwindow* window);
void error_callback(int error, const char* description);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void scroll_callback(GLFWwindow* window, double, double);
void cursor_pos_callback(GLFWwindow* window, double xPos, double yPos);
Mesh genPlane(int quadsX, int quadsY);

const unsigned int SCR_WIDTH = 800*2;
const unsigned int SCR_HEIGHT = 600*2;

int windowWidth = SCR_WIDTH, windowHeight = SCR_HEIGHT;

float deltaTime = 0;
float lastX = windowWidth/2.0f, lastY = windowHeight/2.0f;
bool firstMouse = true;


Camera camera;

int main() {
	// glfw: initialize and configure
	if(!glfwInit()){
		std::cerr << "Failed to initialize GLFW" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
	glfwSetErrorCallback(error_callback);
	// glfw window creation
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetCursorPosCallback(window, cursor_pos_callback);

	

	// glad: load all OpenGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

		glEnable(GL_DEPTH_TEST); 


	Shader modelShader{"./data/shader/model.vs", "./data/shader/model.fs"};
	Model nanosuit{"data/mesh/nanosuit/nanosuit.obj"};

	//Mesh terrain = genPlane(100, 100);
	Terrain terrain{100, 100};
	Shader waterShader{"./data/shader/water.vs", "./data/shader/water.fs"};
	Shader terrainShader{"./data/shader/terrain.vs", "./data/shader/terrain.fs"};


	
	
	
	float planeVertices[] = {
		-50.0f, 0.0f, -50.0f,  0.0f, 1.0f, 0.0f,
		 50.0f, 0.0f, -50.0f,  0.0f, 1.0f, 0.0f,
		 50.0f, 0.0f,  50.0f,  0.0f, 1.0f, 0.0f,
		 50.0f, 0.0f,  50.0f,  0.0f, 1.0f, 0.0f,
		-50.0f, 0.0f,  50.0f,  0.0f, 1.0f, 0.0f,
		-50.0f, 0.0f, -50.0f,  0.0f, 1.0f, 0.0f,
	};
	
	// plane
	unsigned int planeVAO, VBO;
	glGenVertexArrays(1, &planeVAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(planeVAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), planeVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	Shader planeShader{"./data/shader/plane.vs", "./data/shader/plane.fs"};
	

	glm::mat4 model = glm::mat4(1.0f);

	camera.setPosition(glm::vec3(1.2f, 1.0f, 2.0f));

	int frames = 0;
	double previousFrameTime = glfwGetTime();
	float count = 0;
	float speed = 5;
	float sensivity = 0.05f;
	bool firstMouse = true;
	glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

	while (!glfwWindowShouldClose(window))
	{
		deltaTime = glfwGetTime() - previousFrameTime;
		previousFrameTime = glfwGetTime();
		// std::cout << std::fixed << std::setprecision(4);
		// std::cout << delta << std::endl;
		int fps = 1/deltaTime;
		frames++;
		count += deltaTime;
		if (count >= 1.0f){
			//std::cout << frames << std::endl;
			frames = 0;
			count = 0;
		}

		//input
		processInput(window);

		glClearColor(0.25f, 0.61f, 0.95f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		glm::mat4 view = camera.getViewMatrix();
		glm::mat4 projection = camera.getProjectionMatrix((float)windowWidth/windowHeight);
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));

		//render
		modelShader.use();
		modelShader.setMat4("model", glm::value_ptr(model));
		modelShader.setMat4("view", glm::value_ptr(view));
		modelShader.setMat4("projection", glm::value_ptr(projection));
		nanosuit.draw(modelShader);
		// plane
		glBindVertexArray(planeVAO);
		model = glm::mat4(1.0f);
		planeShader.use();
		planeShader.setMat4("model", glm::value_ptr(model));
		planeShader.setMat4("view", glm::value_ptr(view));
		planeShader.setMat4("projection", glm::value_ptr(projection));
		//glDrawArrays(GL_TRIANGLES, 0, 6);
		//water.draw(planeShader);
		//glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

		terrainShader.use();
		terrainShader.setMat4("model", glm::value_ptr(model));
		terrainShader.setMat4("view", glm::value_ptr(view));
		terrainShader.setMat4("projection", glm::value_ptr(projection));
		terrain.draw(terrainShader);


		//chaeck and call events and swap the buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// glfw: terminate, clearing all previously allocated GLFW resources
	glfwTerminate();
	return 0;
}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	
	float speed = 5 * deltaTime;
	glm::vec3 pos = glm::vec3();
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
		pos.x += speed;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
		pos.x -= speed;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
		pos.y -= speed;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
		pos.y += speed;
	}
	camera.translate(pos);
}

void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
	windowWidth = width;
	windowHeight = height;
}

void cursor_pos_callback(GLFWwindow* window, double xPos, double yPos){
	float sensivity = 0.05f;
	if(firstMouse){
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}
	float xOffset = xPos - lastX;
	float yOffset = lastY - yPos;
	lastX = xPos;
	lastY = yPos;
	xOffset *= sensivity;
	yOffset *= sensivity;
	camera.rotate(yOffset, xOffset);
}

void scroll_callback(GLFWwindow* window, double xOffset, double yOffset) {
	camera.zoom(yOffset);
}

unsigned int loadTexture(char const *path){
	unsigned int ID = 0;
	glGenTextures(1, &ID);
	int width, height, nrComponents;
	unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
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
		std::cerr << "Failed to load texture at path: " << path << std::endl;
	}
	stbi_image_free(data);
	return ID;
}

Mesh genPlane(int quadsX, int quadsY){
	FastNoise noise;
	noise.SetNoiseType(FastNoise::SimplexFractal);
	quadsX++;
	quadsY++;
	std::vector<Vertex> vertices;
	float quadSize = 1.0f;
	glm::mat4 center = glm::mat4(1.0f);
	glm::vec3 move{-quadsX/2.0f, 0.0f, -quadsY/2.0f};
	center = glm::translate(center, move);
	for (unsigned int y = 0; y < quadsY; y++) {
		for (unsigned int x = 0; x < quadsX; x++) {
			Vertex vertex;
			float multiplier = 1.5f;
			glm::vec4 position = center * glm::vec4(x, noise.GetNoise(x*multiplier, y*multiplier)*10, y, 1.0f);
			vertex.position = glm::vec3(position);
			vertices.push_back(vertex);
		}
	}

	std::vector<unsigned int> indices;
	unsigned int y = 0;
	for (unsigned int i = 0; i < quadsX * (quadsY-1); i++){
		if((i+1) % (quadsX) != 0){
			indices.push_back(i);
			indices.push_back(i + 1);
			indices.push_back(i + quadsX + 1);

			indices.push_back(i);
			indices.push_back(i + quadsX + 1);
			indices.push_back(i + quadsX);
		} 
	}
	return Mesh(vertices, indices, std::vector<Texture>());
}