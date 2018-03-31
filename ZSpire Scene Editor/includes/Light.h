#ifndef ZSLIGHT
#define ZSLIGHT
#endif

class Light {
public:
	
	float linear;
	float quadratic;
	float maxlight;

	ZSRGBCOLOR light_color;
	ZSVECTOR3 pos;

	void setLightAttenuationParams(float linear, float quadratic, float maxlight);
};