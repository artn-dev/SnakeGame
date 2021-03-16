#include "Window.h"


Window::Window(const char *title, const WindowConfig& config)
        :
        title(title),
        width(config.width),
        height(config.height),
        config(config)
{
}

Window::~Window()
{
        cleanup();
}


bool Window::init()
{
        if (!glfwInit()) {
                std::cerr << "Couldn't initialize glfw\n";
                return -1;
        }

        glfwWindowHint(GLFW_RESIZABLE, config.resizable ? GLFW_TRUE : GLFW_FALSE);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, config.version.major);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, config.version.minor);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        wnd_obj = glfwCreateWindow(width, height, title, NULL, NULL);
        if (wnd_obj == NULL) {
                std::cout << "Failed to create window\n";
                glfwTerminate();
                return false;
        }

        glfwMakeContextCurrent(wnd_obj);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
                std::cout << "Failed to load glad\n";
                glfwDestroyWindow(wnd_obj);
                glfwTerminate();
                return false;
        }

        glViewport(0, 0, width, height);

        std::cout << "OpenGL v" << glGetString(GL_VERSION) << "\n";

        return true;
}

void Window::cleanup()
{
        if (wnd_obj)
                glfwDestroyWindow(wnd_obj);
        glfwTerminate();
}

GLFWwindow* Window::data() const
{
        return wnd_obj;
}

bool Window::is_running() const
{
        return !glfwWindowShouldClose(wnd_obj);
}