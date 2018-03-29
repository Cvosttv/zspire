#version 460

layout (location = 2) out vec3 gPosition;
layout (location = 1) out vec3 gNormal;
layout (location = 0) out vec3 gAlbedo;
			
in vec2 UVCoord;
in vec3 n_Normal;
			
uniform sampler2D diffuse;			
			
int main(){
	
	gNormal = n_Normal;
	gAlbedo = texture(diffuse, UVCoord);
	
}