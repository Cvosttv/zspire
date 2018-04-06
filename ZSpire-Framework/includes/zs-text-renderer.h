/*
    text_renderer.h
    Pershades 2017

    Demented Engine Text Renderer
*/

struct Character {
	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;

	float sizeX = 0;
	float sizeY = 0;

	float step_before = 0;
	float step = 0;

	float offset_y = 0;
};

namespace ZSpire {

	void setLocalScreenSize(unsigned int width, unsigned int height);
	bool LoadGlyphes(const char* texture, const char* glyph_map, float scale = 1.0f);
	void DrawLetter(unsigned int letter, Shader text_shader, float step);
	void DrawString(const wchar_t* text, Shader text_shader, float pos_x, float pos_y, ZSRGBCOLOR color);

	void DrawString(const wchar_t* text, float pos_x, float pos_y, ZSRGBCOLOR color);

	unsigned int GetStringLength(const wchar_t* text);

	unsigned int GetMaximumLetterHeight(const wchar_t* text);
}