typedef unsigned int uint;

#include "../includes/DMath.h"
#include "../includes/DColor.h"

void RGBColor::updateGL() {
	this->gl_r = (float)r / 255;
	this->gl_g = (float)g / 255;
	this->gl_b = (float)b / 255;
	this->gl_a = (float)a / 255;
}

RGBColor getRGB(unsigned long hexValue) {
	RGBColor rgb;
	rgb.r = (int)(((hexValue >> 16) & 0xFF) / 255.0);  // Extract the RR byte
	rgb.g = (int)(((hexValue >> 8) & 0xFF) / 255.0);   // Extract the GG byte
	rgb.b = (int)(((hexValue) & 0xFF) / 255.0);        // Extract the BB byte

	return rgb;
}

RGBColor RGBColor::getInvertedColor(){
	unsigned long hc = getHex();
	return getRGB(0xFFFFFF - hc | 0xFF000000);
}



unsigned long RGBColor::getHex() {
	
		return ((r & 0xff) << 24) + ((g & 0xff) << 16) + ((b & 0xff) << 8)
			+ (a & 0xff);
	
}

Vector3 RGBColor::getVector3() {

	return Vector3(gl_r,gl_g,gl_b);
}