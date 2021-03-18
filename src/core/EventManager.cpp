#include "EventManager.h"


EventManager* EventManager::instance_ = nullptr;


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

EventManager* EventManager::instance()
{
        if (instance_ == nullptr)
                instance_ = new EventManager();
        return instance_;
}

void EventManager::cleanup()
{
        delete instance_;
}

void EventManager::key_callback(
        GLFWwindow* window, int key, int scancode, int action, int mode
)
{
        instance_->notify(key, action);

        switch (action) {
        case GLFW_PRESS:
                instance_->keys_[key] = true;
                break;
        case GLFW_RELEASE:
                instance_->keys_[key] =  false;
                break;
        }
}