#version 400
in vec3 vertex_colour;
out vec3 fragment_colour;

void main() {
    fragment_colour = vertex_colour;
}
