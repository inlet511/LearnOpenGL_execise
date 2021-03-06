
#define STB_IMAGE_IMPLEMENTATION
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include "stb_image.h"
#include <iostream>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <Camera.h>

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window, float deltaTime);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

unsigned int SCR_WIDTH = 800;
unsigned int SCR_HEIGHT = 600;

Camera camera(glm::vec3(1.0f,1.0f,3.0f),glm::vec3(0.0f,1.0f,0.0f),-75.0f,45.0f);

float deltaTime = 0.0f; // 当前帧与上一帧的时间差
float lastFrame = 0.0f; // 上一帧的时间

glm::vec3 lightPos(2.2f, 2.0f, 2.0f);
glm::vec3 objectPos(0.0f, 0.0f, 0.0f);

ImVec4 ambient_lightColor = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
ImVec4 diffuse_lightColor = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
ImVec4 specular_lightColor = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
float shininess = 32.0f;
float specular_multiplier = 0.5f;

int main()
{
	glfwInit();
	const char* glsl_version = "#version 130";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_SCALE_TO_MONITOR, GLFW_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// Setup Imgui
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); 
	(void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);


	Shader cubeShader("shaders/vertex.vert", "shaders/fragment.frag");
	Shader lightShader("shaders/vertex.vert", "shaders/fragment_light.frag");

	// set up vertex data and buffers
	// -----------------------
	float vertices[] = {
	 -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
	};

	unsigned int VBO;
	unsigned int VAO;
	unsigned int lightVAO;

	glGenVertexArrays(1, &VAO);
	glGenVertexArrays(1, &lightVAO);
	glGenBuffers(1, &VBO);

	// Bind Vertex Array Object
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


	// Bind Light Object Vertex Array
	glBindVertexArray(lightVAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(window))
	{
		float current_time = (float)glfwGetTime();
		deltaTime = current_time - lastFrame;
		lastFrame = current_time;

		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		{			
			ImGui::Begin("Control Panel!");
			ImGui::SliderFloat("Shininess", &shininess, 1.0f, 128.0f);
			ImGui::SliderFloat("Specular Multiplier", &specular_multiplier, 0.0f, 1.0f);
			ImGui::ColorEdit3("Ambient Light Color", (float*)&ambient_lightColor);
			ImGui::ColorEdit3("Diffuse Light Color", (float*)&diffuse_lightColor);
			ImGui::ColorEdit3("Specular Light Color", (float*)&specular_lightColor);
			ImGui::End();
		}

		processInput(window, deltaTime);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//lightPos = glm::vec3(
		//	glm::cos(glm::radians(100.0f * glfwGetTime())) * 2.0f,
		//	2.0f,
		//	glm::sin(glm::radians(100.0f * glfwGetTime())) * 2.0f
		//);

		// 绘制第一个立方体
		glBindVertexArray(VAO);

		cubeShader.use();
		cubeShader.setMatrix4("view", camera.GetViewMatrix());

		glm::mat4 projection = glm::mat4(1.0f);
		projection = glm::perspective<float>(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 1000.0f);
		cubeShader.setMatrix4("projection", projection);

		glm::mat4 model = glm::mat4(1.0f);
		glm::translate(model, objectPos);
		cubeShader.setMatrix4("model", model);

		glm::mat3 normalMatrix = glm::transpose(glm::inverse(model));
		cubeShader.setMatrix3("normalMatrix", normalMatrix);

		cubeShader.setVec3("objectColor", glm::vec3(1.0f, 0.5f, 0.31f));
		cubeShader.setVec3("ambient_lightColor", glm::vec3(ambient_lightColor.x,ambient_lightColor.y,ambient_lightColor.z));
		cubeShader.setVec3("diffuse_lightColor", glm::vec3(diffuse_lightColor.x, diffuse_lightColor.y, diffuse_lightColor.z));
		cubeShader.setVec3("specular_lightColor", glm::vec3(specular_lightColor.x, specular_lightColor.y, specular_lightColor.z));
		cubeShader.setVec3("lightPos", lightPos);
		cubeShader.setVec3("eyePos", camera.Position);
		cubeShader.setFloat("Shininess", shininess);
		cubeShader.setFloat("specularMultiplier", specular_multiplier);
		
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// 绘制第二个立方体（表示光源)
		glBindVertexArray(lightVAO);
		lightShader.use();
		lightShader.setMatrix4("view", camera.GetViewMatrix());
		lightShader.setMatrix4("projection", projection);
		lightShader.setVec3("objectColor", glm::vec3(1.0f));
		lightShader.setVec3("ambient_lightColor", glm::vec3(1.0f));
		lightShader.setVec3("diffuse_lightColor", glm::vec3(1.0f));
		lightShader.setVec3("specular_lightColor", glm::vec3(1.0f));
		lightShader.setFloat("Shininess", 1.0f);
		lightShader.setFloat("specularMultiplier", 1.0f);

		model = glm::mat4(1.0f);		
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.2f));
		lightShader.setMatrix4("model", model);

		normalMatrix = glm::transpose(glm::inverse(model));
		lightShader.setMatrix3("normalMatrix", normalMatrix);
		
		glDrawArrays(GL_TRIANGLES, 0, 36);


		// Rendering
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteVertexArrays(1, &lightVAO);
	glDeleteBuffers(1, &VBO);

	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();
	return 0;

}


void processInput(GLFWwindow* window, float deltaTime)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL)==GLFW_PRESS)
	{
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			camera.OnKeyboard(deltaTime, FORWARD);
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			camera.OnKeyboard(deltaTime, BACKWARD);
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			camera.OnKeyboard(deltaTime, LEFT);
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			camera.OnKeyboard(deltaTime, RIGHT);
	}
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	SCR_WIDTH = width;
	SCR_HEIGHT = height;
	glViewport(0, 0, width, height);
}


void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		camera.OnMouseMove(xpos, ypos);
}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		camera.OnScroll(yoffset);
}