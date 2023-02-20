// Name: Furkan Veli Ozalp
// Seneca Student ID: 157580200
// Seneca email: fvozalp@myseneca.ca
// Date of completion: 2022-12-13
#pragma once
#include <glad/glad.h>
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>

#include "Texture.h"
#include "Shader.h"


class QuadRenderer
{
public:

    QuadRenderer(Shader& s);

    ~QuadRenderer();

    void DrawSprite(Texture2D& texture, glm::vec2 position, glm::vec2 size = glm::vec2(10.0f, 10.0f), float rotation = 0.0f, glm::vec3 color = glm::vec3(1.0f));
private:

    Shader       shader;
    unsigned int quadVAO;

    void initRenderData();
};
