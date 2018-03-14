#define CAMERA_PROJECTION_PERSPECTIVE 1
#define CAMERA_PROJECTION_ORTHOGRAPHIC 2

typedef unsigned int ZSPROJECTIONTYPE;

namespace ZSpire {

	struct ZSCAMERADESC {
		ZSPROJECTIONTYPE projection_type;
		float FOV;
		float ZNearPlane;
		float ZFarPlane;
		};
		
		
		void InitializeCamera();

		void setCameraProjectionType(ZSPROJECTIONTYPE type);

		void setCameraZPlanes(float znear, float zfar);

		void setCameraFOV(float nfov);

		void setCameraProjectionResolution(float WIDTH, float HEIGHT);

		void updateCameraMatrix();

		ZSMATRIX4x4 getCameraProjectionMatrix();
		ZSMATRIX4x4 getCameraViewMatrix();
}