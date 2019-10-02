#version 400

in vec3 vertex_position;
in vec3 vertex_normal;
in vec3 vertex_color;

in vec3 lightsource_position[1];

const vec3 ambient = vec3(0,0,0.1);
const float shine = 40.0;

out vec3 fragment_color;

void main() {
    vec3 normal   = normalize(vertex_normal);
    vec3 view     = normalize(vertex_position);
    vec3 ray      = normalize(lightsource_position[0]);
    vec3 diffuse  = vertex_color;
    vec3 specular = vec3(0.9);

    float intensity = max(dot(normal, ray), 0.0) * 0.9 + 0.1;

    if (intensity > 0.0) {
        vec3 half_vector = normalize(ray + view);
        float specular_angle = max(dot(half_vector, normal), 0.0);
        specular = specular * pow(specular_angle, shine);
    }

    vec3 lighting = max(intensity * diffuse + specular, ambient);

    fragment_color = lighting;
}
