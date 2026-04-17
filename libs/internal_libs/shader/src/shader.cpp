#include "shader.h"
#include <iostream>
#include <glm/gtc/type_ptr.hpp>

unsigned int Shader::compileStage(unsigned int type, const char* src) {
    unsigned int id = glCreateShader(type);
    glShaderSource(id, 1, &src, NULL);
    glCompileShader(id);
    int ok; glGetShaderiv(id, GL_COMPILE_STATUS, &ok);
    if (!ok) {
        char log[512]; glGetShaderInfoLog(id, 512, NULL, log);
        std::cerr << "Shader error: " << log << "\n";
    }
    return id;
}

void Shader::Compile(const char* vertSrc, const char* fragSrc) {
    unsigned int vs = compileStage(GL_VERTEX_SHADER, vertSrc);
    unsigned int fs = compileStage(GL_FRAGMENT_SHADER, fragSrc);
    ID = glCreateProgram();
    glAttachShader(ID, vs); glAttachShader(ID, fs);
    glLinkProgram(ID);
    glDeleteShader(vs); glDeleteShader(fs);
}

void Shader::Use() { glUseProgram(ID); }

void Shader::SetMat4(const char* name, const glm::mat4& mat) {
    glUniformMatrix4fv(glGetUniformLocation(ID, name), 1, GL_FALSE, glm::value_ptr(mat));
}

void Shader::SetVec3(const char* name, float r, float g, float b) {
    glUniform3f(glGetUniformLocation(ID, name), r, g, b);
}