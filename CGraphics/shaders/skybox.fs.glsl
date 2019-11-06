#version 400
in vec3 vertex_position;
in vec3 vertex_normal;
in vec2 vertex_uv;

uniform sampler2D texture_sampler;
uniform samplerCube environment_map;

out vec4 fragment_color;

void main() {
    vec3 pixel = texture(environment_map, -vertex_position).rgb;
    fragment_color = vec4(pixel, 1.0);
}
