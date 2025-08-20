// tests/test_orbit.cpp
#include <iostream>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

bool areAlmostEqual(float a, float b, float epsilon = 0.001f) {
    return std::abs(a - b) < epsilon;
}

bool runOrbitTest() {
    float orbitRadius = 10.0f;
    float orbitSpeed = M_PI;
    float time = 1.0f;

    glm::mat4 model = glm::mat4(1.0f);
    float angle = orbitSpeed * time;
    model = glm::rotate(model, angle, glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::translate(model, glm::vec3(orbitRadius, 0.0f, 0.0f));

    glm::vec3 position = glm::vec3(model[3]);
    return areAlmostEqual(position.x, -10.0f)
        && areAlmostEqual(position.y, 0.0f)
        && areAlmostEqual(position.z, 0.0f);
}
