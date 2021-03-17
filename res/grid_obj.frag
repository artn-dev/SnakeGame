#version 450 core

out vec4 frag_color;

in GS_OUT {
        vec4 color;
} fs_in;

void main()
{
        frag_color = fs_in.color;
}