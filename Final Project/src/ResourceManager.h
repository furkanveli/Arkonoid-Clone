// Name: Furkan Veli Ozalp
// Seneca Student ID: 157580200
// Seneca email: fvozalp@myseneca.ca
// Date of completion: 2022-12-13
#pragma once
#include <map>
#include <string>

#include <glad/glad.h>

#include "Texture.h"
#include "Shader.h"

// singleton resource manager class for handling assets throughout the game. It handles loading and clearing of textures and shaders and stores them in static variables.

class ResourceManager
{
public:

    static std::map<std::string, Shader>    Shaders;
    static std::map<std::string, Texture2D> Textures;

    static Shader&    LoadShader(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile, std::string name);

    static Shader&    GetShader(std::string name);

    static Texture2D& LoadTexture(const char* file, bool alpha, std::string name);

    static Texture2D& GetTexture(std::string name);
    static void      Clear();
private:
    ResourceManager() { }
    static Shader    loadShaderFromFile(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile = nullptr);
    static Texture2D loadTextureFromFile(const char* file, bool alpha);
};
