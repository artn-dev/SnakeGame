#ifndef RENDERABLE_HPP
#define RENDERABLE_HPP

#include "Quad.h"

class iRenderable {

public:
        virtual ~iRenderable() = default;
        virtual void set_render_data(Quad*& data, unsigned int& amount) = 0;

};

#endif /* RENDERABLE_HPP */