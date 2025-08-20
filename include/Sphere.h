// include/Sphere.h
// A class to generate and render a sphere mesh.

#ifndef SPHERE_H
#define SPHERE_H

#include <vector>
#include <glad/glad.h>

class Sphere {
public:
    Sphere(float radius, int sectorCount, int stackCount);
    ~Sphere();
    void draw();

private:
    unsigned int VAO, VBO, EBO;
    int indexCount;
    void generateData(float radius, int sectorCount, int stackCount);
};

#endif
