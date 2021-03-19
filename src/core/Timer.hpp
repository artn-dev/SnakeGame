#ifndef TIMER_H
#define TIMER_H

#include <GLFW/glfw3.h>


class Timer {

private:
        double last_time;

public:
        Timer()
        {
                last_time = glfwGetTime();
        }

        float tick()
        {
                double curr_time = glfwGetTime();
                double delta_time = curr_time - last_time;

                last_time = curr_time;

                return static_cast<float>(delta_time);
        }

};

#endif /* TIMER_H */