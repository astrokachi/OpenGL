// include/Texture.h
// A class for loading and using OpenGL textures.

#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include <string>

class Texture {
public:
    unsigned int ID;
    Texture(const char* path);
    void bind(unsigned int slot = 0) const;
};

#endif
