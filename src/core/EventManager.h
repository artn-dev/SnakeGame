#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include <vector>
#include <map>
#include <GLFW/glfw3.h>
#include "game_objects/Subject.h"
#include "game_objects/Observer.h"


class EventManager : public iSubject<int, int> {

private:
        std::vector<iObserver<int, int>*> subscribed;
        std::map<int, bool> keys_;

public:
        virtual ~EventManager() = default;
	
        virtual void notify(int key, int action);
        virtual void subscribe(iObserver<int, int>* observer);
        bool is_pressed(int key);
        void key_callback(int key, int scancode, int action, int mode);
        
};

#endif /* EVENT_MANAGER_H */
