// Name: Furkan Veli Ozalp
// Seneca Student ID: 157580200
// Seneca email: fvozalp@myseneca.ca
// Date of completion: 2022-12-13
#pragma once
#include <glad/glad.h>


class Texture2D
{
public:
    unsigned int ID;
    unsigned int Image_Format;
    unsigned int Internal_Format;
    unsigned int Width, Height; 

    Texture2D();
    void Generate(unsigned int width, unsigned int height, unsigned char* data);
    void Bind() const;
};