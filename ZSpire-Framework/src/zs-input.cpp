
#include "../includes/zs-input.h"

int pressed_keys[MAX_KEYS];

int keys_pressed_amount = 0;

ZSpire::MouseState mouse_state;

void ZSpire::addKeyToQueue(int KEY) {

	if (keys_pressed_amount <= MAX_KEYS) {

		pressed_keys[keys_pressed_amount] = KEY;

		keys_pressed_amount += 1;

	}
}

bool ZSpire::isKeyPressed(int KEY) {
	if (keys_pressed_amount > 0) {
		for (int i = 0; i < keys_pressed_amount; i++) {

			if (pressed_keys[i] == KEY) return true;
		}
	}
	return false;
}

void ZSpire::clearQueue() {
	keys_pressed_amount = 0;
}

ZSpire::MouseState* ZSpire::getMouseState() {
	return &mouse_state;
}

void ZSpire::setMouseStateXYPOSvalue(unsigned int x, unsigned int y){

	mouse_state.x = x;
	mouse_state.y = y;
}

void ZSpire::setMouseStateLeftButtonDownBool(bool left_down) {
	mouse_state.LEFT_BTN_DOWN = left_down;
}

void ZSpire::setMouseStateRightButtonDownBool(bool right_down) {
	mouse_state.RIGHT_BTN_DOWN = right_down;
}

void ZSpire::setMouseStateWheelButtonDownBool(bool wheel_down) {
	mouse_state.RIGHT_BTN_DOWN = wheel_down;
}