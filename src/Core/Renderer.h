#pragma once

#include "Texture.h"
#include <GL/glew.h>
#include <glm/ext/vector_float2.hpp>
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
    void DrawTexturedQuad(const glm::vec2& position, const glm::vec2& size, const Texture* texture);
    void Render();

private:
    GLuint m_vao, m_vbo;
    GLuint m_shaderProgram;
    std::vector<float> m_vertexData;

    void InitializeOpenGL();
    void InitializeShaders();
    void setupShaders();
    void setupBuffers();
    void checkShaderCompileErrors(GLuint shader, const std::string& type);
    void checkProgramLinkErrors(GLuint program);
};
