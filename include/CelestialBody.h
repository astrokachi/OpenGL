// include/CelestialBody.h
// Represents a celestial body with a texture and independent rotation.

#ifndef CELESTIALBODY_H
#define CELESTIALBODY_H

#include "Sphere.h"
#include "Shader.h"
#include "Texture.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>

class CelestialBody {
public:
    // Constructor now accepts a rotationSpeed
    CelestialBody(float radius, float orbitRadius, float orbitSpeed, float rotationSpeed, const std::string& texturePath);

    // New function to calculate and return the model matrix
    glm::mat4 getModelMatrix(const glm::mat4& parentTransform, float time);

    // Draw function is now simpler
    void draw(Shader& shader);

private:
    Sphere sphere;
    Texture texture;
    float orbitRadius;
    float orbitSpeed;
    float rotationSpeed; // New member variable
};

#endif
