class Light {
public:
	
	float linear;
	float quadratic;
	float maxlight;

	ZSRGBCOLOR light_color;

	void setLightAttenuationParams(float linear, float quadratic, float maxlight);
};