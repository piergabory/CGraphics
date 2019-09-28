#version 400
in vec3 vertices;

void main() {
    gl_Position = vec4(vp, 1.0);
}
