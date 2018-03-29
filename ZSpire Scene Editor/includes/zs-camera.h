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

		ZSMATRIX4x4 getCameraProjectionMatrix();
		ZSMATRIX4x4 getCameraViewMatrix();
}