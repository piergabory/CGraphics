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

vec2 reflexUV(vec3 normal, vec3 view) {
    normal = normalize(normal);
    vec3 reflex = reflect(-view, normal);

    vec2 division = vec2(0.25, 0.33);
    vec2 up = vec2(division.x, 0);
    vec2 down = vec2(division.x, division.y * 2);

    vec2 left = vec2(division.x, division.y);
    vec2 right = vec2(division.x * 3, division.y);

    vec2 front = vec2(division.x * 2, division.y);
    vec2 back = vec2(0, division.y);


    vec2 centered_uv = vec2(0);
    // xyz to uv
    // up
    if (reflex.x < reflex.y && reflex.z < reflex.y) {
        centered_uv = reflex.xz * division + up;
    }
    // down
    else if (reflex.x < reflex.y && reflex.x < reflex.z) {
        centered_uv = reflex.xz * division + down;
    }
    // front
    else if (reflex.y < reflex.z && reflex.x < reflex.z) {
        centered_uv = reflex.xy * division + front;
    }
    // back
    else if (reflex.y > reflex.z && reflex.x > reflex.z) {
        centered_uv = reflex.xy * division + back;
    }
    // left
    else if (reflex.y < reflex.x && reflex.z < reflex.x) {
        centered_uv = reflex.yz * division + left;
    }
    // right
    else if (reflex.y > reflex.x && reflex.z > reflex.x) {
        centered_uv = reflex.yz * division + right;
    }


    return (centered_uv + 1) / 2;
}

const vec3 ambient = vec3(0.839215686, 0.792156863, 0.690196078) * 0.1;

uniform Material material;
uniform Light lights[10];
uniform int light_count;

uniform sampler2D texture_sampler;
uniform sampler2D environment_map;

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

    vec3 reflex = texture(environment_map, reflexUV(vertex_normal, vertex_position)).rgb * 0.2;

    vec3 result = ambient + phongs + reflex;
    fragment_color = vec4(result, 1.0);
}
