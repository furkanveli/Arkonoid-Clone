// Name: Furkan Veli Ozalp
// Seneca Student ID: 157580200
// Seneca email: fvozalp@myseneca.ca
// Date of completion: 2022-12-13
#include "GameLevel.h"




void GameLevel::Load(const char* file, unsigned int levelWidth, unsigned int levelHeight)
{
   // clear old level data before loading the level
    Bricks.clear();

    unsigned int number;
    GameLevel level;
    std::string line;
    std::ifstream fstream(file);
    std::vector<std::vector<unsigned int>> tileData;
    if (fstream)
    {
        while (std::getline(fstream, line)) // read each line
        {
            std::istringstream sstream(line);
            std::vector<unsigned int> row;
            while (sstream >> number) // read each word 
                row.push_back(number);
            tileData.push_back(row);
        }
        if (tileData.size() > 0)
            init(tileData, levelWidth, levelHeight);
    }
}

void GameLevel::Draw(QuadRenderer& renderer)
{
    for (GameObject& brick : Bricks)
        if (!brick.Destroyed)
            brick.Draw(renderer);
}

bool GameLevel::IsCompleted()
{
    for (GameObject& brick : Bricks)
        if (!brick.Destroyed)
            return false;
    return true;
}

void GameLevel::init(std::vector<std::vector<unsigned int>> tileData, unsigned int levelWidth, unsigned int levelHeight)
{
    unsigned int height = tileData.size();
    unsigned int width = tileData[0].size(); 
    float unit_width = levelWidth / static_cast<float>(width), unit_height = levelHeight / height;

    /*
    0: empty space
    >1: destroyable brick, increasing number determines the color
    */


    for (unsigned int y = 0; y < height; ++y)
    {
        for (unsigned int x = 0; x < width; ++x)
        {
            if (tileData[y][x] > 1)	// if not empty
            {
                glm::vec3 color = glm::vec3(1.0f); 
                Texture2D tex;
                if (tileData[y][x] == 2) {
                    color = glm::vec3(0.4f, 0.3f, 0.5f);
                    tex = ResourceManager::GetTexture("block");
                }
                else if (tileData[y][x] == 3)
                {
                    color = glm::vec3(0.8f, 0.8f, 0.8f);
                    tex = ResourceManager::GetTexture("block5");
                }
                else if (tileData[y][x] == 4) 
                {
                    color = glm::vec3(0.4f, 0.4f, 0.4f);
                    tex = ResourceManager::GetTexture("block5");
                }
                else // 5
                {
                    color = glm::vec3(1.0f, 0.7f, 0.1f);
                    tex = ResourceManager::GetTexture("block4");
                }

                glm::vec2 pos(unit_width * x, unit_height * y);
                glm::vec2 size(unit_width, unit_height);
                Bricks.push_back(GameObject(pos, size, tex, color));
            }
        }
    }
}