#define _CRT_SECURE_NO_WARNINGS

#include "../includes/zs-math.h"

//GLEW
#ifdef _WIN32
#include <glew.h>
#endif

#ifdef __linux__
#include <GL/glew.h>
#endif

#include "../includes/zs-texture.h"
#include "stdio.h"
#include "string.h"
#include "math.h"
#include "stdlib.h"

#ifdef __linux__
#include "wchar.h"
#endif

#include "../includes/zs-shader.h"

#include "../includes/zs-text-renderer.h"

unsigned int scr_width;
unsigned int scr_height;

void ZSpire::setLocalScreenSize(unsigned int width, unsigned int height) {
	scr_width = width;
	scr_height = height;

}

unsigned int tindices[] = {
	0, 1, 3, // first triangle
	1, 2, 3  // second triangle
};

float font_scale = 1;
GLint font_texture_id = 0;

Character glyphs[2000];

bool ZSpire::LoadGlyphes(const char* texture, const char* glyph_map, float scale) {
	font_scale = scale;

	ZSVERTEX gv[4];

	Texture font_texture;
	font_texture.LoadDDSFromFile(texture);
	//printf("%d", font_texture.getTextureGL_ID());
	
	unsigned int wh = font_texture.properties.WIDTH;
	font_texture_id = font_texture.getTextureGL_ID();
	FILE* glmap = fopen(glyph_map, "r");
	if (glmap == NULL) {

		return false;
	}
	else {

		while (true) {
			char header[120];
			int step = fscanf(glmap, "%s", header);
			if (step == EOF) break;
			if (strcmp(header, "char") == 0) {

				char symbol_id[30];
				char symbol_start_x[30];
				char symbol_start_y[30];

				char symbol_width[30];
				char symbol_height[30];

				char symbol_x_offs[30];
				char symbol_y_offset[30];
				char symbol_x_advance[30];

				char symbol_page[30];
				char symbol_channel[30];

				double x1 = 0;
				double y1 = 0;
				double x2 = 0;
				double y2 = 0;

				int charPos = 0;

				fscanf(glmap, "%s %s %s %s %s %s %s %s %s %s", symbol_id, symbol_start_x, symbol_start_y, symbol_width, symbol_height, symbol_x_offs, symbol_y_offset, symbol_x_advance, symbol_page, symbol_channel);

				charPos = atoi(symbol_id + 3);
				x1 = atof(symbol_start_x + 2);
				y1 = atof(symbol_start_y + 2);

				x2 = atof(symbol_width + 6);
				y2 = atof(symbol_height + 7);

				x2 += x1;
				y2 += y1;

				glyphs[charPos].sizeX = (float)fabs(x2 - x1);
				glyphs[charPos].sizeY = (float)fabs(y2 - y1);

				glyphs[charPos].step_before = (float)atof(symbol_x_offs + 8);
				glyphs[charPos].step = (float)atof(symbol_x_advance + 9);
				glyphs[charPos].offset_y = (float)atof(symbol_y_offset + 8);

				//Right up corner 1
				gv[0] = ZSVERTEX(ZSVECTOR3(glyphs[charPos].sizeX * scale, glyphs[charPos].sizeY * scale, 1.0f), ZSVECTOR2((float)(x2 / wh), (float)(y1 / wh)));
				//Right down corner 2
				gv[1] = ZSVERTEX(ZSVECTOR3(glyphs[charPos].sizeX * scale, 0, 1.0f), ZSVECTOR2((float)(x2 / wh), (float)(y2 / wh)));
				//Left down corner 3
				gv[2] = ZSVERTEX(ZSVECTOR3(0, 0, 1.0f), ZSVECTOR2((float)(x1 / wh), (float)(y2 / wh)));
				//Left up corner 4
				gv[3] = ZSVERTEX(ZSVECTOR3(0, glyphs[charPos].sizeY * scale, 1.0f), ZSVECTOR2((float)(x1 / wh), (float)(y1 / wh)));



				//Generating 2D text
				glGenVertexArrays(1, &glyphs[charPos].VAO);
				glGenBuffers(1, &glyphs[charPos].VBO);
				glGenBuffers(1, &glyphs[charPos].EBO);

				glBindVertexArray(glyphs[charPos].VAO);
				glBindBuffer(GL_ARRAY_BUFFER, glyphs[charPos].VBO);

				glBufferData(GL_ARRAY_BUFFER, sizeof(gv), gv, GL_STATIC_DRAW);

				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, glyphs[charPos].EBO);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(tindices), tindices, GL_STATIC_DRAW);

				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(ZSVERTEX), (void*)0);
				glEnableVertexAttribArray(0);

				glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(ZSVERTEX), (void*)(sizeof(float) * 3));
				glEnableVertexAttribArray(1);
				glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(ZSVERTEX), (void*)(sizeof(float) * 5));
				glEnableVertexAttribArray(2);

				glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(ZSVERTEX), (void*)(sizeof(float) * 8));
				glEnableVertexAttribArray(3);
				glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(ZSVERTEX), (void*)(sizeof(float) * 11));
				glEnableVertexAttribArray(4);
			}


		}

	}

	return true;
}


void ZSpire::DrawLetter(unsigned int letter, Shader text_shader, float step) {
	text_shader.setUniformFloat("step", step);
	text_shader.setUniformFloat("offset_y", glyphs[letter].offset_y);
	glBindVertexArray(glyphs[letter].VAO);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void ZSpire::DrawString(const wchar_t* text, Shader text_shader, float pos_x, float pos_y, ZSRGBCOLOR color) {
	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	float step_x_passed = 0;
	text_shader.Use();
	//Sending required information to shader

	text_shader.setUniformInt("res_x", (int)scr_width);
	text_shader.setUniformInt("res_y", (int)scr_height);

	text_shader.setUniformFloat("posT_x", pos_x);
	text_shader.setUniformFloat("posT_y", pos_y);

	text_shader.setUniformColor3("textColor", color);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, font_texture_id);
	unsigned int len = (unsigned int)wcslen(text);
	for (unsigned int i = 0; i < len; i++) {
		if (text[i] != L' ') {
			step_x_passed += glyphs[text[i]].step_before;
			DrawLetter(text[i], text_shader, step_x_passed);
			step_x_passed += glyphs[text[i]].step;
		}
		else {
			step_x_passed += 30;
		}
	}
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
}




void ZSpire::DrawString(const wchar_t* text, float pos_x, float pos_y, ZSRGBCOLOR color) {
	//dshaders::Shader text_shader = dshaders::getTextShader();
	//DrawString(text, text_shader, pos_x, pos_y, color);
}

unsigned int ZSpire::GetStringLength(wchar_t* text) {


	unsigned int step_x_passed = 0;

	unsigned int len = (unsigned int)wcslen(text);
	for (unsigned int i = 0; i < len; i++) {
		if (text[i] != L' ') {
			step_x_passed += (unsigned int)glyphs[text[i]].step_before;
			step_x_passed += (unsigned int)glyphs[text[i]].step;
		}
		else {
			step_x_passed += 30;
		}
	}
	return step_x_passed;
}

unsigned int ZSpire::GetMaximumLetterHeight(wchar_t* text) {

	unsigned int result = 0;

	for (unsigned int i = 0; i < wcslen(text); i++) {
		if (glyphs[text[i]].sizeY > result) {
			result = (unsigned int)glyphs[text[i]].sizeY;
		}
	}

	return result;
}