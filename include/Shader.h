// include/Shader.h
// A class for loading, compiling, and managing GLSL shaders.

#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {
public:
    // The program ID
    unsigned int ID;

    // Constructor reads and builds the shader
    Shader(const char* vertexPath, const char* fragmentPath);

    // Use/activate the shader
    void use();

    // Utility uniform functions
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setMat4(const std::string &name, const float* value) const;
    void setVec4(const std::string &name, float v1, float v2, float v3, float v4) const;
};

#endif
