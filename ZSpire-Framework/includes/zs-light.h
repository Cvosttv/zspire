#ifndef ZSLIGHT
#define ZSLIGHT
#endif

#define LIGHT_TYPE_DIRECTIONAL 1
#define LIGHT_TYPE_POINT 2
#define LIGHT_TYPE_SPOT 3

namespace ZSpire {

	typedef unsigned int ZS_LIGHT_TYPE;

	class Light {
	protected:
		ZSVECTOR3 position;
		ZSRGBCOLOR diffuse_light_color;

		ZSVECTOR3 light_direction;

		ZS_LIGHT_TYPE light_type;

	public:

		void setLightType(ZS_LIGHT_TYPE light_type);

		void setLightPosition(ZSVECTOR3 position);

		ZSVECTOR3 getPosition();
		ZSVECTOR3 getDirection();
		ZSRGBCOLOR getDiffuseColor();

	};

}