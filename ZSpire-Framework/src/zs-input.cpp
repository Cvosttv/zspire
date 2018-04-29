#include "../includes/zs-input.h"

#include <sdl.h>

int pressed_keys[MAX_KEYS];

int keys_pressed_amount = 0;

ZSpire::Input::MouseState mouse_state;

unsigned int WIN_WIDTH;
unsigned int WIN_HEIGHT;

ZSMOUSEINPUTSTYLE MOUSE_INPUT_STYLE = false;

void ZSpire::Input::setWinWH(unsigned int W, unsigned int H) {
	WIN_WIDTH = W;
	WIN_HEIGHT = H;
}

void ZSpire::Input::addKeyToQueue(int KEY) {

	if (keys_pressed_amount <= MAX_KEYS) {

		pressed_keys[keys_pressed_amount] = KEY;

		keys_pressed_amount += 1;

	}
}

bool ZSpire::Input::isKeyPressed(int KEY) {
	if (keys_pressed_amount > 0) {
		for (int i = 0; i < keys_pressed_amount; i++) {

			if (pressed_keys[i] == KEY) return true;
		}
	}
	return false;
}

void clearMouseState() {
	mouse_state.LEFT_BTN_DOWN = false;
	mouse_state.RIGHT_BTN_DOWN = false;

	mouse_state.relativeX = 0;
	mouse_state.relativeY = 0;

}


void ZSpire::Input::clearQueue() {
	keys_pressed_amount = 0;
	clearMouseState();
}

ZSpire::Input::MouseState* ZSpire::Input::getMouseState() {
	return &mouse_state;
}


void ZSpire::Input::setMouseStateXYPOSvalue(unsigned int x, unsigned int y){

	mouse_state.x = x;
	mouse_state.y = y;
}

void ZSpire::Input::setMouseStateRelativeXYPOSvalue(int x, int y) {
	mouse_state.relativeX = x;
	mouse_state.relativeY = y;
}

void ZSpire::Input::setMouseStateLeftButtonDownBool(bool left_down) {
	mouse_state.LEFT_BTN_DOWN = left_down;
}

void ZSpire::Input::setMouseStateRightButtonDownBool(bool right_down) {
	mouse_state.RIGHT_BTN_DOWN = right_down;
}

void ZSpire::Input::setMouseStateWheelButtonDownBool(bool wheel_down) {
	mouse_state.RIGHT_BTN_DOWN = wheel_down;
}

bool ZSpire::Input::isButtonHoveredByCursor(UI::ButtonUI* button){
	if (mouse_state.x >= button->getTransform()->getPosition().X &&
		mouse_state.x <= button->getTransform()->getPosition().X + button->getTransform()->getScale().X &&
		WIN_HEIGHT - mouse_state.y <= button->getTransform()->getPosition().Y + button->getTransform()->getScale().Y &&
		WIN_HEIGHT - mouse_state.y >= button->getTransform()->getPosition().Y)
		return true;
	return false;
}

bool ZSpire::Input::isButtonClicked(UI::ButtonUI* button){
	if (mouse_state.LEFT_BTN_DOWN == true && isButtonHoveredByCursor(button) == true)
		return true;
	return false;
}

void ZSpire::Input::setMouseInputStyle(ZSMOUSEINPUTSTYLE style) {
	switch (style) {
	case MOUSE_STYLE_NORMAL: {
		MOUSE_INPUT_STYLE = MOUSE_STYLE_NORMAL;
		SDL_SetRelativeMouseMode(SDL_FALSE);
		break;
	}
	case MOUSE_STYLE_RELATIVE: {
		MOUSE_INPUT_STYLE = MOUSE_STYLE_RELATIVE;
		SDL_SetRelativeMouseMode(SDL_TRUE);
		break;
	}
	}
}