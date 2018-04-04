#include "../includes/zs-ui.h"

#include "../includes/zs-mesh.h"

void ZSpire::UI::SpriteUI::Draw() {
	texture->Use(0);

	getPlaneMesh2D()->Draw();
}

ZSpire::Transform* ZSpire::UI::SpriteUI::getTransform() {
	return &transform;
}