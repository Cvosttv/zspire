#ifndef ZSLIGHT
#define ZSLIGHT
#endif

#define LIGHT_TYPE_DIRECTIONAL 1
#define LIGHT_TYPE_POINT 2
#define LIGHT_TYPE_SPOT 3
typedef unsigned int ZSLIGHTTYPE;
namespace ZSpire {

	

	class Light {
	protected:
		ZSVECTOR3 position;
		ZSRGBCOLOR diffuse_light_color;

		ZSVECTOR3 light_rotation;
		ZSVECTOR3 light_direction;

		float range;
		float intensity;

		ZSLIGHTTYPE light_type;

		char label[128];

	public:

		void setLightType(ZSLIGHTTYPE light_type);

		void setLightPosition(ZSVECTOR3 position);
		void setLightDirection(ZSVECTOR3 dir);
		void setLightRotation(ZSVECTOR3 rot);

		void setLightColor(ZSRGBCOLOR color);

		void setLightRange(float range);
		void setLightIntensity(float intensity);

		ZSVECTOR3 getPosition();
		ZSVECTOR3 getDirection();
		ZSRGBCOLOR getDiffuseColor();
		ZSLIGHTTYPE getLightType();
		float getLightRange();
		float getLightIntensity();

		char* getLabel();
		void setLabel(const char* label);

		Light() {
			range = 1;
			intensity = 1;
			label[0] = '\0';
			light_type = LIGHT_TYPE_DIRECTIONAL;
			position = ZSVECTOR3(0.0f, 0.0f, 0.0f);
			light_direction = ZSVECTOR3(0.0f, 0.0f, 0.0f);
		}

	};

}