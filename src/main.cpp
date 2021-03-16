#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

int main()
{
        GLFWwindow *window = nullptr;
        const int SCREEN_WIDTH  = 300;
        const int SCREEN_HEIGHT = 300;

        if (!glfwInit()) {
                std::cout << "Couldn't initialize glfw\n";
                return -1;
        }

        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Snake Game", NULL, NULL);
        if (window == NULL) {
                std::cout << "Failed to create window\n";
                glfwTerminate();
                return -1;
        }

        glfwMakeContextCurrent(window);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
                std::cout << "Failed to load glad\n";
                glfwDestroyWindow(window);
                glfwTerminate();
                return -1;
        }

        std::cout << "OpenGL v" << glGetString(GL_VERSION) << "\n";

        const float red[4] = { 255.0f, 0.0f, 0.0f, 255.0f };

        while (!glfwWindowShouldClose(window)) {
                glfwPollEvents();

                glClearBufferfv(GL_COLOR, 0, red);

                glfwSwapBuffers(window);
        }

        glfwDestroyWindow(window);
        glfwTerminate();
        return 0;
}