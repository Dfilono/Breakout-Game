#ifndef RESOURCE_MANAGE_H
#define RESOURCE_MANAGER_H

#include <map>
#include<string>

#include<glad/glad.h>

#include "texture.h"
#include "shader.h"

class ResourceManager{
    public:
        // resource storage
        static std::map < std::string, Shader > Shaders;
        static std::map < std::string, Texture2D > Textures;

        // loads a shader program
        static Shader LoadShader(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile, std::string name);

        // retrieves a stored shader
        static Shader GetShader(std::string name);

        // load a texture from file
        static Texture2D LoadTexture(const char *file, bool alpha, std::string name);

        // retrives a stored texture
        static Texture2D GetTexture(std::string name);

        // de-allocated all loaded resources
        static void Clear();

    private:
        // private constructor
        ResourceManager() { }

        // load and generates a shader from file
        static Shader loadShaderFromFile(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile = nullptr);

        // load a single texture from file
        static Texture2D loadTextureFromFile(const char *file, bool alpha);
};

#endif