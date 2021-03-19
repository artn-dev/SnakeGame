#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include <GLFW/glfw3.h>
#include "graphics/Quad.h"
#include "Observer.h"
#include "graphics/Renderable.h"

class Snake : public iObserver<int, int>, public iRenderable {

private:
        std::vector<Quad> segments;
        kuso::vec2 direction;

public:
        Snake(kuso::vec2 position);
        virtual ~Snake() = default;

        void move();
        void on_notify(int key, int action) override;
        void set_render_data(Quad*& data, unsigned int& amount) override;

};

#endif /* SNAKE_H */