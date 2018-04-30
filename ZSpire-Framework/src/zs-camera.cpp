

#include "../includes/zs-math.h"

#include "../includes/zs-camera.h"

ZSCAMERAMODE camera_mode;
ZSPROJECTIONTYPE projection_type;

float FOV;
float ZNearPlane;
float ZFarPlane;

float CAMERA_PROJ_WIDTH;
float CAMERA_PROJ_HEIGHT;

ZSVECTOR3 camera_up;
ZSVECTOR3 camera_pos;
ZSVECTOR3 camera_target;
ZSMATRIX4x4 PROJECTION;
ZSMATRIX4x4 VIEW;

ZSMATRIX4x4 PROJECTION_UI;

void ZSpire::Camera::InitializeCamera(){
	FOV = 45.0f;
	ZNearPlane = 0.3f;
	ZFarPlane = 1000.0f;
	projection_type = CAMERA_PROJECTION_ORTHOGRAPHIC;
	camera_mode = CAMERA_MODE_SCENE;
	//Camera View matrix defaults
	camera_up = ZSVECTOR3(0.0f, 1.0f, 0.0f);
	camera_pos = ZSVECTOR3(0.0f, 0.0f, -3.0f);
	camera_target = ZSVECTOR3(0.0f, 0.0f, -1.0f);

	if(CAMERA_PROJ_WIDTH == 0)
		CAMERA_PROJ_WIDTH = 640;
	if(CAMERA_PROJ_HEIGHT == 0)
		CAMERA_PROJ_HEIGHT = 480;
}

void ZSpire::Camera::setCameraProjectionType(ZSPROJECTIONTYPE type) {
	projection_type = type;
}

void ZSpire::Camera::setCameraZPlanes(float znear, float zfar) {
	ZNearPlane = znear;
	ZFarPlane = zfar;
}

void ZSpire::Camera::setCameraFOV(float nfov) {
	FOV = nfov;
}

void ZSpire::Camera::updateCameraMatrix() {
	if (projection_type == CAMERA_PROJECTION_ORTHOGRAPHIC) {
		PROJECTION = getOrthogonal(0, CAMERA_PROJ_WIDTH, 0, CAMERA_PROJ_HEIGHT, ZNearPlane, ZFarPlane);
	}
	else {
		PROJECTION = getPerspective(FOV, CAMERA_PROJ_WIDTH / CAMERA_PROJ_HEIGHT, ZNearPlane, ZFarPlane);
	}

	VIEW = matrixLookAt(camera_pos, camera_target, camera_up);

	PROJECTION_UI = getOrthogonal(0, CAMERA_PROJ_WIDTH, 0, CAMERA_PROJ_HEIGHT);
}

void ZSpire::Camera::setCameraProjectionResolution(float WIDTH, float HEIGHT) {
	CAMERA_PROJ_WIDTH = WIDTH;
	CAMERA_PROJ_HEIGHT = HEIGHT;
}

ZSMATRIX4x4 ZSpire::Camera::getCameraProjectionMatrix(){
	if (camera_mode == CAMERA_MODE_SCENE) {
		return PROJECTION;
	}

	if (camera_mode == CAMERA_MODE_UI) {
		return PROJECTION_UI;
	}
	return getIdentity();
}
ZSMATRIX4x4 ZSpire::Camera::getCameraViewMatrix() {
	if (camera_mode == CAMERA_MODE_SCENE) {
		return VIEW;
	}

	if (camera_mode == CAMERA_MODE_UI) {
		return getIdentity();
	}

	return getIdentity();
}

void ZSpire::Camera::setCameraPosition(ZSVECTOR3 position) {
	camera_pos = position;
}

void ZSpire::Camera::setCameraTarget(ZSVECTOR3 target) {
	camera_target = target;
}

void ZSpire::Camera::setCameraMode(ZSCAMERAMODE mode){
	camera_mode = mode;
}

ZSVECTOR2 ZSpire::Camera::getCameraResolution() {
	return ZSVECTOR2(CAMERA_PROJ_WIDTH, CAMERA_PROJ_HEIGHT);
}