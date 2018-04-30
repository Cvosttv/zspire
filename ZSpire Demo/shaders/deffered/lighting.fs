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
	float range;
	float intensity;
};

in vec2 UVCoord;

out vec4 Color;

uniform Light lights[60];
uniform int lights_amount = 0;

uniform sampler2D b_diffuse;
uniform sampler2D b_normal;
uniform sampler2D b_frag_pos;

void main(){

	vec3 n_Normal = texture(b_normal, UVCoord).xyz;
	vec3 n_FragmentPos = texture(b_frag_pos, UVCoord).xyz;

	
	vec3 result = texture(b_diffuse, UVCoord).xyz;
	
	for(int lg = 0; lg < lights_amount; lg ++){
		if(lights[lg].type == LIGHTSOURCE_DIR){
			float lightcoeff = max(dot(n_Normal, normalize(lights[lg].dir)), 0.0) * lights[lg].intensity;
			vec3 rlight = lightcoeff * lights[lg].color;
			result += rlight;
		}
		
		if(lights[lg].type == LIGHTSOURCE_POINT){
			float dist = length(lights[lg].pos - n_FragmentPos);
			float factor = 1.0 / ( 1.0 + 1.0 / lights[lg].range * dist + 1.0 / lights[lg].range * dist * dist) * lights[lg].intensity;
			result += lights[lg].color * factor;
		}
	}
	
	
	Color = vec4(result, 1.0);

}