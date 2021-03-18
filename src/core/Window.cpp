#include "Window.h"


Window::Window(const char *title, const WindowConfig& config, EventManager *events)
        :
        title_(title),
        width(config.width),
        height(config.height),
        config_(config),
	events_(events)
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

        glfwWindowHint(GLFW_RESIZABLE, config_.resizable ? GLFW_TRUE : GLFW_FALSE);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, config_.version.major);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, config_.version.minor);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        wnd_obj = glfwCreateWindow(width, height, title_, NULL, NULL);
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

	glfwSetWindowUserPointer(wnd_obj, static_cast<void*>(this));
	glfwSetKeyCallback(wnd_obj,
			[](GLFWwindow *window, int key, int scancode, int action, int mode)
			{
				auto self = static_cast<Window*>(glfwGetWindowUserPointer(window));
				self->events_->key_callback(key, scancode, action, mode);
			}
	);

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
