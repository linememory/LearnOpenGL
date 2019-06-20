#include <iostream>
#include <iomanip> 
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <string>
#include <math.h>
#include "Shader.h"
#include "VertexArrayObject.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


void processInput(GLFWwindow* window);
void error_callback(int error, const char* description);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void scroll_callback(GLFWwindow* window, double, double);
std::string readFile(std::string filePath);
unsigned int loadShaders(const char* vertex_shader_path, const char* fragment_shader_path);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

float amount = 0.2f;

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
	
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetScrollCallback(window, scroll_callback);

	// glad: load all OpenGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// build and compile our shader program
	Shader textureShader{"./data/shader/vertex2_shader.vs", "./data/shader/fragment2_shader.fs"};

	float texVertices[] = {
		 0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
		 0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
		-0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f,
		-0.5f,  0.5f, 0.0f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f,
	};
	unsigned int texIndices[] = {
		0, 1, 3,
		1, 2, 3
	};


	unsigned int texTriVAO, texTriVBO, TexTriEBO;
	glGenBuffers(1, &texTriVBO);
	glGenBuffers(1, &TexTriEBO);
	glGenVertexArrays(1, &texTriVAO);

	glBindVertexArray(texTriVAO);

	glBindBuffer(GL_ARRAY_BUFFER, texTriVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(texVertices), texVertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, TexTriEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(texIndices), texIndices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
	
	//Textures
	unsigned int texture0, texture1;
	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &texture0);
	glBindTexture(GL_TEXTURE_2D, texture0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char *data = stbi_load("./data/img/container.jpg", &width, &height, &nrChannels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	} else {
		std::cerr << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	glActiveTexture(GL_TEXTURE1);
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	data = stbi_load("./data/img/awesomeface.png", &width, &height, &nrChannels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	} else {
		std::cerr << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	glm::vec3 rotAxis = glm::vec3(0.0f, 0.0f, 1.0f);
	float rotAngle{0.0f};
	glm::mat4 trans = glm::mat4(1.0f);
	

	textureShader.use();
	textureShader.setInt("texture0", 0);
	textureShader.setInt("texture1", 1);
	textureShader.setFloat("amount", amount);
	textureShader.setMatrix("trans", glm::value_ptr(trans));


	double previousFrameTime = glfwGetTime();


	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	while (!glfwWindowShouldClose(window))
	{
		double delta = glfwGetTime() - previousFrameTime;
		previousFrameTime = glfwGetTime();
		// std::cout << std::fixed << std::setprecision(4);
		// std::cout << delta << std::endl;
		//input
		processInput(window);
		//render
		glClearColor(0.1f, 0.3f, 0.4f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		textureShader.use();
		textureShader.setFloat("amount", amount);
		glBindVertexArray(texTriVAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		rotAngle = 100.0f * delta; 
		trans = glm::rotate(trans, glm::radians(rotAngle), rotAxis);
		textureShader.setMatrix("trans", glm::value_ptr(trans));
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
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS){
		amount += 0.001f;
		if(amount > 1.0f)
			amount = 1.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS){
		amount -= 0.001f;
		if(amount < 1.0f)
			amount = 0.0f;
	}
	
}

void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
	//std::cerr << width << " - " << height << std::endl;
}

void scroll_callback(GLFWwindow* window, double a, double b) {
	//std::cerr << a << " - " << b << std::endl;
}