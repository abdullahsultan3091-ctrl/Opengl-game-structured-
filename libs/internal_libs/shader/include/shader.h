#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>

class Shader {
public:
    unsigned int ID;
    Shader() : ID(0) {}
    void Compile(const char* vertSrc, const char* fragSrc);
    void Use();
    void SetMat4(const char* name, const glm::mat4& mat);
    void SetVec3(const char* name, float r, float g, float b);
private:
    unsigned int compileStage(unsigned int type, const char* src);
};