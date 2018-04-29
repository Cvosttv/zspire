#define MAX_KEYS 10

#ifdef ZS_App
enum
{
	SDLK_UNKNOWN = 0,

	SDLK_RETURN = '\r',
	SDLK_ESCAPE = '\033',
	SDLK_BACKSPACE = '\b',
	SDLK_TAB = '\t',
	SDLK_SPACE = ' ',
	SDLK_EXCLAIM = '!',
	SDLK_QUOTEDBL = '"',
	SDLK_HASH = '#',
	SDLK_PERCENT = '%',
	SDLK_DOLLAR = '$',
	SDLK_AMPERSAND = '&',
	SDLK_QUOTE = '\'',
	SDLK_LEFTPAREN = '(',
	SDLK_RIGHTPAREN = ')',
	SDLK_ASTERISK = '*',
	SDLK_PLUS = '+',
	SDLK_COMMA = ',',
	SDLK_MINUS = '-',
	SDLK_PERIOD = '.',
	SDLK_SLASH = '/',
	SDLK_0 = '0',
	SDLK_1 = '1',
	SDLK_2 = '2',
	SDLK_3 = '3',
	SDLK_4 = '4',
	SDLK_5 = '5',
	SDLK_6 = '6',
	SDLK_7 = '7',
	SDLK_8 = '8',
	SDLK_9 = '9',
	SDLK_COLON = ':',
	SDLK_SEMICOLON = ';',
	SDLK_LESS = '<',
	SDLK_EQUALS = '=',
	SDLK_GREATER = '>',
	SDLK_QUESTION = '?',
	SDLK_AT = '@',
	/*
	Skip uppercase letters
	*/
	SDLK_LEFTBRACKET = '[',
	SDLK_BACKSLASH = '\\',
	SDLK_RIGHTBRACKET = ']',
	SDLK_CARET = '^',
	SDLK_UNDERSCORE = '_',
	SDLK_BACKQUOTE = '`',
	SDLK_a = 'a',
	SDLK_b = 'b',
	SDLK_c = 'c',
	SDLK_d = 'd',
	SDLK_e = 'e',
	SDLK_f = 'f',
	SDLK_g = 'g',
	SDLK_h = 'h',
	SDLK_i = 'i',
	SDLK_j = 'j',
	SDLK_k = 'k',
	SDLK_l = 'l',
	SDLK_m = 'm',
	SDLK_n = 'n',
	SDLK_o = 'o',
	SDLK_p = 'p',
	SDLK_q = 'q',
	SDLK_r = 'r',
	SDLK_s = 's',
	SDLK_t = 't',
	SDLK_u = 'u',
	SDLK_v = 'v',
	SDLK_w = 'w',
	SDLK_x = 'x',
	SDLK_y = 'y',
	SDLK_z = 'z',

	
};
#endif

#ifndef ZSUI
#include "zs-ui.h"
#endif

typedef unsigned int ZSMOUSEINPUTSTYLE;
#define MOUSE_STYLE_NORMAL 0
#define MOUSE_STYLE_RELATIVE 1

namespace ZSpire {
	namespace Input {
		struct MouseState {
			unsigned int x;
			unsigned int y;

			int relativeX;
			int relativeY;

			bool LEFT_BTN_DOWN = false;
			bool RIGHT_BTN_DOWN = false;
		};


		void setWinWH(unsigned int W, unsigned int H);

		void addKeyToQueue(int KEY);
		bool isKeyPressed(int KEY);
		void clearQueue();
		MouseState* getMouseState();

		bool isButtonHoveredByCursor(UI::ButtonUI* button);
		bool isButtonClicked(UI::ButtonUI* button);

		void setMouseStateXYPOSvalue(unsigned int x, unsigned int y);
		void setMouseStateRelativeXYPOSvalue(int x, int y);
		void setMouseStateLeftButtonDownBool(bool left_down);
		void setMouseStateRightButtonDownBool(bool right_down);
		void setMouseStateWheelButtonDownBool(bool wheel_down);

		void setMouseInputStyle(ZSMOUSEINPUTSTYLE style);
	}
}