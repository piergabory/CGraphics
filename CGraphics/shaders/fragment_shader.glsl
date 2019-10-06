#version 400

struct Material {
    float shine;
    float specular;
    float diffuse;
    vec3 color;
};

struct Light {
    vec3 position;
    vec3 color;
};


const vec3 ambient = vec3(0.2);

uniform Material material;
uniform Light light;

in vec3 vertex_position;
in vec3 vertex_normal;
in vec3 vertex_color;

out vec4 fragment_color;

void main() {
    // Normalize
    vec3 normal = normalize(vertex_normal);
    vec3 ray =    normalize(light.position - vertex_position);
    vec3 view =   normalize(-vertex_position);

    // Specular
    vec3 reflection = reflect(-ray, normal);
    float specular_intensity = pow(max(dot(view, reflection), 0.0), material.shine);
    vec3 specular = material.specular * specular_intensity * light.color;

    // Diffuse
    float diffuse_intensity = max(dot(normal, ray), 0.0);
    vec3 diffuse = material.diffuse * light.color * diffuse_intensity;

    // Mix
    vec3 result = (ambient + diffuse + specular) * vertex_color;
    fragment_color = vec4(result, 1.0);
}
