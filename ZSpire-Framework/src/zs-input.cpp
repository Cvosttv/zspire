
#include "../includes/zs-input.h"

int pressed_keys[MAX_KEYS];

int keys_pressed_amount = 0;


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