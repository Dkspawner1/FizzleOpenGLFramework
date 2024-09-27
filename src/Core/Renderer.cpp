#include <GL/glew.h>
#include "Renderer.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <stdexcept>

const char* vertexShaderSource = R"(
    #version 330 core
    layout (location = 0) in vec2 aPos;
    layout (location = 1) in vec4 aColor;
    out vec4 vertexColor;
    uniform mat4 projection;
    void main()
    {
        gl_Position = projection * vec4(aPos.x, aPos.y, 0.0, 1.0);
        vertexColor = aColor;
    }
)";

const char* fragmentShaderSource = R"(
    #version 330 core
    in vec4 vertexColor;
    out vec4 FragColor;
    void main()
    {
        FragColor = vertexColor;
    }
)";

Renderer::Renderer() : m_vao(0), m_vbo(0), m_shaderProgram(0) {
    std::cout << "Renderer constructor called" << std::endl;
}

Renderer::~Renderer() {
    std::cout << "Renderer destructor called" << std::endl;
    glDeleteVertexArrays(1, &m_vao);
    glDeleteBuffers(1, &m_vbo);
    glDeleteProgram(m_shaderProgram);
}

void Renderer::Initialize() {
    std::cout << "Renderer::Initialize started" << std::endl;
    InitializeOpenGL();
    InitializeShaders();
    std::cout << "Renderer::Initialize completed" << std::endl;
}

void Renderer::InitializeOpenGL() {
    std::cout << "Initializing OpenGL..." << std::endl;
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        throw std::runtime_error("Failed to initialize GLEW");
    }
    std::cout << "Using GLEW " << glewGetString(GLEW_VERSION) << std::endl;
    std::cout << "OpenGL initialization complete" << std::endl;
}

void Renderer::InitializeShaders() {
    std::cout << "Initializing shaders..." << std::endl;
    setupShaders();
    setupBuffers();
    std::cout << "Shader initialization complete" << std::endl;
}

void Renderer::Clear() {
    glClear(GL_COLOR_BUFFER_BIT);
    m_vertexData.clear();
}

void Renderer::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color) {
    float vertices[] = {
        // First triangle
        position.x, position.y,                 color.r, color.g, color.b, color.a,
        position.x + size.x, position.y,        color.r, color.g, color.b, color.a,
        position.x, position.y + size.y,        color.r, color.g, color.b, color.a,
        // Second triangle
        position.x + size.x, position.y,        color.r, color.g, color.b, color.a,
        position.x + size.x, position.y + size.y, color.r, color.g, color.b, color.a,
        position.x, position.y + size.y,        color.r, color.g, color.b, color.a
    };
    m_vertexData.insert(m_vertexData.end(), std::begin(vertices), std::end(vertices));
}

void Renderer::Render() {
    glUseProgram(m_shaderProgram);

    glm::mat4 projection = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f);
    GLint projLoc = glGetUniformLocation(m_shaderProgram, "projection");
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

    glBindVertexArray(m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, m_vertexData.size() * sizeof(float), m_vertexData.data(), GL_DYNAMIC_DRAW);

    glDrawArrays(GL_TRIANGLES, 0, m_vertexData.size() / 6);

    glBindVertexArray(0);
    glUseProgram(0);
}

void Renderer::setupShaders() {
    std::cout << "Setting up shaders..." << std::endl;
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    checkShaderCompileErrors(vertexShader, "VERTEX");

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    checkShaderCompileErrors(fragmentShader, "FRAGMENT");

    m_shaderProgram = glCreateProgram();
    glAttachShader(m_shaderProgram, vertexShader);
    glAttachShader(m_shaderProgram, fragmentShader);
    glLinkProgram(m_shaderProgram);
    checkProgramLinkErrors(m_shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    std::cout << "Shaders set up successfully" << std::endl;
}

void Renderer::setupBuffers() {
    std::cout << "Setting up buffers..." << std::endl;
    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);

    glBindVertexArray(m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    std::cout << "Buffers set up successfully" << std::endl;
}

void Renderer::checkShaderCompileErrors(GLuint shader, const std::string& type) {
    GLint success;
    GLchar infoLog[1024];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 1024, NULL, infoLog);
        throw std::runtime_error("ERROR::SHADER_COMPILATION_ERROR of type: " + type + "\n" + infoLog);
    }
}

void Renderer::checkProgramLinkErrors(GLuint program) {
    GLint success;
    GLchar infoLog[1024];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 1024, NULL, infoLog);
        throw std::runtime_error("ERROR::PROGRAM_LINKING_ERROR\n" + std::string(infoLog));
    }
}
