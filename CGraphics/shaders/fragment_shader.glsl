#version 400

struct Material {
    float shine;
    float specular;
    float diffuse;
};

uniform Material material;

in vec3 vertex_position;
in vec3 vertex_normal;
in vec3 vertex_color;

in vec3 lightsource_position;

const vec3 ambient = vec3(0.2);
const vec3 light_color = vec3(1.0);
const float shine = 32.0;
const float specular_strength = 0.5;
const float diffuse_strength = 0.5;

out vec4 fragment_color;

void main() {
    vec3 normal =   normalize(vertex_normal);
    vec3 ray =      normalize(lightsource_position - vertex_position);
    vec3 view =     normalize(-vertex_position);
    vec3 reflection = reflect(-ray, normal);
    float specular_intensity = pow(max(dot(view, reflection), 0.0), shine);
    vec3 specular = specular_strength * specular_intensity * light_color;

    float diffuse_intensity = max(dot(normal, ray), 0.0);
    vec3 diffuse = diffuse_strength * light_color * diffuse_intensity;

    vec3 result = (ambient + diffuse + specular) * vertex_color;
    fragment_color = vec4(result, 1.0);
}
