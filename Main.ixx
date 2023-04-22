#include <cstddef>
#include <glad/gl.h>

import Window;
import Shader;
import VertexBuffer;

const char *VERTEX_SHADER_SOURCE = R"GLSL(
#version 450 core
layout (location = 0) in vec2 aPosition;
layout (location = 1) in vec3 aColor;

layout (location = 0) out vec3 vColor;

void main() {
    gl_Position = vec4(aPosition, 0, 1);
    vColor = aColor;
}
)GLSL";

const char *FRAGMENT_SHADER_SOURCE = R"GLSL(
#version 450 core
layout (location = 0) in vec3 vColor;

layout (location = 0) out vec4 fColor;

void main() {
    fColor = vec4(vColor, 1);
}
)GLSL";

struct Vertex {
    float position[2];
    float color[3];

    static void SetupVertexArray(GLuint vao) {
        SetupVertexArrayFloatsAttrib(vao, 0, 0, 2, offsetof(Vertex, position));
        SetupVertexArrayFloatsAttrib(vao, 1, 0, 3, offsetof(Vertex, color));
    }
};

using Mesh = VertexBuffer<Vertex>;

int main() {
    Window window;

    Shader shader{VERTEX_SHADER_SOURCE, FRAGMENT_SHADER_SOURCE};

    const Vertex vertices[]{
            {{-0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},
            {{0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}},
            {{0.0f, 0.5f}, {0.0f, 0.0f, 1.0f}},
    };

    Mesh mesh{3, vertices};

    window.MainLoop([&](int width, int height) {
        glViewport(0, 0, width, height);

        glClearColor(0.4f, 0.8f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.Use();
        mesh.BindAndDraw(GL_TRIANGLES);
    });

    return 0;
}
