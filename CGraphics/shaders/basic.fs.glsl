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
};

vec3 phong(Light light, Material material, vec3 normal, vec3 view, vec3 pixel) {
    vec3 ray = normalize(light.position - view);
    normal = normalize(normal);
    view = normalize(-view);
    vec3 color = light.color.rgb;
    float intensity = light.color.a;

    // Specular
    vec3 reflection = reflect(-ray, normal);
    vec3 specular = material.specular * color * pow(max(dot(view, reflection), 0.0), material.shine);

    // Diffuse
    vec3 diffuse = pixel * max(dot(normal, ray), 0.0);

    return (diffuse + specular) * intensity;
}

vec3 reflexUV(vec3 normal, vec3 view) {
    normal = normalize(normal);
    view = normalize(view);
    vec3 reflex = reflect(view, normal);
    return reflex;
}

const vec3 ambient = vec3(0.839215686, 0.792156863, 0.690196078) * 0.1;

uniform Material material;
uniform Light lights[10];
uniform int light_count;

uniform sampler2D texture_sampler;
uniform samplerCube environment_map;

in vec3 vertex_position;
in vec3 vertex_normal;
in vec2 vertex_uv;

out vec4 fragment_color;

void main() {
    vec3 phongs = vec3(0);
    vec3 pixel = texture(texture_sampler, vertex_uv).rgb;

    for (int index = 0; index < 10 && index < light_count; index ++) {
        phongs += phong(lights[index], material, vertex_normal, vertex_position, pixel);
    }

    vec3 reflex = texture(environment_map, reflexUV(vertex_normal, vertex_position)).rgb * 1;

    vec3 result = mix(ambient + phongs, reflex, 0.5);
    fragment_color = vec4(result, 1.0);
}
