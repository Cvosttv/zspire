/*
    text_renderer.h
    Pershades 2017

    Demented Engine Text Renderer
*/

struct Character {
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;

	float sizeX = 0;
	float sizeY = 0;

	float step_before = 0;
	float step = 0;

	float offset_y = 0;
};

namespace ZSpire {

	void setLocalScreenSize(uint width, uint height);
	bool LoadGlyphes(const char* texture, const char* glyph_map, float scale = 1.0f);
	//void DrawLetter(uint letter, dshaders::Shader text_shader, float step);
//	void DrawString(const wchar_t* text, dshaders::Shader text_shader, float pos_x, float pos_y, RGBColor color);

	//void DrawString(const wchar_t* text, float pos_x, float pos_y, RGBColor color);

	uint GetStringLength(wchar_t* text);

	uint GetMaximumLetterHeight(wchar_t* text);
}