#version 460 core

#define LIGHTSOURCE_NONE 0
#define LIGHTSOURCE_DIR 1
#define LIGHTSOURCE_POINT 2
#define LIGHTSOURCE_SPOT 3

struct Light{
	int type;
	vec3 pos;
	vec3 dir;
	vec3 color;
};

out vec4 FragColor;

in vec2 UVCoord;
in vec3 n_Normal;

//textures
uniform sampler2D diffuse;

uniform Light lights[60];
uniform int lights_amount = 0;

void main(){

	vec3 result = texture(diffuse, UVCoord).xyz;
	
	for(int lg = 0; lg < lights_amount; lg ++){
		if(lights[lg].type == LIGHTSOURCE_DIR){
			float lightcoeff = max(dot(n_Normal, normalize(lights[lg].dir)), 0.0);
			vec3 rlight = lightcoeff * lights[lg].color;
			result += rlight;
		}
	}
	
	
	FragColor = vec4(result, 1.0);
}