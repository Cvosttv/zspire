#ifndef ZSLIGHT
#define ZSLIGHT
#endif

class Light {
public:
	
	char label[255];
	bool deleted;

	float linear;
	float quadratic;
	float maxlight;

	ZSRGBCOLOR light_color;
	ZSVECTOR3 pos;

	void setLightAttenuationParams(float linear, float quadratic, float maxlight);

	Light() {
		label[0] = '\0';
		deleted = false;
		pos = ZSVECTOR3(0.0f, 0.0f, 0.0f);
	}

};

void addLight(Light light);
void createNewLight();
unsigned int getLightsAmount();
Light* getLightByLabelPtr(const char* label);
Light* getLightPtr(unsigned int index);