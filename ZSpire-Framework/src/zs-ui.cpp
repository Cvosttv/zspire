#define _CRT_SECURE_NO_WARNINGS

#ifdef _WIN32
#include <glew.h>
#endif

#ifdef __linux__
#include <GL/glew.h>
#endif

#include "../includes/zs-ui.h"

#include "../includes/zs-mesh.h"

#include "../includes/zs-camera.h"

#include "../includes/zs-text-renderer.h"

#include "../includes/zs-input.h"

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
	this->text_len = (float)ZSpire::GetStringLength(text);
	this->text_max_h = (float)ZSpire::GetMaximumLetterHeight(text);
}
void ZSpire::UI::ButtonUI::setTextColor(ZSRGBCOLOR text_color){
	this->text_color = text_color;
}
void ZSpire::UI::ButtonUI::setDefaultTexture(Texture* texture){
	this->default_texture = texture;
}
void ZSpire::UI::ButtonUI::setHoveredTexture(Texture* texture) {
	this->hovered_texture = texture;
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
	bool hovered = Input::isButtonHoveredByCursor(this);

	if (!hovered)
		this->sprite.setTexture(default_texture);

	if (hovered && hovered_texture != nullptr)
		this->sprite.setTexture(hovered_texture);

	this->sprite.Draw();
	ZSpire::DrawString(text, *text_shader, ZSVECTOR2(pos.X + size.X / 2  - this->text_len / 2, pos.Y + size.Y / 2 - this->text_max_h / 2), text_color);

}
ZSpire::Transform* ZSpire::UI::ButtonUI::getTransform(){
	return sprite.getTransform();
}

void ZSpire::UI::setShader(Shader* shader){
	ui_shader = shader;
}

void ZSpire::UI::setShaderText(Shader* _text_shader){
	text_shader = _text_shader;
}
//Render UI
void ZSpire::UI::ToggleUI() {

	ui_shader->Use();
	glDisable(GL_CULL_FACE);

	Camera::setCameraMode(CAMERA_MODE_UI);
	ui_shader->updateCamera();
	
}

void ZSpire::UI::SpriteUI::Draw() {
	ui_shader->Use();

	ui_shader->setTransform(getTransform());
	if(texture != nullptr)
	texture->Use(0);

	getUiSpriteMesh2D()->Draw();
}

void ZSpire::UI::TextUI::setText(const wchar_t* text){
	wcscpy(this->text, text);
}
void ZSpire::UI::TextUI::setPosition(ZSVECTOR2 pos){
	this->pos = pos;
}
void ZSpire::UI::TextUI::setTextColor(ZSRGBCOLOR color){
	this->color = color;
}
void ZSpire::UI::TextUI::Draw() {
	ZSpire::DrawString(text, *text_shader, pos, this->color);

}