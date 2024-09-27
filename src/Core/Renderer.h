#pragma once

#define GLEW_STATIC
#define GLEW_NO_GLU
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include <string>

class Renderer {
public:
    Renderer();
    ~Renderer();

    void Initialize();
    void Clear();
    void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
    void Render();

private:
    GLuint vao, vbo;
    GLuint shaderProgram;
    std::vector<float> vertexData;

    void setupShaders();
    void setupBuffers();
    void checkShaderCompileErrors(GLuint shader, const std::string& type);
    void checkProgramLinkErrors(GLuint program);
};
