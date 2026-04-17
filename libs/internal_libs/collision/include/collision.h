#pragma once
#include <tuple>
#include <glm/glm.hpp>
#include "game_object.h"

enum Direction { UP, RIGHT, DOWN, LEFT };

Direction VectorDirection(glm::vec2 target);
std::tuple<bool, Direction, glm::vec2> CheckCollision(GameObject& ball, GameObject& rect);