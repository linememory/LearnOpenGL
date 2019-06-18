#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <string>
#include <math.h>
#include "Shader.h"
#include "VertexArrayObject.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void processInput(GLFWwindow* window);
void error_callback(int error, const char* description);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void scroll_callback(GLFWwindow* window, double, double);
std::string readFile(std::string filePath);
unsigned int loadShaders(const char* vertex_shader_path, const char* fragment_shader_path);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

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
	Shader shader1{"./data/shader/vertex_shader.txt", "./data/shader/fragment_shader.txt"};
	Shader shader2{"./data/shader/vertex2_shader.txt", "./data/shader/fragment2_shader.txt"};


	// set up vertex data (and buffer(s)) and configure vertex attributes
	float vertices[] = {
		0.5f, 0.0f, 0.0f,
		-0.5f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f,
		0.5f, 0.5f, 0.0f,
		0.5f, 0.0f, 0.0f
	};
	float vertices1[] = {
		0.5f, -0.0f, 0.0f,
		-0.5f, -0.0f, 0.0f,
		-0.5f, -0.5f, 0.0f,
	};
	float vertices2[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.5f, -0.0f, 0.0f
	};
	float vertices3[] = {
		0.5f, 0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
		0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
		1.0f, 0.5f, 0.0f,  0.0f, 0.0f, 1.0f,
		1.0f, 0.5f, 0.0f,  0.0f, 0.0f, 1.0f,
		1.0f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f,
		0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
	};
	float vertices4[] = {
		-0.5f, 0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
		-1.0f, 0.5f, 0.0f,  0.0f, 0.0f, 1.0f,
		-1.0f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f,
	};
	unsigned int indices[] = {
		0, 1, 2,
		1, 2, 3
	};
	float vertices5[] = {
		-0.5f, 1.0f, 0.0f,
		0.5f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.0f
	};

	// glGenVertexArrays(1, &VAO5);
	// glGenBuffers(1, &VBO);
	// glBindVertexArray(VAO5);
	// glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// glBufferData(GL_ARRAY_BUFFER, sizeof(vertices5), vertices5, GL_STATIC_DRAW);
	// glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	// glEnableVertexAttribArray(0);

	VertexArrayObject v1, v2, v3, v4, v5, v6;
	v1.setVertexData(vertices5, sizeof(vertices5)/sizeof(*vertices5));
	v1.setVertexAttribPointer(0, 3, 0, 0);
	v1.setShaderProgram(shader2);

	v2.setVertexData(vertices4, sizeof(vertices4)/sizeof(*vertices4));
	v2.setIndices(indices, sizeof(indices)/sizeof(*indices));
	v2.setVertexAttribPointer(0, 3, 0, 6);
	v2.setVertexAttribPointer(1, 3, 3, 6);
	v2.setShaderProgram(shader2);

	v3.setVertexData(vertices3, sizeof(vertices3)/sizeof(*vertices3));
	v3.setVertexAttribPointer(0, 3, 0, 6);
	v3.setVertexAttribPointer(1, 3, 3, 6);
	v3.setShaderProgram(shader2);

	v4.setVertexData(vertices2, sizeof(vertices2)/sizeof(*vertices2));
	v4.setVertexAttribPointer(0, 3, 0, 0);
	v4.setShaderProgram(shader1);

	v5.setVertexData(vertices1, sizeof(vertices1)/sizeof(*vertices1));
	v5.setVertexAttribPointer(0, 3, 0, 0);
	v5.setShaderProgram(shader1);

	v6.setVertexData(vertices, sizeof(vertices)/sizeof(*vertices));
	v6.setVertexAttribPointer(0, 3, 0, 0);
	v6.setShaderProgram(shader1);


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
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	

	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	int width, height, nrChannels;
	unsigned char *data = stbi_load("./data/img/container.jpg", &width, &height, &nrChannels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	} else {
		std::cerr << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
	
	

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	while (!glfwWindowShouldClose(window))
	{
		//input
		processInput(window);
		//render
		glClearColor(0.1f, 0.3f, 0.4f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		// set the color by uniform variable
		float time = static_cast<float>(glfwGetTime());
		float greenValue = sin(time*2) / 2.0f + 0.5f;
		shader1.use();
		shader1.setFloat("green", greenValue);

		shader2.use();
		glBindTexture(GL_TEXTURE_2D, texture);
		glBindVertexArray(texTriVAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// v1.setShaderProgram(shader2);
		// v2.setShaderProgram(shader2);
		// v3.setShaderProgram(shader2);
		// v1.draw();
		// v2.draw();
		// v3.draw();
		// v4.draw();
		// v5.draw();
		// v6.draw();
		
		// wireframe
		// shader1.use();
		// shader1.setFloat("green", 0.0f);
		// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		// v1.setShaderProgram(shader1);
		// v2.setShaderProgram(shader1);
		// v3.setShaderProgram(shader1);
		// v1.draw();
		// v2.draw();
		// v3.draw();
		// v4.draw();
		// v5.draw();
		// v6.draw();
		

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