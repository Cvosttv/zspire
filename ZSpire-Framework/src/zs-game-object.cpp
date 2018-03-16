#include "string.h"

#include "../includes/zs-math.h"
#include "../includes/zs-mesh.h"
#include "../includes/zs-transform.h"
#include "../includes/zs-texture.h"

#include "../includes/zs-game-object.h"

void ZSpire::GameObject::setPosition(ZSVECTOR3 pos) {
	transform.setPosition(pos);
	transform.updateMatrix();
}
void ZSpire::GameObject::setScale(ZSVECTOR3 scale) {
	transform.setScale(scale);
	transform.updateMatrix();
}
void ZSpire::GameObject::setRotation(ZSVECTOR3 rotation) {
	transform.setRotation(rotation);
	transform.updateMatrix();
}

void ZSpire::GameObject::setMesh(Mesh* mesh) {
	this->mesh = mesh;
	hasMesh = true;
}

void ZSpire::GameObject::setDiffuseTexture(Texture* texture) {
	this->diffuse_texture = texture;
	hasTextureDiffuse = true;
}

void ZSpire::GameObject::Draw() {

	if(hasTextureDiffuse == true)
	diffuse_texture->Use(0);

	if(hasMesh == true)
	mesh->Draw();
}

ZSpire::Transform* ZSpire::GameObject::getTransform() {
	return &this->transform;
}

void ZSpire::GameObject::setLabel(const char* label) {
	strcpy_s(this->label, label);
}

char* ZSpire::GameObject::getLabel() {
	return this->label;
}