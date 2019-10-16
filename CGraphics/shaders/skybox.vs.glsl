#version 400

uniform mat4 model_view_projection_matrix_uniform;
uniform mat4 model_view_matrix_uniform;
uniform mat4 normal_matrix_uniform;

in vec3 vertex_position_attribute;
in vec3 vertex_normal_attribute;
in vec2 vertex_uv_attribute;

out vec3 vertex_position;
out vec3 vertex_normal;
out vec2 vertex_uv;

void main() {
    vertex_position = (model_view_matrix_uniform * vec4(vertex_position_attribute, 1)).xyz;
    vertex_normal = (normal_matrix_uniform * vec4(vertex_normal_attribute, 1)).xyz;
    vertex_uv = vertex_uv_attribute;
    
    gl_Position = model_view_projection_matrix_uniform * vec4(vertex_position_attribute, 1);
}
