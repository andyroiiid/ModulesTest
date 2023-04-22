//
// Created by Andrew Huang on 4/22/2023.
//

module;

#include <glad/gl.h>

export module VertexBuffer;

import Movable;

export template<typename Vertex>
class VertexBuffer {
public:
    VertexBuffer() {
        glCreateBuffers(1, &m_vbo);

        glCreateVertexArrays(1, &m_vao);
        glVertexArrayVertexBuffer(m_vao, 0, m_vbo, 0, sizeof(Vertex));

        Vertex::SetupVertexArray(m_vao);
    }

    VertexBuffer(const size_t count, const Vertex *data)
        : VertexBuffer() {
        UpdateData(count, data, GL_STATIC_DRAW);
    }

    ~VertexBuffer() {
        if (m_vbo) glDeleteBuffers(1, &m_vbo);
        if (m_vao) glDeleteVertexArrays(1, &m_vao);
    }

    VertexBuffer(const VertexBuffer &) = delete;
    VertexBuffer(VertexBuffer &&) noexcept = default;
    VertexBuffer &operator=(const VertexBuffer &) = delete;
    VertexBuffer &operator=(VertexBuffer &&) noexcept = default;

    void UpdateData(const size_t count, const Vertex *data, const GLenum usage = GL_DYNAMIC_DRAW) {
        m_count = static_cast<GLsizei>(count);
        glNamedBufferData(m_vbo, count * sizeof(Vertex), data, usage);
    }

    void BindAndDraw(const GLenum mode) const {
        glBindVertexArray(m_vao);
        glDrawArrays(mode, 0, m_count);
    }

protected:
    Movable<GLuint> m_vbo;
    Movable<GLuint> m_vao;
    Movable<GLsizei> m_count;
};

export void SetupVertexArrayAttrib(
        const GLuint vao,
        const GLuint attribIndex,
        const GLuint bindingIndex,
        const GLint size,
        const GLenum type,
        const GLboolean normalized,
        const GLuint relativeOffset) {
    glEnableVertexArrayAttrib(vao, attribIndex);
    glVertexArrayAttribBinding(vao, attribIndex, bindingIndex);
    glVertexArrayAttribFormat(vao, attribIndex, size, type, normalized, relativeOffset);
}

export void SetupVertexArrayFloatsAttrib(
        const GLuint vao,
        const GLuint attribIndex,
        const GLuint bindingIndex,
        const GLint size,
        const GLuint relativeOffset) {
    SetupVertexArrayAttrib(vao, attribIndex, bindingIndex, size, GL_FLOAT, GL_FALSE, relativeOffset);
}
