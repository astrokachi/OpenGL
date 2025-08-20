// include/Camera.h
// A basic camera class for navigating the 3D scene.

#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f));

    glm::mat4 GetViewMatrix();
};

#endif
