#version 400

uniform mat4 model_view_projection_matrix_uniform;
uniform mat4 model_view_matrix_uniform;
uniform mat4 normal_matrix_uniform;
uniform vec3 lightpoint_array;

in vec3 vertex_position_attribute;
in vec3 vertex_normal_attribute;
in vec3 vertex_color_attribute;

out vec3 vertex_position;
out vec3 vertex_normal;
out vec3 vertex_color;
out vec3 lightsource_position;

void main() {
    vertex_position = (model_view_matrix_uniform * vec4(vertex_position_attribute, 1)).xyz;
    vertex_normal = (normal_matrix_uniform * vec4(vertex_normal_attribute, 1)).xyz;
    vertex_color = vertex_color_attribute;
    lightsource_position = lightpoint_array;

    gl_Position = model_view_projection_matrix_uniform * vec4(vertex_position_attribute, 1);
}
