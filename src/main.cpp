// src/main.cpp
// The main application file, now updated to simulate the complete solar system.

#include <iostream>
#include <vector>
#include <memory>
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
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);

// Screen settings
const unsigned int SCR_WIDTH = 1920;
const unsigned int SCR_HEIGHT = 1080;

// Camera
Camera camera(glm::vec3(0.0f, 8.0f, 25.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// Timing
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
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Solar System Simulation", NULL, NULL);
    if (window == NULL) { /* ... error handling ... */ return -1; }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) { /* ... error handling ... */ return -1; }
    glEnable(GL_DEPTH_TEST);

    // Build and compile our shader program
    Shader ourShader("shaders/basic.vert", "shaders/basic.frag");

    // --- Create all celestial bodies ---
    // Parameters: (radius, orbitRadius, orbitSpeed, rotationSpeed, texturePath)
    auto sun = std::make_unique<CelestialBody>(3.5f, 0.0f, 0.0f, 0.05f, "textures/sun.jpg");
    
    // Inner Planets
    auto mercury = std::make_unique<CelestialBody>(0.5f, 5.0f, 0.8f, 0.5f, "textures/mercury.jpg");
    auto venus = std::make_unique<CelestialBody>(0.8f, 8.0f, 0.65f, 0.4f, "textures/venus.jpg");
    auto earth = std::make_unique<CelestialBody>(1.0f, 11.5f, 0.5f, 1.0f, "textures/earth.jpg");
    auto moon = std::make_unique<CelestialBody>(0.27f, 1.5f, 2.0f, 0.5f, "textures/moon.jpg");
    auto mars = std::make_unique<CelestialBody>(0.7f, 15.0f, 0.4f, 0.8f, "textures/mars.jpg");

    // Outer Planets
    auto jupiter = std::make_unique<CelestialBody>(2.0f, 20.0f, 0.25f, 2.0f, "textures/jupiter.jpg");
    auto saturn = std::make_unique<CelestialBody>(1.8f, 26.0f, 0.2f, 1.8f, "textures/saturn.jpg");
    auto uranus = std::make_unique<CelestialBody>(1.4f, 31.0f, 0.15f, 1.2f, "textures/uranus.jpg");
    auto neptune = std::make_unique<CelestialBody>(1.3f, 35.0f, 0.1f, 1.0f, "textures/neptune.jpg");

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
        glClearColor(0.01f, 0.01f, 0.01f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ourShader.use();

        // View and projection matrices
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 200.0f);
        glm::mat4 view = camera.GetViewMatrix();
        ourShader.setMat4("projection", glm::value_ptr(projection));
        ourShader.setMat4("view", glm::value_ptr(view));

        // --- Render all bodies ---
        glm::mat4 origin = glm::mat4(1.0f);

        // Sun
        glm::mat4 sunMatrix = sun->getModelMatrix(origin, currentFrame);
        ourShader.setMat4("model", glm::value_ptr(sunMatrix));
        sun->draw(ourShader);

        // Planets orbiting the Sun
        glm::mat4 mercuryMatrix = mercury->getModelMatrix(sunMatrix, currentFrame);
        ourShader.setMat4("model", glm::value_ptr(mercuryMatrix));
        mercury->draw(ourShader);

        glm::mat4 venusMatrix = venus->getModelMatrix(sunMatrix, currentFrame);
        ourShader.setMat4("model", glm::value_ptr(venusMatrix));
        venus->draw(ourShader);

        glm::mat4 earthMatrix = earth->getModelMatrix(sunMatrix, currentFrame);
        ourShader.setMat4("model", glm::value_ptr(earthMatrix));
        earth->draw(ourShader);
        
        glm::mat4 marsMatrix = mars->getModelMatrix(sunMatrix, currentFrame);
        ourShader.setMat4("model", glm::value_ptr(marsMatrix));
        mars->draw(ourShader);

        glm::mat4 jupiterMatrix = jupiter->getModelMatrix(sunMatrix, currentFrame);
        ourShader.setMat4("model", glm::value_ptr(jupiterMatrix));
        jupiter->draw(ourShader);

        glm::mat4 saturnMatrix = saturn->getModelMatrix(sunMatrix, currentFrame);
        ourShader.setMat4("model", glm::value_ptr(saturnMatrix));
        saturn->draw(ourShader);

        glm::mat4 uranusMatrix = uranus->getModelMatrix(sunMatrix, currentFrame);
        ourShader.setMat4("model", glm::value_ptr(uranusMatrix));
        uranus->draw(ourShader);

        glm::mat4 neptuneMatrix = neptune->getModelMatrix(sunMatrix, currentFrame);
        ourShader.setMat4("model", glm::value_ptr(neptuneMatrix));
        neptune->draw(ourShader);

        // Moon orbiting the Earth
        glm::mat4 moonMatrix = moon->getModelMatrix(earthMatrix, currentFrame);
        ourShader.setMat4("model", glm::value_ptr(moonMatrix));
        moon->draw(ourShader);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

// Helper functions (processInput, callbacks) remain the same
void processInput(GLFWwindow *window) { if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, true); if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) camera.ProcessKeyboard(FORWARD, deltaTime); if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) camera.ProcessKeyboard(BACKWARD, deltaTime); if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) camera.ProcessKeyboard(LEFT, deltaTime); if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) camera.ProcessKeyboard(RIGHT, deltaTime); }
void framebuffer_size_callback(GLFWwindow* window, int width, int height) { glViewport(0, 0, width, height); }
void mouse_callback(GLFWwindow* window, double xpos, double ypos) { if (firstMouse) { lastX = xpos; lastY = ypos; firstMouse = false; } float xoffset = xpos - lastX; float yoffset = lastY - ypos; lastX = xpos; lastY = ypos; camera.ProcessMouseMovement(xoffset, yoffset); }
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) { camera.ProcessMouseScroll(yoffset); }
