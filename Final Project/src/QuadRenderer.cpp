// Name: Furkan Veli Ozalp
// Seneca Student ID: 157580200
// Seneca email: fvozalp@myseneca.ca
// Date of completion: 2022-12-13
#include "QuadRenderer.h"


QuadRenderer::QuadRenderer(Shader& s)
{
    shader = s;
    initRenderData();
}

QuadRenderer::~QuadRenderer()
{
    glDeleteVertexArrays(1, &quadVAO);
}

void QuadRenderer::DrawSprite(Texture2D& texture, glm::vec2 position, glm::vec2 size, float rotation, glm::vec3 color)
{

    // projection view and model
    glm::mat4 projection = glm::ortho(0.0f, 1024.0f, 768.0f, 0.0f, -1.0f, 1.0f);
    glm::mat4 view = glm::mat4(1.0);
    shader.Use();
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position, 0.0f));  

    // translate the rotation center to the quad center before rotating
    model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f)); 
    model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f)); 
    model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f)); 

    // scale
    model = glm::scale(model, glm::vec3(size, 1.0f)); 

    shader.SetUniformMat4("model", model);
    shader.SetUniform3f("quadColor", color);
    shader.SetUniformMat4("projection", projection);
    shader.SetUniformMat4("view", view);

    // set the texture
    glActiveTexture(GL_TEXTURE0);
    texture.Bind();

    // issue draw command
    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void QuadRenderer::initRenderData()
{
   // init vao and vbo for quad rendering
    unsigned int VBO;
    float vertices[] = {
        // positions     // texture coordinates
        1.0f, 0.0f,      1.0f, 0.0f,
        0.0f, 1.0f,      0.0f, 1.0f,
        0.0f, 0.0f,      0.0f, 0.0f,
                         
        0.0f, 1.0f,      0.0f, 1.0f,
        1.0f, 1.0f,      1.0f, 1.0f,
        1.0f, 0.0f,      1.0f, 0.0f
    };

    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(quadVAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}