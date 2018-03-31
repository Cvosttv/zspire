#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uv;
layout (location = 2) in vec3 normal;
layout (location = 3) in vec3 tangent;
layout (location = 4) in vec3 bitangent;

out vec2 UVCoord;
out vec3 n_Normal;

uniform mat4 cam_projection;
uniform mat4 cam_view;
uniform mat4 object_transform;

void main(){
	UVCoord = uv;
	n_Normal = normalize(normal);
	gl_Position = cam_projection * cam_view * object_transform * vec4(position, 1.0);
	
}