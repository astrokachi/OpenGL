// include/CelestialBody.h
// Represents a single object in the solar system, like a planet or a star.

#ifndef CELESTIALBODY_H
#define CELESTIALBODY_H

#include "Sphere.h"
#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class CelestialBody {
public:
    CelestialBody(float radius, float orbitRadius, float orbitSpeed, glm::vec4 color);
    void draw(Shader& shader, const glm::mat4& parentTransform, float time);

private:
    Sphere sphere;
    glm::vec4 color;
    float orbitRadius;
    float orbitSpeed;
};

#endif
