#include "EventManager.h"


void EventManager::notify(int key, int action)
{
        for (auto& observer : subscribed) {
                observer->on_notify(key, action);
        }
}

void EventManager::subscribe(iObserver<int, int>* observer)
{
        subscribed.push_back(observer);
}

bool EventManager::is_pressed(int key)
{
        try {
                return keys_.at(key);
        } catch (const std::out_of_range& e) {
                return false;
        }
}

void EventManager::key_callback(int key, int scancode, int action, int mode)
{
        notify(key, action);

        switch (action) {
        case GLFW_PRESS:
                keys_[key] = true;
                break;
        case GLFW_RELEASE:
                keys_[key] =  false;
                break;
        }
}
