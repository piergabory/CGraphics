#version 400

in vec3 vertex_position;
in vec3 vertex_normal;
in vec3 vertex_color;

out vec3 fragment_colour;

void main() {
    float shade = 1 - 0.1 / clamp(vertex_normal.y, 0, 1);
    fragment_colour = vertex_color * shade;
}
