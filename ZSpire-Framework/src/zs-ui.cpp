#define _CRT_SECURE_NO_WARNINGS

#include "../includes/zs-ui.h"

#include "../includes/zs-mesh.h"

#include "../includes/zs-camera.h"

#include "../includes/zs-text-renderer.h"

#include <wchar.h>

ZSpire::Shader* ui_shader;
ZSpire::Shader* text_shader;

ZSpire::Transform* ZSpire::UI::SpriteUI::getTransform() {
	return &transform;
}

void ZSpire::UI::SpriteUI::setTexture(Texture* texture){
	this->texture = texture;
}

void ZSpire::UI::SpriteUI::setSize(ZSVECTOR2 size) {
	transform.setScale(ZSVECTOR3(size.X, size.Y, 1.0f));
	transform.updateMatrix();
}
void ZSpire::UI::SpriteUI::setPosition(ZSVECTOR2 pos) {
	transform.setPosition(ZSVECTOR3(pos.X, pos.Y, 0.0f));
	transform.updateMatrix();
}
//Button
void ZSpire::UI::ButtonUI::setText(const wchar_t* text){
	wcscpy(this->text, text);
	this->text_len = ZSpire::GetStringLength(text);
	this->text_max_h = ZSpire::GetMaximumLetterHeight(text);
}
void ZSpire::UI::ButtonUI::setTextColor(ZSRGBCOLOR text_color){
	this->text_color = text_color;
}
void ZSpire::UI::ButtonUI::setTexture(Texture* texture){
	this->sprite.setTexture(texture);
}
void ZSpire::UI::ButtonUI::setPosition(ZSVECTOR2 pos){
	this->sprite.setPosition(pos);
	this->pos = pos;
}
void ZSpire::UI::ButtonUI::setSize(ZSVECTOR2 size){
	this->sprite.setSize(size);
	this->size = size;
}
void ZSpire::UI::ButtonUI::Draw(){
	this->sprite.Draw();
	ZSpire::DrawString(text, *text_shader, pos.X + size.X / 2  - this->text_len / 2, pos.Y + size.Y / 2 - this->text_max_h / 2, text_color);

}

void ZSpire::UI::setShader(Shader* shader){
	ui_shader = shader;
}

void ZSpire::UI::setShaderText(Shader* _text_shader){
	text_shader = _text_shader;
}

void ZSpire::UI::ToggleUI() {

	ui_shader->Use();
	Camera::setCameraMode(CAMERA_MODE_UI);
	ui_shader->updateCamera();
	
}

void ZSpire::UI::SpriteUI::Draw() {
	ui_shader->Use();

	ui_shader->setTransform(getTransform());

	//ui_shader->setUniformFloat("size_x", this->transform.getScale().X);
	//ui_shader->setUniformFloat("size_y", this->transform.getScale().Y);

	//ui_shader->setUniformFloat("pos_x", this->transform.getPosition().X);
	//ui_shader->setUniformFloat("pos_y", this->transform.getPosition().Y);

	texture->Use(0);

	getUiSpriteMesh2D()->Draw();
}