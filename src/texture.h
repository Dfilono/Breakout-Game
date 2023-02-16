#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>

// Store and configure texture in OpenGL
class Texture2D{
    public:
        // hold the ID of the texture object
        unsigned int ID;

        // texture image dimensions
        unsigned int Width, Height;

        // texture format
        unsigned int Internal_Format;
        unsigned int Image_Format;

        // texture config
        unsigned int Wrap_S;
        unsigned int Wrap_T;
        unsigned int Filter_Min;
        unsigned int Filter_Max;

        // constructor
        Texture2D();

        // generates texture from image data
        void Generate(unsigned int width, unsigned int height, unsigned char* data);

        // binds the texture as the current active GL_TEXTURE_2D object
        void Bind() const;
};

#endif