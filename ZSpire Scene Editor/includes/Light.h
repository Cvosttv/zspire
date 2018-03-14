class Light {
public:
	
	float linear;
	float quadratic;
	float maxlight;

	RGBColor light_color;

	void setLightAttenuationParams(float linear, float quadratic, float maxlight);
};