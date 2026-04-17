#include "renderer.h"
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

Renderer::Renderer(Shader& shader) : shader(shader) { initQuad(); }

Renderer::~Renderer() {
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
}

void Renderer::initQuad() {
    float vertices[] = {
        0.0f, 1.0f,  1.0f, 0.0f,  0.0f, 0.0f,
        0.0f, 1.0f,  1.0f, 1.0f,  1.0f, 0.0f
    };
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glBindVertexArray(0);
}

void Renderer::Draw(GameObject& obj) {
    shader.Use();
    glm::mat4 model(1.0f);
    model = glm::translate(model, glm::vec3(obj.Position, 0.0f));
    model = glm::scale(model, glm::vec3(obj.Size, 1.0f));
    shader.SetMat4("model", model);
    shader.SetVec3("spriteColor", obj.Color.r, obj.Color.g, obj.Color.b);
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}