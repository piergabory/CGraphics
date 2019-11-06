#version 400
in vec3 vertex_position;
in vec3 vertex_normal;

out vec4 fragment_color;

void main() {
    vec3 color = normalize(vertex_normal);
    fragment_color = vec4(color, 1.0);
}
