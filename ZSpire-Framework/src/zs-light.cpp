
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
void ZSpire::Light::setLightRotation(ZSVECTOR3 rot) {
	this->light_rotation = rot;
	this->light_direction = _getDirection(light_rotation.X, light_rotation.Y, light_rotation.Z);
}
void ZSpire::Light::setLightColor(ZSRGBCOLOR color) {
	this->diffuse_light_color = color;
}

void ZSpire::Light::setLightRange(float range){
	this->range = range;
}
void ZSpire::Light::setLightIntensity(float intensity){
	this->intensity = intensity;
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

float ZSpire::Light::getLightRange(){
	return range;
}

float ZSpire::Light::getLightIntensity() {
	return intensity;
}

void ZSpire::Light::setLabel(const char* label) {
	strcpy_s(this->label, label);
}

char* ZSpire::Light::getLabel() {
	return this->label;
}
