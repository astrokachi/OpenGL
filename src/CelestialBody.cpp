// src/CelestialBody.cpp
// Implementation of the refactored CelestialBody class.

#include "CelestialBody.h"
#include <glm/gtc/type_ptr.hpp>

// Updated constructor to initialize rotationSpeed
CelestialBody::CelestialBody(float radius, float orbitRadius, float orbitSpeed, float rotationSpeed, const std::string& texturePath)
    : sphere(radius, 36, 18),
      texture(texturePath.c_str()),
      orbitRadius(orbitRadius),
      orbitSpeed(orbitSpeed),
      rotationSpeed(rotationSpeed) {}

// New function that separates calculation from drawing
glm::mat4 CelestialBody::getModelMatrix(const glm::mat4& parentTransform, float time) {
    glm::mat4 model = parentTransform;
    // Orbit around the parent
    float orbitAngle = orbitSpeed * time;
    model = glm::rotate(model, orbitAngle, glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::translate(model, glm::vec3(orbitRadius, 0.0f, 0.0f));
    
    // Rotate on its own axis
    float rotationAngle = rotationSpeed * time;
    model = glm::rotate(model, rotationAngle, glm::vec3(0.0f, 1.0f, 0.0f));

    return model;
}

// Simplified draw function
void CelestialBody::draw(Shader& shader) {
    texture.bind();
    sphere.draw();
}
