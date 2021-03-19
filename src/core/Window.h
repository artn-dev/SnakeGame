#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "EventManager.h"


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
        WindowConfig  config_;
        const int     width;
        const int     height;
        const char   *title_;
        GLFWwindow   *wnd_obj;
	EventManager *events_;

public:
        Window(const char *title, const WindowConfig& config, EventManager *events);

        ~Window();
        
        bool init();
        void cleanup();
        GLFWwindow* data() const;
        bool is_running() const;
        
};

#endif /* WINDOW_H */
