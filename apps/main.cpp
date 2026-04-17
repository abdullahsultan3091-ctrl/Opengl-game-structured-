#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <tuple>
#include <cmath>

#include "shader.h"
#include "game_object.h"
#include "collision.h"
#include "renderer.h"

// --- Shaders (could later move to .vs/.fs files) ---
const char* vSrc = R"(
#version 330 core
layout (location = 0) in vec2 vertex;
uniform mat4 model;
uniform mat4 projection;
void main() { gl_Position = projection * model * vec4(vertex, 0.0, 1.0); }
)";

const char* fSrc = R"(
#version 330 core
out vec4 color;
uniform vec3 spriteColor;
void main() { color = vec4(spriteColor, 1.0); }
)";

Shader gShader;

void framebuffer_size_callback(GLFWwindow*, int w, int h) {
    glViewport(0, 0, w, h);
    glm::mat4 proj = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f);
    gShader.Use();
    gShader.SetMat4("projection", proj);
}

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Rainbow Breakout", NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    gShader.Compile(vSrc, fSrc);
    glm::mat4 proj = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f);
    gShader.Use();
    gShader.SetMat4("projection", proj);

    Renderer renderer(gShader);

    GameObject Player({ 350.0f, 570.0f }, { 100.0f, 20.0f }, { 1.0f, 1.0f, 1.0f });
    GameObject Ball({ 395.0f, 550.0f }, { 15.0f, 15.0f }, { 1.0f, 1.0f, 1.0f });
    Ball.Velocity = { 300.0f, -350.0f };
    bool stuck = true;

    std::vector<GameObject> bricks;
    const int ROWS = 6, COLS = 10;
    float brickW = 800.0f / COLS, brickH = 30.0f;
    for (int row = 0; row < ROWS; row++)
        for (int col = 0; col < COLS; col++) {
            float r = (float)col / COLS, g = (float)row / ROWS;
            bricks.emplace_back(
                glm::vec2(col * brickW, row * brickH + 50.0f),
                glm::vec2(brickW - 4.0f, brickH - 4.0f),
                glm::vec3(r, g, 1.0f - r));
        }

    float lastFrame = 0.0f;
    while (!glfwWindowShouldClose(window)) {
        float dt = (float)glfwGetTime() - lastFrame;
        lastFrame += dt;
        glfwPollEvents();

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
            Player.Position.x -= 600.0f * dt;
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
            Player.Position.x += 600.0f * dt;
        Player.Position.x = glm::clamp(Player.Position.x, 0.0f, 800.0f - Player.Size.x);
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) stuck = false;

        if (!stuck) {
            Ball.Position += Ball.Velocity * dt;
            if (Ball.Position.x <= 0.0f || Ball.Position.x >= 800.0f - Ball.Size.x) Ball.Velocity.x *= -1.0f;
            if (Ball.Position.y <= 0.0f) Ball.Velocity.y *= -1.0f;
            if (Ball.Position.y > 600.0f) {
                stuck = true;
                Ball.Position = Player.Position + glm::vec2(42.0f, -20.0f);
            }

            auto [pHit, pDir, pDiff] = CheckCollision(Ball, Player);
            if (pHit && Ball.Velocity.y > 0.0f) {
                Ball.Velocity.y *= -1.0f;
                Ball.Position.y = Player.Position.y - Ball.Size.y;
            }

            for (auto& brick : bricks) {
                if (brick.Destroyed) continue;
                auto [hit, dir, diff] = CheckCollision(Ball, brick);
                if (!hit) continue;
                brick.Destroyed = true;
                if (dir == LEFT || dir == RIGHT) {
                    Ball.Velocity.x *= -1.0f;
                    float pen = Ball.Size.x / 2.0f - std::abs(diff.x);
                    Ball.Position.x += (dir == LEFT ? pen : -pen);
                }
                else {
                    Ball.Velocity.y *= -1.0f;
                    float pen = Ball.Size.y / 2.0f - std::abs(diff.y);
                    Ball.Position.y += (dir == UP ? pen : -pen);
                }
                break;
            }
        }
        else {
            Ball.Position = Player.Position + glm::vec2(42.0f, -20.0f);
        }

        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        renderer.Draw(Player);
        renderer.Draw(Ball);
        for (auto& b : bricks) if (!b.Destroyed) renderer.Draw(b);
        glfwSwapBuffers(window);
    }
    glfwTerminate();
}