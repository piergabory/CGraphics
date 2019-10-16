#version 400
in vec3 vertex_position;
in vec3 vertex_normal;
in vec2 vertex_uv;

uniform sampler2D texture_sampler;

out vec4 fragment_color;

void main() {
    vec3 pixel = texture(texture_sampler, vertex_uv).rgb + vec3(0,0,0);
    fragment_color = vec4(pixel, 1.0);
}