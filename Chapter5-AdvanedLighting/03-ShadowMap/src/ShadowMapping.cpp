
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
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

unsigned int SCR_WIDTH  = 800;
unsigned int SCR_HEIGHT = 600;

Camera camera;

float deltaTime = 0.0f; // 当前帧与上一帧的时间差
float lastFrame = 0.0f; // 上一帧的时间

glm::vec3 lightPos (2.2f, 2.0f, 2.0f);
glm::vec3 objectPos(0.0f, 0.0f, 0.0f);


ImVec4 light_ambient  = ImVec4(0.2f, 0.2f, 0.2f,1.0f);
ImVec4 light_diffuse  = ImVec4(0.5f, 0.5f, 0.5f,1.0f);
ImVec4 light_specular = ImVec4(1.0f, 1.0f, 1.0f,1.0f);
ImVec4 light_position = ImVec4(2.2f, 2.0f, 2.0f,1.0f);

ImVec4 material_ambient   = ImVec4(0.2f, 0.2f, 0.2f, 1.0f);
ImVec4 material_diffuse   = ImVec4(0.5f, 0.5f, 0.5f, 1.0f);
ImVec4 material_specular  = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
float  material_shininess = 32.0f;
bool right_mouse_button_down = false;

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
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
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetScrollCallback(window, scroll_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 130");


	Shader cubeShader("shaders/vertex.vert", "shaders/blinn_phong.frag");
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

	float planeVertices[] = {
		5.0f, 0.5f, 5.0f, 2.0f, 0.0f,
		-5.0f, -0.5f, 5.0f, 0.0f, 0.0f,
		-5.0f, -0.5f, -5.0f, 0.0f, 2.0f,

		5.0f, -0.5f, 5.0f, 2.0f, 0.0f,

	}

	unsigned int VBO;
	unsigned int VAO;
	unsigned int EBO;
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
			ImGui::Text("Light Settings");
			ImGui::BeginGroup();
			ImGui::ColorEdit3("Light Ambient"  , (float*)&light_ambient);
			ImGui::ColorEdit3("Light Diffuse"  , (float*)&light_diffuse);
			ImGui::ColorEdit3("Light Specular" , (float*)&light_specular);
			ImGui::InputFloat3("Light Position", (float*)&light_position);
			ImGui::EndGroup();

			ImGui::Text("Material Settings");
			ImGui::BeginGroup();
			ImGui::ColorEdit3("Material Ambient"  , (float*)&material_ambient);
			ImGui::ColorEdit3("Material Diffuse"  , (float*)&material_diffuse);
			ImGui::ColorEdit3("Material Specular" , (float*)&material_specular);
			ImGui::SliderFloat("Shininess", (float*)&material_shininess, 0.0f, 256.0f);
			ImGui::EndGroup();
			ImGui::End();
		}


		processInput(window, deltaTime);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



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

		cubeShader.setVec3("light.ambient" , glm::vec3(light_ambient.x, light_ambient.y, light_ambient.z));
		cubeShader.setVec3("light.diffuse" , glm::vec3(light_diffuse.x, light_diffuse.y, light_diffuse.z));
		cubeShader.setVec3("light.specular", glm::vec3(light_specular.x, light_specular.y, light_specular.z));
		cubeShader.setVec3("light.position", glm::vec3(light_position.x, light_position.y, light_position.z));

		cubeShader.setVec3("eyePos", camera.Position);

		cubeShader.setFloat("material.shininess", material_shininess);
		cubeShader.setVec3 ("material.diffuse"  , glm::vec3(material_diffuse.x, material_diffuse.y, material_diffuse.z));
		cubeShader.setVec3 ("material.specular" , glm::vec3(material_specular.x, material_specular.y, material_specular.z));
		cubeShader.setVec3 ("material.ambient"  , glm::vec3(material_ambient.x, material_ambient.y, material_ambient.z));

		
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// 绘制第二个立方体（表示光源)
		glBindVertexArray(lightVAO);
		lightShader.use();
		lightShader.setMatrix4("view", camera.GetViewMatrix());
		lightShader.setMatrix4("projection", projection);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(light_position.x, light_position.y, light_position.z));
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
	glDeleteBuffers(1, &EBO);
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
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.OnKeyboard(deltaTime, FORWARD);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.OnKeyboard(deltaTime, BACKWARD);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.OnKeyboard(deltaTime, LEFT);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.OnKeyboard(deltaTime, RIGHT);
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		camera.OnKeyboard(deltaTime, UP);
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		camera.OnKeyboard(deltaTime, DOWN);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	SCR_WIDTH = width;
	SCR_HEIGHT = height;
	glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (right_mouse_button_down)
	{
		camera.OnMouseMove(xpos, ypos);
	}
	else
	{
		camera.Initialize();
	}
}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.OnScroll(yoffset);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
		right_mouse_button_down = true;
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
		right_mouse_button_down = false;
}