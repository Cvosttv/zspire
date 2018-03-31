#version 330 core

out vec4 FragColor;

in vec2 UVCoord;
in vec3 n_Normal;

//textures
uniform sampler2D diffuse;

void main(){

	FragColor = texture(diffuse, UVCoord);
}