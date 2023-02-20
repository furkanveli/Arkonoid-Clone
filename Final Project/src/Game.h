// Name: Furkan Veli Ozalp
// Seneca Student ID: 157580200
// Seneca email: fvozalp@myseneca.ca
// Date of completion: 2022-12-13
#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "GameLevel.h"
#include "Ball.h"
#include "PowerUp.h"
#include <tuple>


enum Direction {
    UP,
    RIGHT,
    DOWN,
    LEFT
};


// typedefing collision data with an std::tuple
typedef std::tuple<bool, Direction, glm::vec2> Collision; // <did collision happen?, collision direction?, difference vector center - closest point>

const glm::vec2 BALL_VELOCITY(150.0f, -450.0f);
const float PLAYER_VELOCITY(560.0f);

const float BALL_RADIUS = 12.5f;
const glm::vec2 PLAYER_SIZE(100.0f, 25.0f);


class Game
{
public:
    // game state and input
    
    bool                    Keys[1024];
    unsigned int            Width, Height;

    // level
    std::vector<GameLevel>  Levels;
    unsigned int            CurrentLevel;

    // game objects 
    QuadRenderer* Renderer;
    GameObject* Player;
    Ball* ball;

    // power ups
    std::vector<PowerUp> PowerUps;
    void SpawnPowerUp(GameObject& block);
    void UpdatePowerUp(float dt);
    void ActivatePowerUp(PowerUp& powerUp);



    Game(unsigned int width, unsigned int height);
    ~Game();
 
    void Init();
  
    // game loop
    void ProcessInput(float dt);
    void Update(float dt);
    void Render();

    // Collision detection
    Collision CheckCollision(Ball& circle, GameObject& box); // check collision between a circle and a box
    bool CheckCollision(GameObject& one, GameObject& two); // check collision between two boxes
    void ApplyCollisions();
    Direction VectorDirection(glm::vec2 target);


    // reset
    void ResetLevel();
    void ResetPlayer();
};