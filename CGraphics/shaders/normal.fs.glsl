#version 400
in vec3 vertex_position;
in vec3 vertex_normal;

out vec4 fragment_color;

void main() {
    vec3 color = normalize(vertex_normal);//normalize(vertex_normal) * 0.5 + vec3(0.5);
    fragment_color = vec4(color, 1.0);
}
