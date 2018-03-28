
#include "../includes/zs-math.h"

#include "../includes/zs-light.h"

void ZSpire::Light::setLightType(ZS_LIGHT_TYPE light_type) {
	this->light_type = light_type;
}

void ZSpire::Light::setLightPosition(ZSVECTOR3 position) {

	this->position = position;
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