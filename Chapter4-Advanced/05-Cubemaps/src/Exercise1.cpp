
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

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void processInput(GLFWwindow *window);
unsigned int loadTexture(const char *path);
unsigned int loadCubeTexture(vector<std::string> paths);



// settings
const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 720;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = (float)SCR_WIDTH / 2.0;
float lastY = (float)SCR_HEIGHT / 2.0;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

bool right_mouse_button_down = false;

vector<std::string> cubemap_paths
{
	"Res/Images/Lycksele2/px.jpg",
	"Res/Images/Lycksele2/nx.jpg",
	"Res/Images/Lycksele2/py.jpg",
	"Res/Images/Lycksele2/ny.jpg",
	"Res/Images/Lycksele2/pz.jpg",
	"Res/Images/Lycksele2/nz.jpg",
};

float skyboxVertices[] = {
	// positions          
		   -1.0f,  1.0f, -1.0f,
		   -1.0f, -1.0f, -1.0f,
			1.0f, -1.0f, -1.0f,
			1.0f, -1.0f, -1.0f,
			1.0f,  1.0f, -1.0f,
		   -1.0f,  1.0f, -1.0f,

		   -1.0f, -1.0f,  1.0f,
		   -1.0f, -1.0f, -1.0f,
		   -1.0f,  1.0f, -1.0f,
		   -1.0f,  1.0f, -1.0f,
		   -1.0f,  1.0f,  1.0f,
		   -1.0f, -1.0f,  1.0f,

			1.0f, -1.0f, -1.0f,
			1.0f, -1.0f,  1.0f,
			1.0f,  1.0f,  1.0f,
			1.0f,  1.0f,  1.0f,
			1.0f,  1.0f, -1.0f,
			1.0f, -1.0f, -1.0f,

		   -1.0f, -1.0f,  1.0f,
		   -1.0f,  1.0f,  1.0f,
			1.0f,  1.0f,  1.0f,
			1.0f,  1.0f,  1.0f,
			1.0f, -1.0f,  1.0f,
		   -1.0f, -1.0f,  1.0f,

		   -1.0f,  1.0f, -1.0f,
			1.0f,  1.0f, -1.0f,
			1.0f,  1.0f,  1.0f,
			1.0f,  1.0f,  1.0f,
		   -1.0f,  1.0f,  1.0f,
		   -1.0f,  1.0f, -1.0f,

		   -1.0f, -1.0f, -1.0f,
		   -1.0f, -1.0f,  1.0f,
			1.0f, -1.0f, -1.0f,
			1.0f, -1.0f, -1.0f,
		   -1.0f, -1.0f,  1.0f,
			1.0f, -1.0f,  1.0f
};

int main()
{
	// glfw: initialize and configure
   // ------------------------------
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

	// tell GLFW to capture our mouse
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// configure global opengl state
	// -----------------------------
	glEnable(GL_DEPTH_TEST);


	// build and compile shaders
	// -------------------------
	Shader shader("Res/Shaders/vert.vert", "Res/Shaders/frag.frag");
	Shader skyboxshader("Res/Shaders/skybox.vert", "Res/Shaders/skybox.frag");
	Shader exerciseShader("Res/Shaders/exercise1.vert", "Res/Shaders/exercise1.frag");


	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float cubeVertices[] = {
		// positions          // normals
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
		// positions          // texture Coords (note we set these higher than 1 (together with GL_REPEAT as texture wrapping mode). this will cause the floor texture to repeat)
		 5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
		-5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
		-5.0f, -0.5f, -5.0f,  0.0f, 2.0f,

		 5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
		-5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
		 5.0f, -0.5f, -5.0f,  2.0f, 2.0f
	};
	float quadVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
	   // positions   // texCoords
	   -1.0f,  1.0f,  0.0f, 1.0f,
	   -1.0f, -1.0f,  0.0f, 0.0f,
		1.0f, -1.0f,  1.0f, 0.0f,

	   -1.0f,  1.0f,  0.0f, 1.0f,
		1.0f, -1.0f,  1.0f, 0.0f,
		1.0f,  1.0f,  1.0f, 1.0f
	};


	// cube VAO VBO
	unsigned int cubeVAO, cubeVBO;
	glGenVertexArrays(1, &cubeVAO);
	glGenBuffers(1, &cubeVBO);
	glBindVertexArray(cubeVAO);
	glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glBindVertexArray(0);

	// plane VAO VBO
	unsigned int planeVAO, planeVBO;
	glGenVertexArrays(1, &planeVAO);
	glGenBuffers(1, &planeVBO);
	glBindVertexArray(planeVAO);
	glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), &planeVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glBindVertexArray(0);

	// sky VAO VBO
	unsigned int skyVAO, skyVBO;
	glGenVertexArrays(1, &skyVAO);
	glGenBuffers(1, &skyVBO);
	glBindVertexArray(skyVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);


	// load textures
	// -------------
	unsigned int cubeTexture = loadTexture("Res/Images/container.jpg");
	unsigned int floorTexture = loadTexture("Res/Images/wall.jpg");
	unsigned int cubemapTexture = loadCubeTexture(cubemap_paths);

	// shader configuration
	// --------------------
	shader.use();
	shader.setInt("texture1", 0);

	skyboxshader.use();
	skyboxshader.setInt("skybox", 0);

	exerciseShader.use();	
	exerciseShader.setInt("skybox", 4);


	string modelPath("../../models/nanosuit_relfection/nanosuit.obj");
	Model ourModel(modelPath);

	// render loop
	// -----------
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
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		glm::mat4 view = camera.GetViewMatrix();
		glm::mat4 model = glm::mat4(1.0f);

		// Draw Model
		
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0, 0, 0));
		model = glm::scale(model, glm::vec3(0.25f));
		exerciseShader.use();
		exerciseShader.setMatrix4("model", model);
		exerciseShader.setMatrix4("view", view);
		exerciseShader.setMatrix4("projection", projection);
		exerciseShader.setVec3("camPos", camera.Position);
		glActiveTexture(GL_TEXTURE4);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);

		ourModel.Draw(exerciseShader);


		// draw floor
		shader.use();
		view = camera.GetViewMatrix();
		model = glm::mat4(1.0f);
		shader.setMatrix4("projection", projection);
		shader.setMatrix4("view", view);

		// floor
		glBindVertexArray(planeVAO);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, floorTexture);
		shader.setMatrix4("model", glm::mat4(1.0f));
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);

		// skybox的深度已经在shader中设置为1，要把深度测试函数设置为<= 才能显示出来
		glDepthFunc(GL_LEQUAL);

		skyboxshader.use();
		skyboxshader.setMatrix4("view", glm::mat4(glm::mat3(camera.GetViewMatrix())));
		skyboxshader.setMatrix4("projection", projection);
		glBindVertexArray(skyVAO);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &cubeVAO);
	glDeleteVertexArrays(1, &planeVAO);
	glDeleteVertexArrays(1, &skyVAO);
	glDeleteBuffers(1, &cubeVBO);
	glDeleteBuffers(1, &planeVBO);
	glDeleteBuffers(1, &skyVBO);

	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
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

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
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

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.OnScroll(yoffset);
}

// utility function for loading a 2D texture from file
// ---------------------------------------------------
unsigned int loadTexture(char const *path)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}

unsigned int loadCubeTexture(vector<std::string> paths)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	int width, height, nrChannels;
	for (unsigned int i = 0; i < paths.size(); i++)
	{
		unsigned char* data = stbi_load(paths[i].c_str(), &width, &height, &nrChannels, 0);

		GLenum format;
		if (nrChannels == 1)
			format = GL_RED;
		else if (nrChannels == 3)
			format = GL_RGB;
		else if (nrChannels == 4)
			format = GL_RGBA;

		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
		} else
		{
			std::cout << "Cubemap texture failed to load at path: " << paths[i] << std::endl;
			stbi_image_free(data);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	return textureID;
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
		right_mouse_button_down = true;
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
		right_mouse_button_down = false;
}