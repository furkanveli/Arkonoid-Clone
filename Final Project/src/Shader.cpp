// Name: Furkan Veli Ozalp
// Seneca Student ID: 157580200
// Seneca email: fvozalp@myseneca.ca
// Date of completion: 2022-12-13
#include "Shader.h"

Shader& Shader::Use()
{
	glUseProgram(objectID);
	return *this;
}

void Shader::Compile(const char* vertexSource, const char* fragmentSource, const char* geometrySource)
{
    unsigned int sVertex, sFragment, gShader;

    sVertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(sVertex, 1, &vertexSource, NULL);
    glCompileShader(sVertex);
    checkCompileErrors(sVertex, "VERTEX");

    sFragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(sFragment, 1, &fragmentSource, NULL);
    glCompileShader(sFragment);
    checkCompileErrors(sFragment, "FRAGMENT");
    // if geometry shader source code is given, also compile geometry shader
    if (geometrySource != nullptr)
    {
        gShader = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(gShader, 1, &geometrySource, NULL);
        glCompileShader(gShader);
        checkCompileErrors(gShader, "GEOMETRY");
    }

    objectID = glCreateProgram();
    glAttachShader(objectID, sVertex);
    glAttachShader(objectID, sFragment);
    if (geometrySource != nullptr)
        glAttachShader(objectID, gShader);
    glLinkProgram(objectID);
    checkCompileErrors(objectID, "PROGRAM");

    glDeleteShader(sVertex);
    glDeleteShader(sFragment);
    if (geometrySource != nullptr)
        glDeleteShader(gShader);
}

void Shader::SetUniform1f(const char* name, float value, bool useShader)
{
    if (useShader)
        Use();
    glUniform1f(glGetUniformLocation(objectID, name), value);
}

void Shader::SetUniform1i(const char* name, int value, bool useShader)
{
    if (useShader)
        Use();
    glUniform1i(glGetUniformLocation(objectID, name), value);
}

void Shader::SetUniform2f(const char* name, float x, float y, bool useShader)
{
    if (useShader)
       Use();
    glUniform2f(glGetUniformLocation(objectID, name), x, y);
}

void Shader::SetUniform2f(const char* name, const glm::vec2& value, bool useShader)
{
    if (useShader)
        Use();
    glUniform2f(glGetUniformLocation(objectID, name), value.x, value.y);
}

void Shader::SetUniform3f(const char* name, float x, float y, float z, bool useShader)
{
    if (useShader)
        Use();
    glUniform3f(glGetUniformLocation(objectID, name), x, y, z);
}

void Shader::SetUniform3f(const char* name, const glm::vec3& value, bool useShader)
{
    if (useShader)
       Use();
    glUniform3f(glGetUniformLocation(objectID, name), value.x, value.y, value.z);
}

void Shader::SetUniform4f(const char* name, float x, float y, float z, float w, bool useShader)
{
    if (useShader)
        Use();
    glUniform4f(glGetUniformLocation(objectID, name), x, y, z, w);
}

void Shader::SetUniform4f(const char* name, const glm::vec4& value, bool useShader)
{
    if (useShader)
       Use();
    glUniform4f(glGetUniformLocation(objectID, name), value.x, value.y, value.z, value.w);
}

void Shader::SetUniformMat4(const char* name, const glm::mat4& matrix, bool useShader)
{
    if (useShader)
        Use();
    glUniformMatrix4fv(glGetUniformLocation(objectID, name), 1, false, glm::value_ptr(matrix));
}

void Shader::checkCompileErrors(unsigned int object, std::string type)
{
    int success;
    char infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(object, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(object, 1024, NULL, infoLog);
            std::cout << type << " Shader failed to compile!" << "\n"
                << infoLog << "\n -- --------------------------------------------------- -- "
                << std::endl;
        }
    }
    else
    {
        glGetProgramiv(object, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(object, 1024, NULL, infoLog);
            std::cout << " Shader linking error!" << "\n"
                << infoLog << "\n -- --------------------------------------------------- -- "
                << std::endl;
        }
    }
}
