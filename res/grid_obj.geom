#version 450 core

layout (points) in;
layout (triangle_strip, max_vertices = 4) out;


in VS_OUT {
        vec4 color;
        float padding;
} gs_in[];

out GS_OUT {
        vec4 color;
} gs_out;

uniform int grid_rows;
uniform int grid_cols;
uniform float grid_cellsize;

mat4 get_projection(float width, float height);
void build_quad(vec3 grid_pos, float pad, mat4 proj);

void main()
{
        float total_width  = grid_cols * grid_cellsize;
        float total_height = grid_rows * grid_cellsize;

        mat4 proj = get_projection(total_width, total_height);

        if (1 != 0)
                gs_out.color = gs_in[0].color;
        else
                gs_out.color = vec4(0.2,0,0.3,1);

        build_quad(gl_in[0].gl_Position.xyz, gs_in[0].padding, proj);
}

mat4 get_projection(float width, float height)
{
        mat4 proj;

        for (int i = 0; i < 4; i++)
                for (int j = 0; j < 4; j++)
                        proj[i][j] = 0;

        proj[0][0] =  2.0 / width;
        proj[1][1] = -2.0 / height;
        proj[2][2] =  1.0;
        proj[3][3] =  1.0;
        proj[3][0] = -1.0;
        proj[3][1] =  1.0;

        return proj;
}

void build_quad(vec3 grid_pos, float pad, mat4 proj)
{
        vec3 vertex_offsets[] = {
                vec3(0, 0, 0),  // top-left
                vec3(1, 0, 0),  // top-right
                vec3(0, 1, 0),  // bottom-left
                vec3(1, 1, 0),  // bottom-right
        };

        vec3 pad_offset = pad * vec3(1, 1, 0);
        vec3 topleft    = grid_cellsize * grid_pos;
        float size      = grid_cellsize - 2 * pad;

        for (int i = 0; i < 4; i++) {
                vec3 position = topleft + size * vertex_offsets[i] + pad_offset;
                gl_Position   = proj * vec4(position, 1);
                EmitVertex();
        }

        EndPrimitive();
}