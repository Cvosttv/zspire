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

		ZSVECTOR3 light_direction;

		ZSLIGHTTYPE light_type;

		char label[128];

	public:

		void setLightType(ZSLIGHTTYPE light_type);

		void setLightPosition(ZSVECTOR3 position);
		void setLightDirection(ZSVECTOR3 dir);

		void setLightColor(ZSRGBCOLOR color);

		ZSVECTOR3 getPosition();
		ZSVECTOR3 getDirection();
		ZSRGBCOLOR getDiffuseColor();
		ZSLIGHTTYPE getLightType();

		char* getLabel();
		void setLabel(const char* label);

		Light() {
			label[0] = '\0';
			light_type = LIGHT_TYPE_DIRECTIONAL;
			position = ZSVECTOR3(0.0f, 0.0f, 0.0f);

		}

	};

}