#define _CRT_SECURE_NO_WARNINGS

#include <vector>
#include "../includes/zs-math.h"
#include "../includes/Light.h"

std::vector<Light> lights;


void createNewLight() {
	Light light;
	strcpy(light.label, "light");
	addLight(light);
}

void addLight(Light light){
	lights.push_back(light);
}

unsigned int getLightsAmount() {
	return (unsigned int)lights.size();
}

Light* getLightPtr(unsigned int index) {
	return &lights[index];
}

Light getLight(unsigned int index) {
	return lights[index];
}

Light* getLightByLabelPtr(const char* label) {
	for (unsigned int i = 0; i < getLightsAmount(); i++) {
		if (strcmp(lights[i].label, label) == 0) return &lights[i];
	}
	return nullptr;
}