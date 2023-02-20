// Name: Furkan Veli Ozalp
// Seneca Student ID: 157580200
// Seneca email: fvozalp@myseneca.ca
// Date of completion: 2022-12-13
#pragma once
#include <string>
#include <iostream>
#include <glad/glad.h>
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/type_ptr.hpp>



class Shader
{
public:
    unsigned int objectID;
    Shader() = default;
    Shader& Use();
    void Compile(const char* vertexSource, const char* fragmentSource, const char* geometrySource = nullptr); 

    void    SetUniform1f(const char* name, float value, bool useShader = false);
    void    SetUniform1i(const char* name, int value, bool useShader = false);
    void    SetUniform2f(const char* name, float x, float y, bool useShader = false);
    void    SetUniform2f(const char* name, const glm::vec2& value, bool useShader = false);
    void    SetUniform3f(const char* name, float x, float y, float z, bool useShader = false);
    void    SetUniform3f(const char* name, const glm::vec3& value, bool useShader = false);
    void    SetUniform4f(const char* name, float x, float y, float z, float w, bool useShader = false);
    void    SetUniform4f(const char* name, const glm::vec4& value, bool useShader = false);
    void    SetUniformMat4(const char* name, const glm::mat4& matrix, bool useShader = false);
private:
    
    void    checkCompileErrors(unsigned int object, std::string type);
};
