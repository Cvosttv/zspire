#include "../includes/zs-math.h"

#include "../includes/zs-transform.h"

void ZSpire::Transform::setPosition(ZSVECTOR3 pos){
	position = ZSVECTOR3(pos.X, pos.Y, pos.Z);
}

void ZSpire::Transform::setScale(ZSVECTOR3 scale) {
	this->scale = ZSVECTOR3(scale.X, scale.Y, scale.Z);
}

void ZSpire::Transform::setRotation(ZSVECTOR3 rotation) {
	this->rotation = rotation;
}

void ZSpire::Transform::updateMatrix(){

	ZSMATRIX4x4 position_mat = getTranslationMat(position.X, position.Y, position.Z);
	ZSMATRIX4x4 scale_mat = getScaleMat(scale.X, scale.Y, scale.Z);

	ZSMATRIX4x4 rotation_x_mat = getRotationXMat(rotation.X);
	ZSMATRIX4x4 rotation_y_mat = getRotationYMat(rotation.Y);
	ZSMATRIX4x4 rotation_z_mat = getRotationZMat(rotation.Z);

	ZSMATRIX4x4 result = getIdentity();

	result = result * scale_mat;
	result = result * rotation_x_mat;
	result = result * rotation_y_mat;
	result = result * rotation_z_mat;
	result = result * position_mat;
	
	translation_matrix = result;
}


ZSVECTOR3 ZSpire::Transform::getPosition(){
	return position;
}
ZSVECTOR3 ZSpire::Transform::getScale(){
	return scale;
}
ZSVECTOR3 ZSpire::Transform::getRotation() {
	return rotation;
}
