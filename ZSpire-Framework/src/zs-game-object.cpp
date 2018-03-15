
#include "../includes/zs-math.h"
#include "../includes/zs-mesh.h"
#include "../includes/zs-transform.h"
#include "../includes/zs-texture.h"

#include "../includes/zs-game-object.h"

void ZSpire::GameObject::setPosition(ZSVECTOR3 pos) {
	transform.setPosition(pos);
}
void ZSpire::GameObject::setScale(ZSVECTOR3 scale) {
	transform.setScale(scale);
}
void ZSpire::GameObject::setRotation(ZSVECTOR3 rotation) {
	transform.setRotation(rotation);
}

void ZSpire::GameObject::setMesh(Mesh* mesh) {
	this->mesh = mesh;
}

void ZSpire::GameObject::Draw() {

	diffuse_texture->Use(0);

	mesh->Draw();
}

ZSpire::Transform* ZSpire::GameObject::getTransform() {
	return &this->transform;
}