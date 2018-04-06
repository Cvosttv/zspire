#ifndef ZSCAMERA
#define ZSCAMERA
#endif

#ifndef ZSTRANSFORM
#include "../includes/zs-transform.h"
#endif

#define CAMERA_MODE_UI 1
#define CAMERA_MODE_SCENE 2

#define CAMERA_PROJECTION_PERSPECTIVE 1
#define CAMERA_PROJECTION_ORTHOGRAPHIC 2

typedef unsigned int ZSCAMERAMODE;
typedef unsigned int ZSPROJECTIONTYPE;

namespace ZSpire {
	namespace Camera {

		void InitializeCamera();

		void setCameraProjectionType(ZSPROJECTIONTYPE type);

		void setCameraZPlanes(float znear, float zfar);

		void setCameraFOV(float nfov);

		void setCameraProjectionResolution(float WIDTH, float HEIGHT);

		void updateCameraMatrix();

		void setCameraPosition(ZSVECTOR3 position);

		ZSMATRIX4x4 getCameraProjectionMatrix();
		ZSMATRIX4x4 getCameraViewMatrix();

		void setCameraMode(ZSCAMERAMODE mode);

		ZSVECTOR2 getCameraResolution();
	}
}