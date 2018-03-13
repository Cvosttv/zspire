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

	ZSMATRIX4x4 position_mat = getTranslation(position.X, position.Y, position.Z);
	ZSMATRIX4x4 scale_mat = getScale(scale.X, scale.Y, scale.Z);

	ZSMATRIX4x4 rotation_x_mat = getRotationX(rotation.X);
	ZSMATRIX4x4 rotation_y_mat = getRotationY(rotation.Y);
	ZSMATRIX4x4 rotation_z_mat = getRotationZ(rotation.Z);

	ZSMATRIX4x4 result = getIdentity();

	result = result * scale_mat;
	result = result * position_mat;
	result = result * rotation_x_mat;
	result = result * rotation_y_mat;
	result = result * rotation_z_mat;

	translation_matrix = result;
}



