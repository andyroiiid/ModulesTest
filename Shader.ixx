//
// Created by Andrew Huang on 4/22/2023.
//

module;

#include <cstdio>
#include <glad/gl.h>
#include <initializer_list>

export module Shader;

import Movable;

GLuint CreateShader(const GLenum type, const char *source) {
    const GLuint shader = glCreateShader(type);

    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    GLint compileStatus = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus);
    if (compileStatus != GL_TRUE) {
        GLint infoLogLength = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
        const auto infoLog = new GLchar[infoLogLength];
        glGetShaderInfoLog(shader, infoLogLength, &infoLogLength, infoLog);
        fprintf(stderr, "Failed to load shader: %s\n", infoLog);
        delete[] infoLog;
        glDeleteShader(shader);
        return 0;
    }

    return shader;
}

GLuint CreateProgram(const std::initializer_list<GLuint> &shaders) {
    const GLuint program = glCreateProgram();

    for (const GLuint shader: shaders)
        glAttachShader(program, shader);
    glLinkProgram(program);

    GLint linkStatus = 0;
    glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
    if (linkStatus != GL_TRUE) {
        GLint infoLogLength = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);
        const auto infoLog = new GLchar[infoLogLength];
        glGetProgramInfoLog(program, infoLogLength, &infoLogLength, infoLog);
        fprintf(stderr, "Failed to link program: %s\n", infoLog);
        delete[] infoLog;
        glDeleteProgram(program);
        return 0;
    }

    for (const GLuint shader: shaders)
        glDetachShader(program, shader);
    return program;
}

export class Shader {
public:
    Shader() = default;

    Shader(const char *vertexSource, const char *fragmentSource) {
        const GLuint vertexShader = CreateShader(GL_VERTEX_SHADER, vertexSource);
        const GLuint fragmentShader = CreateShader(GL_FRAGMENT_SHADER, fragmentSource);

        m_program = CreateProgram({vertexShader, fragmentShader});

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    Shader(const Shader &) = delete;
    Shader(Shader &&) noexcept = default;
    Shader &operator=(const Shader &) = delete;
    Shader &operator=(Shader &&) noexcept = default;

    ~Shader() {
        if (m_program) glDeleteProgram(m_program);
    }

    void Use() const {
        glUseProgram(m_program);
    }

private:
    Movable<GLuint> m_program;
};
