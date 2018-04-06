#ifndef  ZSTRANSFORM
#define ZSTRANSFORM
#endif // ! ZSTRANSFORM

#ifndef ZSMATH
#include "../includes/zs-math.h"
#endif


namespace ZSpire {
	class Transform {
	protected:

		ZSVECTOR3 position;
		ZSVECTOR3 scale;
		ZSVECTOR3 rotation;

		
	public:

		Transform() {
			position = ZSVECTOR3(0,0,0);
			scale = ZSVECTOR3(1,1,1);
			rotation = ZSVECTOR3(0,0,0);
		}

		ZSMATRIX4x4 translation_matrix;

		void setPosition(ZSVECTOR3 pos);
		void setScale(ZSVECTOR3 scale);
		void setRotation(ZSVECTOR3 rotation);

		ZSVECTOR3 getPosition();
		ZSVECTOR3 getScale();
		ZSVECTOR3 getRotation();

		void updateMatrix();
	};
}