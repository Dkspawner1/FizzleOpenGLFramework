#include "FizzleFramework/Core/Renderer.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <stdexcept>

const char *vertexShaderSource = R"(
    #version 330 core
    layout (location = 0) in vec2 aPos;
    layout (location = 1) in vec2 aTexCoord;
    out vec2 TexCoord;
    uniform mat4 projection;
    void main()
    {
        gl_Position = projection * vec4(aPos.x, aPos.y, 0.0, 1.0);
        TexCoord = aTexCoord;
    }
)";

const char *fragmentShaderSource = R"(
    #version 330 core
    in vec2 TexCoord;
    out vec4 FragColor;
    uniform sampler2D ourTexture;
    void main()
    {
        FragColor = texture(ourTexture, TexCoord);
    }
)";

const char *colorVertexShaderSource = R"(
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

const char *colorFragmentShaderSource = R"(
    #version 330 core
    in vec4 vertexColor;
    out vec4 FragColor;
    void main()
    {
        FragColor = vertexColor;
    }
)";

Renderer::Renderer() : m_vao(0), m_vbo(0), m_colorVAO(0), m_colorVBO(0), m_shaderProgram(0), m_colorShaderProgram(0) {
    std::cout << "Renderer constructor called" << std::endl;
}

Renderer::~Renderer() {
    std::cout << "Renderer destructor called" << std::endl;
    glDeleteVertexArrays(1, &m_vao);
    glDeleteBuffers(1, &m_vbo);
    glDeleteVertexArrays(1, &m_colorVAO);
    glDeleteBuffers(1, &m_colorVBO);
    glDeleteProgram(m_shaderProgram);
    glDeleteProgram(m_colorShaderProgram);
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
    setupColorShaders();
    setupBuffers();
    std::cout << "Shader initialization complete" << std::endl;
}

void Renderer::Clear() {
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::DrawQuad(const glm::vec2 &position, const glm::vec2 &size, const glm::vec4 &color) {
    glUseProgram(m_colorShaderProgram);

    glm::mat4 projection = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f);
    GLint projLoc = glGetUniformLocation(m_colorShaderProgram, "projection");
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

    float vertices[] = {
        position.x,         position.y,          color.r, color.g, color.b, color.a,
        position.x + size.x, position.y,          color.r, color.g, color.b, color.a,
        position.x,         position.y + size.y, color.r, color.g, color.b, color.a,
        position.x + size.x, position.y + size.y, color.r, color.g, color.b, color.a
    };

    glBindVertexArray(m_colorVAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_colorVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    glBindVertexArray(0);
    glUseProgram(0);
}

void Renderer::DrawTexturedQuad(const glm::vec2& position, const glm::vec2& size, const Texture* texture) {
    if (texture && texture->IsLoaded()) {
        glUseProgram(m_shaderProgram);

        glm::mat4 projection = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f);
        GLint projLoc = glGetUniformLocation(m_shaderProgram, "projection");
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

        GLint texLoc = glGetUniformLocation(m_shaderProgram, "ourTexture");
        glUniform1i(texLoc, 0); // Set texture unit to 0

        texture->Bind(0); // Bind texture to unit 0

        float vertices[] = {
            // positions        // texture coords
            position.x,         position.y,          0.0f, 0.0f,
            position.x + size.x, position.y,          1.0f, 0.0f,
            position.x,         position.y + size.y, 0.0f, 1.0f,
            position.x + size.x, position.y + size.y, 1.0f, 1.0f
        };

        glBindVertexArray(m_vao);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

        glBindVertexArray(0);
        texture->Unbind();
        glUseProgram(0);
    }
}

void Renderer::Render() {
    // This method is no longer needed as we're rendering immediately in DrawQuad and DrawTexturedQuad
}

void Renderer::setupShaders() {
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
}

void Renderer::setupColorShaders() {
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &colorVertexShaderSource, NULL);
    glCompileShader(vertexShader);
    checkShaderCompileErrors(vertexShader, "COLOR_VERTEX");

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &colorFragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    checkShaderCompileErrors(fragmentShader, "COLOR_FRAGMENT");

    m_colorShaderProgram = glCreateProgram();
    glAttachShader(m_colorShaderProgram, vertexShader);
    glAttachShader(m_colorShaderProgram, fragmentShader);
    glLinkProgram(m_colorShaderProgram);
    checkProgramLinkErrors(m_colorShaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Renderer::setupBuffers() {
    // Setup for textured quads
    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);

    glBindVertexArray(m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Setup for colored quads
    glGenVertexArrays(1, &m_colorVAO);
    glGenBuffers(1, &m_colorVBO);

    glBindVertexArray(m_colorVAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_colorVBO);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Renderer::checkShaderCompileErrors(GLuint shader, const std::string &type) {
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