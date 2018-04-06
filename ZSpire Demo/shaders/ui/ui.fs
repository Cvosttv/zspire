#version 460 core

out vec4 FragColor;

in vec2 UVCoord;

//textures
uniform sampler2D diffuse;

void main(){

	FragColor = texture(diffuse, UVCoord);
}