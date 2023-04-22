//
// Created by Andrew Huang on 4/22/2023.
//

module;

#include <GLFW/glfw3.h>
#include <glad/gl.h>

export module Window;

export class Window {
public:
    Window() {
        glfwInit();
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        m_window = glfwCreateWindow(800, 600, "Modules Test", nullptr, nullptr);
        glfwMakeContextCurrent(m_window);
        gladLoadGL(glfwGetProcAddress);
    }

    ~Window() {
        glfwDestroyWindow(m_window);
        glfwTerminate();
    }

    Window(const Window &) = delete;
    Window(Window &&) = delete;
    Window &operator=(const Window &) = delete;
    Window &operator=(Window &&) = delete;

    template<class Frame>
    void MainLoop(Frame &&frame) {
        while (!glfwWindowShouldClose(m_window)) {
            glfwPollEvents();
            int width, height;
            glfwGetFramebufferSize(m_window, &width, &height);
            frame(width, height);
            glfwSwapBuffers(m_window);
        }
    }

private:
    GLFWwindow *m_window = nullptr;
};
