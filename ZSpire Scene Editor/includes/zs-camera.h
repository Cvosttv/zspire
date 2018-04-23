#ifndef ZSCAMERA
#define ZSCAMERA
#endif

#ifndef ZSTRANSFORM
#include "../includes/zs-transform.h"
#endif


#define CAMERA_PROJECTION_PERSPECTIVE 1
#define CAMERA_PROJECTION_ORTHOGRAPHIC 2

typedef unsigned int ZSPROJECTIONTYPE;

namespace ZSpire {

	
		
		
		void InitializeCamera();

		void setCameraProjectionType(ZSPROJECTIONTYPE type);

		void setCameraZPlanes(float znear, float zfar);

		void setCameraFOV(float nfov);

		void setCameraProjectionResolution(float WIDTH, float HEIGHT);

		void updateCameraMatrix();

		void setCameraPosition(ZSVECTOR3 position);
		void setCameraFront(ZSVECTOR3 front);

		ZSMATRIX4x4 getCameraProjectionMatrix();
		ZSMATRIX4x4 getCameraViewMatrix();

		ZSVECTOR3 getCameraPos();
		ZSVECTOR3 getCameraFront();
		ZSVECTOR3 getCameraRight();
}