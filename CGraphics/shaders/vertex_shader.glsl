#version 400
in vec3 vertex_position_attribute;
in vec3 vertex_colour_attribute;

uniform mat4 model_view_projection_matrix_uniform;
uniform mat4 model_view_matrix_uniform;
uniform mat4 normal_matrix_uniform;

out vec3 vertex_position;
out vec3 vertex_normal;

void main() {
    vertex_position = (model_view_matrix_uniform * vec4(vertex_position_attribute, 1)).xyz;
    vertex_normal = (normal_matrix_uniform * vec4(vertex_position_attribute, 1)).xyz;
    gl_Position = model_view_projection_matrix_uniform * vec4(vertex_position_attribute, 1);
}
