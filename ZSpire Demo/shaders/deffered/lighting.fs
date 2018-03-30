#version 460 core


in vec2 UVCoord;

out vec4 Color;

uniform sampler2D b_diffuse;
uniform sampler2D b_normal;
uniform sampler2D b_frag_pos;

void main(){

	Color = texture(b_diffuse, UVCoord);

}