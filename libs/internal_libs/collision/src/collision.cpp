#include "collision.h"
#include <glm/gtc/matrix_transform.hpp>

Direction VectorDirection(glm::vec2 target) {
    glm::vec2 compass[] = {
        {0.0f,  1.0f}, {1.0f,  0.0f},
        {0.0f, -1.0f}, {-1.0f, 0.0f}
    };
    float maxDot = 0.0f;
    int bestMatch = -1;
    for (int i = 0; i < 4; i++) {
        float d = glm::dot(glm::normalize(target), compass[i]);
        if (d > maxDot) { maxDot = d; bestMatch = i; }
    }
    return (Direction)bestMatch;
}

std::tuple<bool, Direction, glm::vec2> CheckCollision(GameObject& ball, GameObject& rect) {
    glm::vec2 ballCenter = ball.Position + (ball.Size.x / 2.0f);
    glm::vec2 halfExtents(rect.Size.x / 2.0f, rect.Size.y / 2.0f);
    glm::vec2 rectCenter(rect.Position.x + halfExtents.x, rect.Position.y + halfExtents.y);
    glm::vec2 diff = ballCenter - rectCenter;
    glm::vec2 clamped = glm::clamp(diff, -halfExtents, halfExtents);
    glm::vec2 closest = rectCenter + clamped;
    diff = closest - ballCenter;
    if (glm::length(diff) < (ball.Size.x / 2.0f))
        return { true, VectorDirection(diff), diff };
    return { false, UP, glm::vec2(0.0f) };
}