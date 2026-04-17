#pragma once
#include <glm/glm.hpp>

struct GameObject {
    glm::vec2 Position, Size, Velocity;
    glm::vec3 Color;
    bool Destroyed;

    GameObject(glm::vec2 pos, glm::vec2 size, glm::vec3 col);
};