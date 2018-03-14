#pragma once
class RGBColor {
public:
	int r;
	int g;
	int b;
	int a;

	float gl_r;
	float gl_g;
	float gl_b;
	float gl_a;

	void updateGL();

	RGBColor(int r, int g, int b, int a) {
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;

		this->updateGL();
	}
	RGBColor(int r, int g, int b) {
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = 255;

		this->updateGL();
	}

	RGBColor(){
		this->r = 255;
		this->g = 255;
		this->b = 255;
		this->a = 255;

		this->updateGL();
	}

	unsigned long getHex();
	//RGBColor RGBColor::getRGB();
	RGBColor getInvertedColor();
	Vector3 getVector3();
	
};