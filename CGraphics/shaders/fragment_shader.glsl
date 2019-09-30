#version 400

in vec3 vertex_position;
in vec3 vertex_normal;

out vec3 fragment_colour;

void main() {
    fragment_colour = vertex_normal;
}
