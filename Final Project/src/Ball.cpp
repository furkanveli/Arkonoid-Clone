// Name: Furkan Veli Ozalp
// Seneca Student ID: 157580200
// Seneca email: fvozalp@myseneca.ca
// Date of completion: 2022-12-13
#include "Ball.h"


Ball::Ball()
    : GameObject(), Radius(12.5f), Stuck(true) { }

Ball::Ball(glm::vec2 pos, float radius, glm::vec2 velocity, Texture2D tex)
    : GameObject(pos, glm::vec2(radius * 2.0f, radius * 2.0f), tex, glm::vec3(1.0f), velocity), Radius(radius), Stuck(true) { }

glm::vec2 Ball::Move(float dt, unsigned int window_width)
{
    // if the ball is not stuck to the platform
    if (!Stuck)
    {
        // move the ball
        Position += Velocity * dt;
        // check if outside bounds and reverse velocity if it its
        if (Position.x <= 0.0f)
        {
            Velocity.x = -Velocity.x;
            Position.x = 0.0f;
        }
        else if (Position.x + Size.x >= window_width)
        {
            Velocity.x = -Velocity.x;
            Position.x = window_width - Size.x;
        }
        if (Position.y <= 0.0f)
        {
            Velocity.y = -Velocity.y;
            Position.y = 0.0f;
        }
    }
    return Position;
}

// reset the ball as stuck to the platform
void Ball::Reset(glm::vec2 position, glm::vec2 velocity)
{
    Position = position;
    Velocity = velocity;
    Stuck = true;
}


