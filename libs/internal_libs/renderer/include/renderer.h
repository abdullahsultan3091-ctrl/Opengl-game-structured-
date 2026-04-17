#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "shader.h"
#include "game_object.h"

class Renderer {
public:
    Renderer(Shader& shader);
    ~Renderer();
    void Draw(GameObject& obj);
private:
    Shader& shader;
    unsigned int vao, vbo;
    void initQuad();
};