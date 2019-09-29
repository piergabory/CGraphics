#version 400
in vec3 vertex_position_attribute;
in vec3 vertex_colour_attribute;



out vec3 vertex_colour;

void main() {
    vertex_colour = vertex_colour_attribute;
    gl_Position = vec4(vertex_position_attribute, 1.0);
}
