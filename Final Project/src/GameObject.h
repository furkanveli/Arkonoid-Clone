// Name: Furkan Veli Ozalp
// Seneca Student ID: 157580200
// Seneca email: fvozalp@myseneca.ca
// Date of completion: 2022-12-13
#pragma once
#include <glad/glad.h>
#include <glm/glm/glm.hpp>

#include "texture.h"
#include "QuadRenderer.h"



class GameObject
{
public:
    glm::vec2   Position, Size, Velocity;
    glm::vec3   Color;
    float       Rotation;
    bool        Destroyed;
    Texture2D   objectTexture;

    GameObject();
    GameObject(glm::vec2 pos, glm::vec2 size, Texture2D tex, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f));

    virtual void Draw(QuadRenderer& renderer);
};