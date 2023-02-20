// Name: Furkan Veli Ozalp
// Seneca Student ID: 157580200
// Seneca email: fvozalp@myseneca.ca
// Date of completion: 2022-12-13
#include <vector>

#include <glad/glad.h>
#include <glm/glm/glm.hpp>
#include <fstream>
#include <sstream>
#include "GameObject.h"
#include "QuadRenderer.h"
#include "ResourceManager.h"



class GameLevel
{
public:

    std::vector<GameObject> Bricks;
    GameLevel() { }
    // loading levels from a text file
    void Load(const char* file, unsigned int levelWidth, unsigned int levelHeight);
    // drawing the level
    void Draw(QuadRenderer& renderer);
    // to check if the level is completed
    bool IsCompleted();
private:
    
    void init(std::vector<std::vector<unsigned int>> tileData, unsigned int levelWidth, unsigned int levelHeight);
};
