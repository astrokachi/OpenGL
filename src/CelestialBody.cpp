// src/CelestialBody.cpp
// Implementation of the CelestialBody class.

#include "CelestialBody.h"
#include <glm/gtc/type_ptr.hpp>

CelestialBody::CelestialBody(float radius, float orbitRadius, float orbitSpeed, glm::vec4 color)
    : sphere(radius, 36, 18), color(color), orbitRadius(orbitRadius), orbitSpeed(orbitSpeed) {}

void CelestialBody::draw(Shader& shader, const glm::mat4& parentTransform, float time) {
    // Calculate the object's position in its orbit
    glm::mat4 model = parentTransform;
    float angle = orbitSpeed * time;
    model = glm::rotate(model, angle, glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::translate(model, glm::vec3(orbitRadius, 0.0f, 0.0f));

    // Apply a rotation for the planet's own axis
    model = glm::rotate(model, time * glm::radians(50.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    shader.setMat4("model", glm::value_ptr(model));
    shader.setVec4("objectColor", color.r, color.g, color.b, color.a);
    
    sphere.draw();
}
