// Name: Furkan Veli Ozalp
// Seneca Student ID: 157580200
// Seneca email: fvozalp@myseneca.ca
// Date of completion: 2022-12-13
#include "Game.h"
#include "ResourceManager.h"
#include "QuadRenderer.h"
#include "GameObject.h"

// for returning a random number for powerups
bool SpawnChance(unsigned int chance);
bool SpawnChance(unsigned int chance)
{
    // if chance is 20, then 1 in 20 bricks
    unsigned int random = rand() % chance;
    return random == 0;
}


Game::Game(unsigned int width, unsigned int height)
    : Keys(), Width(width), Height(height)
{

}

Game::~Game()
{
    delete Renderer;
    delete Player;
    delete ball;
}

void Game::Init()
{
    // load shaders
    ResourceManager::LoadShader("./Shaders/QuadVertex.vert", "./Shaders/QuadFragment.frag", nullptr, "quadShader");

    ResourceManager::GetShader("quadShader").Use().SetUniform1i("image", 0);
    // initialize the renderer
    Renderer = new QuadRenderer(ResourceManager::GetShader("quadShader"));
    // load textures
    ResourceManager::LoadTexture("./Textures/block.png", false, "block");
    ResourceManager::LoadTexture("./Textures/platform.png", true, "platform");
    ResourceManager::LoadTexture("./Textures/ball.png", true, "ball");
    ResourceManager::LoadTexture("./Textures/block4.png", false, "block4");
    ResourceManager::LoadTexture("./Textures/block5.png", false, "block5");
    // initialize game level
    GameLevel levelOne;
    levelOne.Load("./Levels/level1.txt", Width, Height / 2);
    Levels.push_back(levelOne);
    CurrentLevel = 0;

    // player in the bottom middle
    glm::vec2 playerPos = glm::vec2(Width / 2.0f - PLAYER_SIZE.x / 2.0f, Height - PLAYER_SIZE.y);
    Player = new GameObject(playerPos, PLAYER_SIZE, ResourceManager::GetTexture("platform"));
    // ball in the bottom middle
    glm::vec2 ballPosition = playerPos + glm::vec2(PLAYER_SIZE.x / 2.0f - BALL_RADIUS, -BALL_RADIUS * 2.0f);

    ball = new Ball(ballPosition, BALL_RADIUS, BALL_VELOCITY, ResourceManager::GetTexture("ball"));
}

void Game::Update(float dt)
{
    ball->Move(dt, Width);

    ApplyCollisions();

    UpdatePowerUp(dt);

    if (ball->Position.y >= Height) // if ball reached the bottom edge reset the level
    {
        ResetLevel();
        ResetPlayer();
    }
}

void Game::ProcessInput(float dt)
{
    
        // if ball is stuck to the platform move the ball with the platform, don't if otherwise
        float velocity = PLAYER_VELOCITY * dt;
        // move platform
        if (Keys[GLFW_KEY_A])
        {
            if (Player->Position.x >= 0.0f)
            {
                Player->Position.x -= velocity;
                if (ball->Stuck)
                    ball->Position.x -= velocity;
            }
        }
        if (Keys[GLFW_KEY_D])
        {
            if (Player->Position.x <= Width - Player->Size.x)
            {
                Player->Position.x += velocity;
                if (ball->Stuck)
                    ball->Position.x += velocity;
            }
        }
        if (Keys[GLFW_KEY_SPACE])
            ball->Stuck = false;
   
}

void Game::Render()
{
        // draw level
        Levels[CurrentLevel].Draw(*Renderer);
        // draw player
        Player->Draw(*Renderer);

        for (PowerUp& powerUp : PowerUps)
            if (!powerUp.Destroyed)
                powerUp.Draw(*Renderer);

        // draw the ball 
        ball->Draw(*Renderer);
}

bool Game::CheckCollision(GameObject& one, GameObject& two) // box to box collision
{
    // check if there's collision on x axis
    bool collisionX = one.Position.x + one.Size.x >= two.Position.x &&
        two.Position.x + two.Size.x >= one.Position.x;
    //  check if there's collision on y axis
    bool collisionY = one.Position.y + one.Size.y >= two.Position.y &&
        two.Position.y + two.Size.y >= one.Position.y;
    // if there's collision on both axes then two object have collided
    return collisionX && collisionY;
}

Collision Game::CheckCollision(Ball& circle, GameObject& box) // circle to box collision
{
    // get the circle collider's center point
    glm::vec2 center(circle.Position + circle.Radius);
    // calculate quad's half extends(height or width /2) and center
    glm::vec2 quadHalfExtent(box.Size.x / 2.0f, box.Size.y / 2.0f);
    glm::vec2 quadCenter(
        box.Position.x + quadHalfExtent.x,
        box.Position.y + quadHalfExtent.y
    );
    // get the difference vector between the circle's center and quad's center
    glm::vec2 difference = center - quadCenter;
    glm::vec2 clampedResult = glm::clamp(difference, -quadHalfExtent, quadHalfExtent);
    // add clamped value to the quad's center to get the closest point on the quad to the circle
    glm::vec2 closest = quadCenter + clampedResult;
    // check if the difference is smaller than radius. If it is, that means we have a collision
    difference = closest - center;
    if (glm::length(difference) < circle.Radius) 
        return std::make_tuple(true, VectorDirection(difference), difference);
    else
        return std::make_tuple(false, UP, glm::vec2(0.0f, 0.0f));
}

void Game::ApplyCollisions()
{
    for (GameObject& box : Levels[CurrentLevel].Bricks)
    {
        if (!box.Destroyed)
        {
            Collision collision = CheckCollision(*ball, box);
            if (std::get<0>(collision)) // if collision is true
            {
                // destroy block and spawn power up 
                    box.Destroyed = true;
                    SpawnPowerUp(box);
                // collision resolution
                Direction direction = std::get<1>(collision);
                glm::vec2 differenceVector = std::get<2>(collision);
                if (direction == LEFT || direction == RIGHT) // horizontal collision
                {
                    ball->Velocity.x = -ball->Velocity.x; // reverse velocity in the x axis
                    // relocate
                    float penetration = ball->Radius - std::abs(differenceVector.x);
                    if (direction == LEFT)
                        ball->Position.x += penetration; // move the ball to the right
                    else
                        ball->Position.x -= penetration; // move the ball to the left;
                }
                else // vertical collision
                {
                    ball->Velocity.y = -ball->Velocity.y; // reverse velocity in y axis
                    // relocate
                    float penetration = ball->Radius - std::abs(differenceVector.y);
                    if (direction == UP)
                        ball->Position.y -= penetration; // move ball back up
                    else
                        ball->Position.y += penetration; // move ball back down
                }
            }
        }
    }

    // if there is a power up, activate it
    for (PowerUp& p : PowerUps)
    {
        if (!p.Destroyed)
        {
            // if powerup passed the bottom edge then destroy it
            if (p.Position.y >= Height)
                p.Destroyed = true;

            if (CheckCollision(*Player, p))
            {	// if powerup collided with player then activate it
                ActivatePowerUp(p);
                p.Destroyed = true;
            }
        }
    }



    Collision result = CheckCollision(*ball, *Player);
    if (!ball->Stuck && std::get<0>(result))
    {
        // check where the ball hit the platform
        float centerBoard = Player->Position.x + Player->Size.x / 2.0f;
        float distance = (ball->Position.x + ball->Radius) - centerBoard;
        float percentage = distance / (Player->Size.x / 2.0f);
        // and change velocity accordingly
        float strength = 2.0f;
        glm::vec2 oldVelocity = ball->Velocity;
        ball->Velocity.x = BALL_VELOCITY.x * percentage * strength;
        ball->Velocity.y = -1.0f * abs(ball->Velocity.y);
        ball->Velocity = glm::normalize(ball->Velocity) * glm::length(oldVelocity);
    }

}


Direction Game::VectorDirection(glm::vec2 target)
{
    glm::vec2 compass[] = {
        glm::vec2(0.0f, 1.0f),	// up
        glm::vec2(1.0f, 0.0f),	// right
        glm::vec2(0.0f, -1.0f),	// down
        glm::vec2(-1.0f, 0.0f)	// left
    };
    float max = 0.0f;
    unsigned int closestMatch = -1;
    for (unsigned int i = 0; i < 4; i++)
    {
        float dot = glm::dot(glm::normalize(target), compass[i]);
        if (dot > max)
        {
            max = dot;
            closestMatch = i;
        }
    }
    return (Direction)closestMatch; // cast the result to the direction enum declared in the game.h file
}


void Game::ResetLevel()
{
        Levels[0].Load("./Levels/level1.txt", Width, Height / 2);
}

void Game::ResetPlayer()
{
    // reset the platform
    Player->Size = PLAYER_SIZE;
    Player->Position = glm::vec2(Width / 2.0f - PLAYER_SIZE.x / 2.0f, Height - PLAYER_SIZE.y);
    ball->Reset(Player->Position + glm::vec2(PLAYER_SIZE.x / 2.0f - BALL_RADIUS, -(BALL_RADIUS * 2.0f)), BALL_VELOCITY);
}


void Game::SpawnPowerUp(GameObject& block)
{ 
    if (SpawnChance(13))
        PowerUps.push_back(
            PowerUp(glm::vec3(1.0f), block.Position, ResourceManager::GetTexture("block4")));
}

void Game::ActivatePowerUp(PowerUp& powerUp)
{
        Player->Size.x *= 2;
}

void Game::UpdatePowerUp(float dt)
{
    // move the powerup
    for (PowerUp& powerUp : this->PowerUps)
    {
        powerUp.Position += powerUp.Velocity * dt;
    }
}