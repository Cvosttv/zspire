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

	float range;
	float intensity;

	ZSRGBCOLOR light_color;
	ZSVECTOR3 pos;
	ZSVECTOR3 rotation;
	ZSVECTOR3 direction;

	Light() {
		range = 1;
		intensity = 1;
		type = LIGHTSOURCE_DIRECTIONAL;
		label[0] = '\0';
		deleted = false;
		pos = ZSVECTOR3(0.0f, 0.0f, 0.0f);
		rotation = ZSVECTOR3(0.0f, 0.0f, 0.0f);
	}

};

void addLight(Light light);
void createNewLight();
unsigned int getLightsAmount();
Light* getLightByLabelPtr(const char* label);
Light* getLightPtr(unsigned int index);
Light getLight(unsigned int index);