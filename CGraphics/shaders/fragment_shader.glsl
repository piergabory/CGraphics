#version 400

struct Material {
    float shine;
    float specular;
    float diffuse;
    vec3 color;
};

struct Light {
    vec3 position;
    vec4 color;
    mat4 projection;
};

vec3 phong(Light light, Material material, vec3 normal, vec3 view) {
    vec3 ray = normalize(light.position - view);
    normal = normalize(normal);
    view = normalize(-view);
    vec3 color = light.color.rgb;
    float intensity = light.color.a;

    // Specular
    vec3 reflection = reflect(-ray, normal);
    vec3 specular = material.specular * color * pow(max(dot(view, reflection), 0.0), material.shine);

    // Diffuse
    vec3 diffuse = material.diffuse * color * max(dot(normal, ray), 0.0);

    return (diffuse + specular) * intensity;
}

const vec3 ambient = vec3(0.2);

uniform Material material;
uniform Light lights[10];
uniform int light_count;

in vec3 vertex_position;
in vec3 vertex_normal;
in vec3 vertex_color;

out vec4 fragment_color;

void main() {
    vec3 phongs = vec3(0);
    for (int index = 0; index < 10 && index < light_count; index ++) {
        phongs += phong(lights[index], material, vertex_normal, vertex_position);
    }
    vec3 result = ambient + phongs;
    fragment_color = vec4(result, 1.0);
}
