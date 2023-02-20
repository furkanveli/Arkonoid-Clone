// Name: Furkan Veli Ozalp
// Seneca Student ID: 157580200
// Seneca email: fvozalp@myseneca.ca
// Date of completion: 2022-12-13
#pragma once
#include <glad/glad.h>
#include <glm/glm/glm.hpp>

#include "GameObject.h"
#include "texture.h"

// ball class handles the functionality of the sphere
class Ball : public GameObject
{
public:
 
    float   Radius;
    bool    Stuck;

    Ball();
    Ball(glm::vec2 pos, float radius, glm::vec2 velocity, Texture2D tex);
   
    glm::vec2 Move(float dt, unsigned int window_width);
    
    void      Reset(glm::vec2 position, glm::vec2 velocity);
};