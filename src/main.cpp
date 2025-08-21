// src/main.cpp
// Now with camera zoom and a moon orbiting the Earth!

#include <iostream>
#include <vector>
#include <memory> // For std::make_unique
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Camera.h"
#include "CelestialBody.h"

// Function prototypes
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset); // New callback for scrolling
void processInput(GLFWwindow *window);

// Screen settings, camera, timing remain the same
const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 720;
Camera camera(glm::vec3(0.0f, 4.0f, 12.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;
float deltaTime = 0.0f;
float lastFrame = 0.0f;

int main() {
    // GLFW and GLAD initialization
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Solar System", NULL, NULL);
    if (window == NULL) { /* ... error handling ... */ return -1; }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback); // Register the new scroll callback
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) { /* ... error handling ... */ return -1; }
    glEnable(GL_DEPTH_TEST);

    // Build and compile our shader program
    Shader ourShader("shaders/basic.vert", "shaders/basic.frag");

    // Create celestial bodies: (radius, orbitRadius, orbitSpeed, rotationSpeed, texturePath)
    auto sun = std::make_unique<CelestialBody>(1.5f, 0.0f, 0.0f, 0.2f, "textures/sun.jpg");
    auto earth = std::make_unique<CelestialBody>(0.4f, 6.0f, 0.4f, 1.0f, "textures/earth.jpg");
    auto mars = std::make_unique<CelestialBody>(0.3f, 9.0f, 0.3f, 0.8f, "textures/mars.jpg");
    auto moon = std::make_unique<CelestialBody>(0.1f, 1.0f, 2.0f, 0.5f, "textures/moon.jpg"); // You'll need a moon.jpg for this

    ourShader.use();
    ourShader.setInt("texture1", 0);

    // Render loop
    while (!glfwWindowShouldClose(window)) {
        // Time logic
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Input
        processInput(window);

        // Render
        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ourShader.use();

        // View and projection matrices
        // Use camera.Zoom for the perspective field of view
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        ourShader.setMat4("projection", glm::value_ptr(projection));
        ourShader.setMat4("view", glm::value_ptr(view));

        // Hierarchical transformations
        glm::mat4 origin = glm::mat4(1.0f);

        glm::mat4 sunMatrix = sun->getModelMatrix(origin, currentFrame);
        ourShader.setMat4("model", glm::value_ptr(sunMatrix));
        sun->draw(ourShader);

        glm::mat4 earthMatrix = earth->getModelMatrix(sunMatrix, currentFrame);
        ourShader.setMat4("model", glm::value_ptr(earthMatrix));
        earth->draw(ourShader);
        
        glm::mat4 marsMatrix = mars->getModelMatrix(sunMatrix, currentFrame);
        ourShader.setMat4("model", glm::value_ptr(marsMatrix));
        mars->draw(ourShader);

        glm::mat4 moonMatrix = moon->getModelMatrix(earthMatrix, currentFrame);
        ourShader.setMat4("model", glm::value_ptr(moonMatrix));
        moon->draw(ourShader);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

// Process input function remains the same
void processInput(GLFWwindow *window) { if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, true); if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) camera.ProcessKeyboard(FORWARD, deltaTime); if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) camera.ProcessKeyboard(BACKWARD, deltaTime); if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) camera.ProcessKeyboard(LEFT, deltaTime); if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) camera.ProcessKeyboard(RIGHT, deltaTime); }

// Framebuffer size callback remains the same
void framebuffer_size_callback(GLFWwindow* window, int width, int height) { glViewport(0, 0, width, height); }

// Mouse callback for looking around remains the same
void mouse_callback(GLFWwindow* window, double xpos, double ypos) { if (firstMouse) { lastX = xpos; lastY = ypos; firstMouse = false; } float xoffset = xpos - lastX; float yoffset = lastY - ypos; lastX = xpos; lastY = ypos; camera.ProcessMouseMovement(xoffset, yoffset); }

// New callback function for mouse scroll
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    camera.ProcessMouseScroll(yoffset);
}
