// Name: Furkan Veli Ozalp
// Seneca Student ID: 157580200
// Seneca email: fvozalp@myseneca.ca
// Date of completion: 2022-12-13
#pragma once
#include <string>

#include <glad/glad.h>
#include <glm/glm/glm.hpp>

#include "GameObject.h"


class PowerUp : public GameObject
{
public:

    PowerUp(glm::vec3 color, glm::vec2 position, Texture2D texture)
        : GameObject(position, glm::vec2(45.0f, 15.0f) , texture, color, glm::vec2(0.0f, 200.0f)) { }
};
