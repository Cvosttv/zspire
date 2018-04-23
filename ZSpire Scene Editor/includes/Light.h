#ifndef ZSLIGHT
#define ZSLIGHT
#endif

#define LIGHTSOURCE_DIRECTIONAL 1
#define LIGHTSOURCE_SPOT 3
#define LIGHTSOURCE_POINT 2

class Light {
public:
	
	int type;

	char label[255];
	bool deleted;

	float linear;
	float quadratic;
	float maxlight;

	ZSRGBCOLOR light_color;
	ZSVECTOR3 pos;
	ZSVECTOR3 direction;

	void setLightAttenuationParams(float linear, float quadratic, float maxlight);

	Light() {
		type = LIGHTSOURCE_DIRECTIONAL;
		label[0] = '\0';
		deleted = false;
		pos = ZSVECTOR3(0.0f, 0.0f, 0.0f);
		direction = ZSVECTOR3(0.0f, 0.0f, 0.0f);
	}

};

void addLight(Light light);
void createNewLight();
unsigned int getLightsAmount();
Light* getLightByLabelPtr(const char* label);
Light* getLightPtr(unsigned int index);
Light getLight(unsigned int index);