#include "game_object.h"

GameObject::GameObject(glm::vec2 pos, glm::vec2 size, glm::vec3 col)
    : Position(pos), Size(size), Color(col), Velocity(0.0f), Destroyed(false) {
}