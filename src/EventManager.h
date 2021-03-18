#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include <vector>
#include <map>
#include <GLFW/glfw3.h>
#include "Subject.h"
#include "Observer.h"


class EventManager : public iSubject<int, int> {

private:
        std::vector<iObserver<int, int>*> subscribed;
        std::map<int, bool> keys_;

        EventManager() = default;
        virtual ~EventManager() = default;

        static EventManager *instance_;

public:
        virtual void notify(int key, int action);
        virtual void subscribe(iObserver<int, int>* observer);
        bool is_pressed(int key);
        

public:
        static EventManager* instance();
        static void cleanup();
        static void key_callback(
                GLFWwindow* window, int key, int scancode, int action, int mode
        );
        
};

#endif /* EVENT_MANAGER_H */