
#define STB_IMAGE_IMPLEMENTATION
#include "Shader.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "imgui.h"
#include "stb_image.h"
#include <Camera.h>
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window, float deltaTime);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
unsigned int loadTexture(const char* path);

unsigned int SCR_WIDTH = 800;
unsigned int SCR_HEIGHT = 600;

Camera camera;

float deltaTime = 0.0f; // 当前帧与上一帧的时间差
float lastFrame = 0.0f; // 上一帧的时间

glm::vec3 objectPos(0.0f, 0.0f, 0.0f);

ImVec4 light_ambient = ImVec4(0.2f, 0.2f, 0.2f, 1.0f);
ImVec4 light_diffuse = ImVec4(0.5f, 0.5f, 0.5f, 1.0f);
ImVec4 light_specular = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
float light_position[3] = { -2.2f, -2.0f, -2.0f };
float light_direction[3] = { 1.0f, 1.0f, 1.0f };

ImVec4 material_ambient = ImVec4(0.2f, 0.2f, 0.2f, 1.0f);
ImVec4 material_diffuse = ImVec4(0.5f, 0.5f, 0.5f, 1.0f);
ImVec4 material_specular = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
float material_shininess = 32.0f;

bool right_mouse_button_down = false;
float outer_cone = 12.5f;
float fallOff = 0.5f;

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetScrollCallback(window, scroll_callback);
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
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

    Shader cubeShader("shaders/vertex.vert", "shaders/fragment_multiple_lights.frag");
    Shader lightShader("shaders/vertex.vert", "shaders/fragment_light.frag");

    // set up vertex data and buffers
    // -----------------------
    float vertices[] = {
        // positions          // normals           // texture coords
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,

        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,

        -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,

        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f
    };

    glm::vec3 cubePositions[] = {
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(2.0f, 5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f, 3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f, 2.0f, -2.5f),
        glm::vec3(1.5f, 0.2f, -1.5f),
        glm::vec3(-1.3f, 1.0f, -1.5f)
    };

    // positions of the point lights
    glm::vec3 pointLightPositions[] = {
        glm::vec3(0.7f, 0.2f, 2.0f),
        glm::vec3(2.3f, -3.3f, -4.0f),
        glm::vec3(-4.0f, 2.0f, -12.0f),
        glm::vec3(0.0f, 0.0f, -3.0f)
    };

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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Bind Light Object Vertex Array
    glBindVertexArray(lightVAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glEnable(GL_DEPTH_TEST);

    unsigned int diffuseMap = loadTexture("textures/container2.png");
    unsigned int specularMap = loadTexture("textures/container2_specular.png");

    cubeShader.use();
    cubeShader.setInt("material.diffuse" , 0);
    cubeShader.setInt("material.specular", 1);

    while (!glfwWindowShouldClose(window)) {
        float current_time = (float)glfwGetTime();
        deltaTime = current_time - lastFrame;
        lastFrame = current_time;

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        {
            ImGui::Begin("Control Panel");
            ImGui::Text("Light Settings");
            ImGui::BeginGroup();
            ImGui::ColorEdit3("Light Ambient", (float*)&light_ambient);
            ImGui::ColorEdit3("Light Diffuse", (float*)&light_diffuse);
            ImGui::ColorEdit3("Light Specular", (float*)&light_specular);
            ImGui::SliderFloat3("Light Position", light_position, -8.0f, 8.0f);
            ImGui::SliderFloat3("Light Direction", light_direction, -1.0f, 1.0f);
            ImGui::SliderFloat("Outer Cone", (float*)&outer_cone, 2.0f, 90.0f);
            ImGui::SliderFloat("Fall Off", (float*)&fallOff, 0.0f, 1.0f);
            ImGui::EndGroup();

            ImGui::Text("Material Settings");
            ImGui::BeginGroup();
            ImGui::SliderFloat("Shininess", (float*)&material_shininess, 1.0f, 256.0f);
            ImGui::EndGroup();
            ImGui::End();
        }

        processInput(window, deltaTime);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // 绘制第一个立方体
        cubeShader.use();
        cubeShader.setMatrix4("view", camera.GetViewMatrix());

        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective<float>(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 1000.0f);
        cubeShader.setMatrix4("projection", projection);

        // directional light
        cubeShader.setVec3   ("dirLight.direction", -0.2f, -1.0f, -0.3f);
        cubeShader.setVec3   ("dirLight.ambient", 0.05f, 0.05f, 0.05f);
        cubeShader.setVec3   ("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
        cubeShader.setVec3   ("dirLight.specular", 0.5f, 0.5f, 0.5f);
        // point light 1
        cubeShader.setVec3   ("pointLights[0].position", pointLightPositions[0]);
        cubeShader.setVec3   ("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
        cubeShader.setVec3   ("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
        cubeShader.setVec3   ("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
        cubeShader.setFloat  ("pointLights[0].constant", 1.0f);
        cubeShader.setFloat  ("pointLights[0].linear", 0.09f);
        cubeShader.setFloat  ("pointLights[0].quadratic", 0.032f);
        // point light 2
        cubeShader.setVec3   ("pointLights[1].position", pointLightPositions[1]);
        cubeShader.setVec3   ("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
        cubeShader.setVec3   ("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
        cubeShader.setVec3   ("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
        cubeShader.setFloat  ("pointLights[1].constant", 1.0f);
        cubeShader.setFloat  ("pointLights[1].linear", 0.09f);
        cubeShader.setFloat  ("pointLights[1].quadratic", 0.032f);
        // point light 3
        cubeShader.setVec3   ("pointLights[2].position", pointLightPositions[2]);
        cubeShader.setVec3   ("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
        cubeShader.setVec3   ("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
        cubeShader.setVec3   ("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
        cubeShader.setFloat  ("pointLights[2].constant", 1.0f);
        cubeShader.setFloat  ("pointLights[2].linear", 0.09f);
        cubeShader.setFloat  ("pointLights[2].quadratic", 0.032f);
        // point light 4
        cubeShader.setVec3   ("pointLights[3].position", pointLightPositions[3]);
        cubeShader.setVec3   ("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
        cubeShader.setVec3   ("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
        cubeShader.setVec3   ("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
        cubeShader.setFloat  ("pointLights[3].constant", 1.0f);
        cubeShader.setFloat  ("pointLights[3].linear", 0.09f);
        cubeShader.setFloat  ("pointLights[3].quadratic", 0.032f);
        // spotLight

        cubeShader.setVec3   ("spotlight.ambient", 0.0f, 0.0f, 0.0f);
        cubeShader.setVec3   ("spotlight.diffuse", 1.0f, 1.0f, 1.0f);
        cubeShader.setVec3   ("spotlight.specular", 1.0f, 1.0f, 1.0f);
        cubeShader.setFloat  ("spotlight.constant", 1.0f);
        cubeShader.setFloat  ("spotlight.linear", 0.09f);
        cubeShader.setFloat  ("spotlight.quadratic", 0.032f);
        cubeShader.setVec3   ("spotlight.position", glm::vec3(light_position[0], light_position[1], light_position[2]));
        cubeShader.setVec3   ("spotlight.direction", glm::vec3(light_direction[0], light_direction[1], light_direction[2]));   
        cubeShader.setFloat  ("spotlight.outerCone", glm::cos(glm::radians(outer_cone)));
        cubeShader.setFloat  ("spotlight.fallOff", fallOff);

        cubeShader.setFloat  ("material.shininess", material_shininess);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, diffuseMap);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, specularMap);

        glBindVertexArray(VAO);
        for (unsigned int i = 0; i < sizeof(cubePositions) / sizeof(glm::vec3); i++) {
            float angle = 20.0f * i;
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            model = glm::rotate(model, angle, glm::vec3(1.0f, 0.3f, 0.5f));
            cubeShader.setMatrix4("model", model);

            glm::mat3 normalMatrix = glm::transpose(glm::inverse(model));
            cubeShader.setMatrix3("normalMatrix", normalMatrix);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        // 绘制光源
        glBindVertexArray(lightVAO);
        lightShader.use();
        lightShader.setMatrix4("view", camera.GetViewMatrix());
        lightShader.setMatrix4("projection", projection);

        for(unsigned int i = 0; i< 4; i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, pointLightPositions[i]);
            model = glm::scale(model, glm::vec3(0.2f));
            lightShader.setMatrix4("model", model);

            glm::mat3 normalMatrix = glm::transpose(glm::inverse(model));
            lightShader.setMatrix3("normalMatrix", normalMatrix);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        

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
    if (right_mouse_button_down) {
        camera.OnMouseMove(xpos, ypos);
    } else {
        camera.Initialize();
    }
}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.OnScroll(yoffset);
}

unsigned int loadTexture(const char* path)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data) {
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
    } else {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
        right_mouse_button_down = true;
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
        right_mouse_button_down = false;
}