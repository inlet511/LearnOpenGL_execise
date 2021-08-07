#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "Shader.h"
#include "Camera.h"
#include "Model.h"

#include <iostream>
#include <vector>


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void processInput(GLFWwindow* window);
int InitializeEnvi();


bool right_mouse_button_down = false;

// settings
unsigned int scr_width = 1280;
unsigned int scr_height = 720;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = (float)scr_width / 2.0;
float lastY = (float)scr_height / 2.0;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;
GLFWwindow* window = nullptr;

int main()
{
	int result = InitializeEnvi();
	if (result != 0)
		return result;

	glEnable(GL_DEPTH_TEST);


	Model planet("models/planet.obj");
	Model rock("models/rock.obj");

	Shader planetShader("shaders/planet.vert", "shaders/planet.frag");
	Shader instanceShader("shaders/instanced_array.vert", "shaders/instanced_array.frag");

	unsigned int amount = 100000;
	glm::mat4* modelMatrices;
	modelMatrices = new glm::mat4[amount];
	srand((unsigned int)glfwGetTime());
	float radius = 150.0;
	float offset = 25.0f;

	for (unsigned int i = 0; i < amount; i++)
	{
		glm::mat4 model;
		float angle = (float)i / (float)amount * 360.0f;
		float displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
		float x = sin(angle) * radius + displacement;
		displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
		float y = displacement * 0.4f; // 让行星带的高度比x和z的宽度要小
		displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
		float z = cos(angle) * radius + displacement;
		model = glm::translate(model, glm::vec3(x, y, z));

		// 2. 缩放：在 0.05 和 0.25f 之间缩放
		float scale = float(rand() % 20) / 100.0f + 0.05;
		model = glm::scale(model, glm::vec3(scale));

		// 3. 旋转：绕着一个（半）随机选择的旋转轴向量进行随机的旋转
		float rotAngle = float(rand() % 360);
		model = glm::rotate(model, rotAngle, glm::vec3(0.4f, 0.6f, 0.8f));

		// 4. 添加到矩阵的数组中
		modelMatrices[i] = model;
	}


	unsigned int buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, amount * sizeof(glm::mat4), &modelMatrices[0], GL_STATIC_DRAW);

	for (unsigned int i = 0; i < rock.meshes.size(); i++)
	{
		unsigned int VAO = rock.meshes[i].VAO;
		glBindVertexArray(VAO);
		// 顶点属性
		GLsizei vec4Size = sizeof(glm::vec4);
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)0);
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(vec4Size));
		glEnableVertexAttribArray(5);
		glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(2 * vec4Size));
		glEnableVertexAttribArray(6);
		glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(3 * vec4Size));

		glVertexAttribDivisor(3, 1);
		glVertexAttribDivisor(4, 1);
		glVertexAttribDivisor(5, 1);
		glVertexAttribDivisor(6, 1);

		glBindVertexArray(0);
	}


	// render loop
	while (!glfwWindowShouldClose(window))
	{
		// per-frame time logic
		// --------------------
		float currentFrame = (float)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// input
		// -----
		processInput(window);

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		planetShader.use();
		
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)scr_width / (float)scr_height, 0.1f, 100.0f);
		glm::mat4 view = camera.GetViewMatrix();
		glm::mat4 model_matrix = glm::mat4(1.0f);
		model_matrix = glm::scale(model_matrix, glm::vec3(4.0f));

		planetShader.setMatrix4("projection", projection);		
		planetShader.setMatrix4("view", view);
		planetShader.setMatrix4("model", model_matrix);		
		planet.Draw(planetShader);


		instanceShader.use();
		instanceShader.setMatrix4("projection", projection);
		instanceShader.setMatrix4("view", view);
		instanceShader.setInt("texture_diffuse1", 0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, rock.textures_loaded[0].id); // note: we also made the textures_loaded vector public (instead of private) from the model class.
		for (unsigned int i = 0; i < rock.meshes.size(); i++)
		{
			glBindVertexArray(rock.meshes[i].VAO);
			glDrawElementsInstanced(GL_TRIANGLES, rock.meshes[i].indices.size(), GL_UNSIGNED_INT, 0, amount);
			glBindVertexArray(0);
		}



		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

int InitializeEnvi()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(scr_width, scr_height, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	// Set context
	glfwMakeContextCurrent(window);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// add callbacks
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);

	return 0;
}

void processInput(GLFWwindow* window)
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
	glViewport(0, 0, width, height);
	scr_width = width;
	scr_height = height;
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