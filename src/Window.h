#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


struct WindowConfig {
        int width;
        int height;
        bool resizable;
        struct {
                int major;
                int minor;
        } version;
};

class Window {
private:
        const int   width;
        const int   height;
        const char *title;
        GLFWwindow *wnd_obj;
        WindowConfig  config;
public:
        Window(const char *title, const WindowConfig& config);
        ~Window();
        
        bool init();
        void cleanup();
        GLFWwindow* data() const;
        bool is_running() const;
        
};

#endif /* WINDOW_H */