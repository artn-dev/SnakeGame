#version 450 core

layout (location = 0) in vec2  attrib_position;
layout (location = 1) in vec4  attrib_color;
layout (location = 2) in float attrib_padding;

out VS_OUT {
        vec4  color;
        float padding;
} vs_out;


void main()
{
        gl_Position    = vec4(attrib_position, 0, 1);

        vs_out.color   = attrib_color;
        vs_out.padding = attrib_padding;
}