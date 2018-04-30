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
		//Sets default values to camera properties
		void InitializeCamera();
		//Sets Projectional type
		//CAMERA_PROJECTION_PERSPECTIVE: to render 3 dimensional world
		//CAMERA_PROJECTION_ORTHOGRAPHIC: to render 2d world
		void setCameraProjectionType(ZSPROJECTIONTYPE type);
		//Sets Far and Near plane to render
		void setCameraZPlanes(float znear, float zfar);
		//Sets FOV to camera in degrees
		void setCameraFOV(float nfov);

		void setCameraProjectionResolution(float WIDTH, float HEIGHT);

		void updateCameraMatrix();
		//Sets camera pos in 3 dimensional space
		void setCameraPosition(ZSVECTOR3 position);
		void setCameraTarget(ZSVECTOR3 target);

		ZSMATRIX4x4 getCameraProjectionMatrix();
		ZSMATRIX4x4 getCameraViewMatrix();

		void setCameraMode(ZSCAMERAMODE mode);

		ZSVECTOR2 getCameraResolution();
	}
}