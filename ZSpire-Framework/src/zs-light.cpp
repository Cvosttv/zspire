
#include "string.h"

#include "../includes/zs-math.h"

#include "../includes/zs-light.h"

#ifdef __linux__
#define strcpy_s strcpy
#endif


void ZSpire::Light::setLightType(ZSLIGHTTYPE light_type) {
	this->light_type = light_type;
}

void ZSpire::Light::setLightPosition(ZSVECTOR3 position) {

	this->position = position;
}

void ZSpire::Light::setLightDirection(ZSVECTOR3 dir) {
	this->light_direction = dir;
}

void ZSpire::Light::setLightColor(ZSRGBCOLOR color) {
	this->diffuse_light_color = color;
}

ZSVECTOR3 ZSpire::Light::getPosition() {
	return this->position;
}

ZSRGBCOLOR ZSpire::Light::getDiffuseColor() {
	return this->diffuse_light_color;
}

ZSVECTOR3 ZSpire::Light::getDirection() {
	return this->light_direction;
}

ZSLIGHTTYPE ZSpire::Light::getLightType() {
	return light_type;
}

void ZSpire::Light::setLabel(const char* label) {
	strcpy_s(this->label, label);
}

char* ZSpire::Light::getLabel() {
	return this->label;
}
