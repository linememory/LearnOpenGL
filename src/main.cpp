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

void processInput(GLFWwindow* window);
void error_callback(int error, const char* description);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void scroll_callback(GLFWwindow* window, double, double);
void cursor_pos_callback(GLFWwindow* window, double xPos, double yPos);
unsigned int loadTexture(char const *path);

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


	float planeVertices[] = {
		-50.0f, 0.0f, -50.0f,  0.0f, 1.0f, 0.0f,
		 50.0f, 0.0f, -50.0f,  0.0f, 1.0f, 0.0f,
		 50.0f, 0.0f,  50.0f,  0.0f, 1.0f, 0.0f,
		 50.0f, 0.0f,  50.0f,  0.0f, 1.0f, 0.0f,
		-50.0f, 0.0f,  50.0f,  0.0f, 1.0f, 0.0f,
		-50.0f, 0.0f, -50.0f,  0.0f, 1.0f, 0.0f,
	};




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

	// glm::vec3 cubePositions[] = {
	// 	glm::vec3( 0.0f,  0.0f,  0.0f), 
	// 	glm::vec3( 2.0f,  5.0f, -15.0f), 
	// 	glm::vec3(-1.5f, -2.2f, -2.5f),  
	// 	glm::vec3(-3.8f, -2.0f, -12.3f),  
	// 	glm::vec3( 2.4f, -0.4f, -3.5f),  
	// 	glm::vec3(-1.7f,  3.0f, -7.5f),  
	// 	glm::vec3( 1.3f, -2.0f, -2.5f),  
	// 	glm::vec3( 1.5f,  2.0f, -2.5f), 
	// 	glm::vec3( 1.5f,  0.2f, -1.5f), 
	// 	glm::vec3(-1.3f,  1.0f, -1.5f),
	// };

	// std::array<glm::vec3, 4> pointLightPosition {
	// 	glm::vec3(0.7f, 0.2f, 2.0f),
	// 	glm::vec3(2.3f, -3.3f, -4.0f),
	// 	glm::vec3(-4.0f, 2.0f, -12.0f),
	// 	glm::vec3(0.0f, 0.0f, -3.0f),
	// };

	glm::vec3 cubePositions[] = {
		glm::vec3( 0.0f, 4.0f,  0.0f), 
		glm::vec3( 2.0f, 9.0f, -15.0f), 
		glm::vec3(-1.5f, 1.8f, -2.5f),  
		glm::vec3(-3.8f, 2.0f, -12.3f),  
		glm::vec3( 2.4f, 3.6f, -3.5f),  
		glm::vec3(-1.7f, 7.0f, -7.5f),  
		glm::vec3( 1.3f, 2.0f, -2.5f),  
		glm::vec3( 1.5f, 6.0f, -2.5f), 
		glm::vec3( 1.5f, 4.2f, -1.5f), 
		glm::vec3(-1.3f, 5.0f, -1.5f),
	};


	std::array<glm::vec3, 4> pointLightPosition {
		glm::vec3( 0.7f, 4.2f,  2.0f),
		glm::vec3( 2.3f, 1.7f, -4.0f),
		glm::vec3(-4.0f, 6.0f, -12.0f),
		glm::vec3( 0.0f, 4.0f, -3.0f),
	};
	

	// Cube
	unsigned int cubeVAO, lightVAO, planeVAO, VBO;
	glGenVertexArrays(1, &cubeVAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(cubeVAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
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
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	Shader lightShader("./data/shader/light.vs", "./data/shader/light.fs");

	// plane

	glGenVertexArrays(1, &planeVAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(planeVAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), planeVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)( 3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	Shader planeShader{"./data/shader/plane.vs", "./data/shader/plane.fs"};
	
	

	//Textures
	unsigned int diffuseContainer = loadTexture("./data/img/container-texture.png");
	unsigned int specularContainer = loadTexture("./data/img/container-specular.png");
	
	
	double previousFrameTime = glfwGetTime();

	glm::mat4 model = glm::mat4(1.0f);



	camera.setPosition(glm::vec3(1.2f, 1.0f, 2.0f));

	int frames = 0;
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
		//render

		// lights
		glm::vec3 lightColor = glm::vec3(1.0f, 0.95f, 0.9f);
		glm::vec3 lightAmbient = lightColor * 0.04f;
		glm::vec3 lightDiffuse = lightColor * 0.5f;
		glm::vec3 lightSpecular = lightColor;
		glm::vec3 dirLightColor = glm::vec3(1.0f, 1.0f, 1.0f);
		float linear = 0.09f;
		float quadratic = 0.032f;
		glm::vec3 dirLightDirection= glm::vec3(-0.2f, -1.0f, -0.3f);

		// plane
		glBindVertexArray(planeVAO);
		model = glm::mat4(1.0f);
		planeShader.use();
		planeShader.setMat4("model", glm::value_ptr(model));
		planeShader.setMat4("view", glm::value_ptr(view));
		planeShader.setMat4("projection", glm::value_ptr(projection));
		planeShader.setVec3("viewPos", camera.getPosition());
		planeShader.setVec3("material.diffuse", 0.5f, 0.5f, 0.5f);
		planeShader.setVec3("material.specular", 0.6f, 0.6f, 0.6f);
		planeShader.setFloat("material.shininess", 16.0f);
		planeShader.setVec3("dirLight.direction", dirLightDirection);
		planeShader.setVec3("dirLight.ambient", lightAmbient);
		planeShader.setVec3("dirLight.diffuse", lightDiffuse);
		planeShader.setVec3("dirLight.specular", lightSpecular);

		planeShader.setVec3("pointLights[0].position", glm::value_ptr(pointLightPosition[0]));
		planeShader.setFloat("pointLights[0].constant", 1.0f);
		planeShader.setFloat("pointLights[0].linear", linear);
		planeShader.setFloat("pointLights[0].quadratic", quadratic);
		planeShader.setVec3("pointLights[0].ambient", lightAmbient);
		planeShader.setVec3("pointLights[0].diffuse", lightDiffuse);
		planeShader.setVec3("pointLights[0].specular", lightSpecular);
		
		planeShader.setVec3("pointLights[1].position", glm::value_ptr(pointLightPosition[1]));
		planeShader.setFloat("pointLights[1].constant", 1.0f);
		planeShader.setFloat("pointLights[1].linear", linear);
		planeShader.setFloat("pointLights[1].quadratic", quadratic);
		planeShader.setVec3("pointLights[1].ambient", lightAmbient);
		planeShader.setVec3("pointLights[1].diffuse", lightDiffuse);
		planeShader.setVec3("pointLights[1].specular", lightSpecular);

		planeShader.setVec3("pointLights[2].position", glm::value_ptr(pointLightPosition[2]));
		planeShader.setFloat("pointLights[2].constant", 1.0f);
		planeShader.setFloat("pointLights[2].linear", linear);
		planeShader.setFloat("pointLights[2].quadratic", quadratic);
		planeShader.setVec3("pointLights[2].ambient", lightAmbient);
		planeShader.setVec3("pointLights[2].diffuse", lightDiffuse);
		planeShader.setVec3("pointLights[2].specular", lightSpecular);

		planeShader.setVec3("pointLights[3].position", glm::value_ptr(pointLightPosition[3]));
		planeShader.setFloat("pointLights[3].constant", 1.0f);
		planeShader.setFloat("pointLights[3].linear", linear);
		planeShader.setFloat("pointLights[3].quadratic", quadratic);
		planeShader.setVec3("pointLights[3].ambient", lightAmbient);
		planeShader.setVec3("pointLights[3].diffuse", lightDiffuse);
		planeShader.setVec3("pointLights[3].specular", lightSpecular);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		
		

		// Cubes
		cubeShader.use();
		cubeShader.setMat4("view", glm::value_ptr(view));
		cubeShader.setMat4("projection", glm::value_ptr(projection));
		cubeShader.setVec3("viewPos", camera.getPosition());
		cubeShader.setInt("material.diffuse", 0);
		cubeShader.setInt("material.specular", 1);
		cubeShader.setFloat("material.shininess", 32.0f);
		// directional light
		
		cubeShader.setVec3("dirLight.direction", dirLightDirection);
		cubeShader.setVec3("dirLight.ambient", lightAmbient);
		cubeShader.setVec3("dirLight.diffuse", lightDiffuse);
		cubeShader.setVec3("dirLight.specular", lightSpecular);
		// point light 1		
		cubeShader.setVec3("pointLights[0].position", glm::value_ptr(pointLightPosition[0]));
		cubeShader.setFloat("pointLights[0].constant", 1.0f);
		cubeShader.setFloat("pointLights[0].linear", linear);
		cubeShader.setFloat("pointLights[0].quadratic", quadratic);
		cubeShader.setVec3("pointLights[0].ambient", lightAmbient);
		cubeShader.setVec3("pointLights[0].diffuse", lightDiffuse);
		cubeShader.setVec3("pointLights[0].specular", lightSpecular);
		// point light 2
		cubeShader.setVec3("pointLights[1].position", glm::value_ptr(pointLightPosition[1]));
		cubeShader.setFloat("pointLights[1].constant", 1.0f);
		cubeShader.setFloat("pointLights[1].linear", linear);
		cubeShader.setFloat("pointLights[1].quadratic", quadratic);
		cubeShader.setVec3("pointLights[1].ambient", lightAmbient);
		cubeShader.setVec3("pointLights[1].diffuse", lightDiffuse);
		cubeShader.setVec3("pointLights[1].specular", lightSpecular);
		// point light 3
		cubeShader.setVec3("pointLights[2].position", glm::value_ptr(pointLightPosition[2]));
		cubeShader.setFloat("pointLights[2].constant", 1.0f);
		cubeShader.setFloat("pointLights[2].linear", linear);
		cubeShader.setFloat("pointLights[2].quadratic", quadratic);
		cubeShader.setVec3("pointLights[2].ambient", lightAmbient);
		cubeShader.setVec3("pointLights[2].diffuse", lightDiffuse);
		cubeShader.setVec3("pointLights[2].specular", lightSpecular);
		// point light 4
		cubeShader.setVec3("pointLights[3].position", glm::value_ptr(pointLightPosition[3]));
		cubeShader.setFloat("pointLights[3].constant", 1.0f);
		cubeShader.setFloat("pointLights[3].linear", linear);
		cubeShader.setFloat("pointLights[3].quadratic", quadratic);
		cubeShader.setVec3("pointLights[3].ambient", lightAmbient);
		cubeShader.setVec3("pointLights[3].diffuse", lightDiffuse);
		cubeShader.setVec3("pointLights[3].specular", lightSpecular);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffuseContainer);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, diffuseContainer);
		glBindVertexArray(cubeVAO);
		for(unsigned int i = 0; i < 10; i++)
		{
			model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			float angle = -20.0f * i; 
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			model = glm::rotate(model, (float)glfwGetTime() * glm::radians(5.0f), glm::vec3(0.5f, 1.0f, 0.0f));
			cubeShader.setMat4("model", value_ptr(model));
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}


		// point lights
		lightShader.use();
		lightShader.setMat4("view", glm::value_ptr(view));
		lightShader.setMat4("projection", glm::value_ptr(projection));
		glBindVertexArray(cubeVAO);
		for (int i = 0; i < pointLightPosition.size(); i++){
			model = glm::mat4(1.0f);
			model = glm::translate(model, pointLightPosition[i]);
			model = glm::scale(model, glm::vec3(0.2f));
			lightShader.setMat4("model", glm::value_ptr(model));
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		model = glm::mat4(1.0f);
		model = glm::translate(model, (glm::normalize(-dirLightDirection)*20.0f));
		lightShader.setMat4("model", glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// flashlight
		lightPos = camera.getPosition();
		model = glm::scale(model, glm::vec3(0.2f));
		lightShader.use();
		lightShader.setMat4("model", value_ptr(model));
		lightShader.setMat4("view", glm::value_ptr(view));
		lightShader.setMat4("projection", glm::value_ptr(projection));
		//glDrawArrays(GL_TRIANGLES, 0, 36);

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