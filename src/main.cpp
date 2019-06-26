#include <iostream>
#include <iomanip> 
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <string>
#include <math.h>
#include "Shader.h"
#include "Camera.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


void processInput(GLFWwindow* window);
void error_callback(int error, const char* description);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void scroll_callback(GLFWwindow* window, double, double);
void cursor_pos_callback(GLFWwindow* window, double xPos, double yPos);
std::string readFile(std::string filePath);
unsigned int loadShaders(const char* vertex_shader_path, const char* fragment_shader_path);

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



	float cubeVertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,   0.0f,  0.0f, -1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,   0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,   0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,   0.0f,  0.0f, -1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,   0.0f,  0.0f, -1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,   0.0f,  0.0f, -1.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,   0.0f,  0.0f,  1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,   0.0f,  0.0f,  1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,   0.0f,  0.0f,  1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,   0.0f,  0.0f,  1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,   0.0f,  0.0f,  1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,   0.0f,  0.0f,  1.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  -1.0f,  0.0f,  0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,   1.0f,  0.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,   1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,   1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,   1.0f,  0.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,   1.0f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,   1.0f,  0.0f,  0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,   0.0f, -1.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,   0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,   0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,   0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,   0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,   0.0f, -1.0f,  0.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,   0.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,   0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,   0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,   0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,   0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,   0.0f,  1.0f,  0.0f,
	};


	

	// Cube
	unsigned int cubeVAO, lightVAO, cubeVBO;
	glGenBuffers(1, &cubeVBO);
	glGenVertexArrays(1, &cubeVAO);
	glBindVertexArray(cubeVAO);
	glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
	glEnableVertexAttribArray(2);
	

	Shader cubeShader{"./data/shader/cube.vs", "./data/shader/cube.fs"};
	
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	Shader lightShader("./data/shader/light.vs", "./data/shader/light.fs");

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
	
	double previousFrameTime = glfwGetTime();

	glm::mat4 model = glm::mat4(1.0f);

	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection;


	camera.setPosition(glm::vec3(1.2f, 1.0f, 2.0f));

	glm::vec3 cubePositions[] = {
		glm::vec3( 0.0f,  0.0f,  0.0f), 
		glm::vec3( 2.0f,  5.0f, -15.0f), 
		glm::vec3(-1.5f, -2.2f, -2.5f),  
		glm::vec3(-3.8f, -2.0f, -12.3f),  
		glm::vec3( 2.4f, -0.4f, -3.5f),  
		glm::vec3(-1.7f,  3.0f, -7.5f),  
		glm::vec3( 1.3f, -2.0f, -2.5f),  
		glm::vec3( 1.5f,  2.0f, -2.5f), 
		glm::vec3( 1.5f,  0.2f, -1.5f), 
		glm::vec3(-1.3f,  1.0f, -1.5f),
	};


	glEnable(GL_DEPTH_TEST);  
	int frames = 0;
	float count = 0;
	float speed = 5;
	float lastX = width/2, lastY = height/2;
	float sensivity = 0.05f;
	bool firstMouse = true;
	glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
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

		view = camera.getViewMatrix();
		projection = camera.getProjectionMatrix((float)windowWidth/windowHeight);
		//render
		glClearColor(0.3f, 0.32, 0.35, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		glBindVertexArray(cubeVAO);
		glm::mat4 lampModel = glm::mat4(1.0f);
		//lampModel = glm::rotate(lampModel, (float)glm::radians(glfwGetTime()*20), glm::vec3(0.0f, 1.0f, 0.0f));
		
		float radius = 10;
		lightPos = glm::vec3(sin(glfwGetTime()/2) * radius, 0.0f, cos(glfwGetTime()/2) * radius);
		lampModel = glm::translate(lampModel, lightPos);
		lampModel = glm::scale(lampModel, glm::vec3(0.2f));
		lightShader.use();
		lightShader.setMat4("model", value_ptr(lampModel));
		lightShader.setMat4("view", glm::value_ptr(view));
		lightShader.setMat4("projection", glm::value_ptr(projection));
		glm::vec3 lightColor;
		lightColor.x = sin(glfwGetTime() * 2.0f);
		lightColor.y = sin(glfwGetTime() * 0.7f);
		lightColor.z = sin(glfwGetTime() * 1.3f);
		glm::vec3 lightAmbient = lightColor * 0.3f;
		glm::vec3 lightDiffuse = lightColor * 0.8f;
		glDrawArrays(GL_TRIANGLES, 0, 36);
		for(unsigned int i = 0; i < 10; i++)
		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * i; 
			//model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			// if(i % 3 == 0)
			//model = glm::rotate(model, (float)glfwGetTime() * glm::radians(10.0f), glm::vec3(0.5f, 1.0f, 0.0f));
			cubeShader.use();
			cubeShader.setMat4("model", value_ptr(model));
			cubeShader.setMat4("view", glm::value_ptr(view));
			cubeShader.setMat4("projection", glm::value_ptr(projection));
			cubeShader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
			cubeShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
			cubeShader.setVec3("lightPos", glm::value_ptr(lightPos));
			cubeShader.setVec3("viewPos", camera.getPosition());
			cubeShader.setVec3("material.ambient", 0.25f, 0.25f, 0.25f);
			cubeShader.setVec3("material.diffuse", 0.4f, 0.4f, 0.4f);
			cubeShader.setVec3("material.specular", 0.774597f, 0.774597f, 0.774597f);
			cubeShader.setFloat("material.shininess", 76.0f);
			cubeShader.setVec3("light.ambient", lightAmbient);
			cubeShader.setVec3("light.diffuse", lightDiffuse);
			cubeShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		


		
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