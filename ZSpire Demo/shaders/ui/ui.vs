#version 460 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uv;

out vec2 UVCoord;

uniform float size_x;
uniform float size_y;

uniform float pos_x;
uniform float pos_y;

uniform float frame_x;
uniform float frame_y;

void main(){
	UVCoord = uv;
	
	gl_Position = vec4(((position.x * size_x + pos_x) / frame_x) * 2 - 1 , ((position.y * size_y + pos_y) / frame_y) * 2 - 1, 0, 1.0);
}