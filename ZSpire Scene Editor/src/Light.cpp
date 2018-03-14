typedef unsigned int uint;

#include "../includes/DMath.h"
#include "../includes/DColor.h"
#include "../includes/Light.h"

void Light::setLightAttenuationParams(float linear, float quadratic, float maxlight) {
	this->linear = linear;
	this->quadratic = quadratic;
	this->maxlight = maxlight;

}
