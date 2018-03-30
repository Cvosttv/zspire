#version 460

layout (location = 2) out vec3 gPosition;
layout (location = 1) out vec3 gNormal;
layout (location = 0) out vec3 gAlbedo;
			
in vec2 UVCoord;
in vec3 n_Normal;
in vec3 n_FragmentPos;			
			
uniform sampler2D diffuse;
uniform sampler2D normal;	
			
void main(){
	
	gNormal = n_Normal;
	gPosition = n_FragmentPos;
	gAlbedo = texture(diffuse, UVCoord).rgb;
	
}