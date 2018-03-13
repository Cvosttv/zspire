#define ZS_App

#include "string.h"
#include <zspire.h>

ZSpire::ZSpireApp app;

ZSpire::Texture texture;
ZSpire::Shader shader;
ZSpire::Mesh mesh;
ZSpire::Transform transform;

ZSVERTEX vertices[] = {
	// positions              // texture coords
	ZSVERTEX(ZSVECTOR3(0.5f,  0.5f, 0.0f), ZSVECTOR2( 1.0f, 1.0f)),   // top right
	ZSVERTEX(ZSVECTOR3(0.5f, -0.5f, 0.0f),    ZSVECTOR2(1.0f, 0.0f) ),   // bottom right
	ZSVERTEX(ZSVECTOR3(-0.5f, -0.5f, 0.0f),    ZSVECTOR2(0.0f, 0.0f)),   // bottom left
	ZSVERTEX (ZSVECTOR3(-0.5f,  0.5f, 0.0f),   ZSVECTOR2(0.0f, 1.0f ))   // top left 
};

unsigned int ind[] = {0,1,2, 0,2,3};

int main() {

	ZSpire::ZSWindowDesc dec;
	dec.WIDTH = 800;
	dec.HEIGHT = 600;
	strcpy_s(dec.WINDOW_TITLE , "Demo");

	if (!app.createWindow(dec)) {
		app.MSGBox();
	}
	
	texture.InitializeTexture();
	texture.LoadDDSFromFile("ext_road_night.DDS");

	shader.InitializeShader();
	shader.compileFromFile("shaders/object.vs", "shaders/object.fs");

	mesh.InitializeMesh();
	mesh.processMesh(vertices,ind, 4, 6);

	transform.setPosition(ZSVECTOR3(1,0,0));
	transform.updateMatrix();

	while (true) {
		
		app.gl_clear();

		shader.Use();
		shader.setTransform(transform);

		texture.Use(0);

		mesh.Draw();

		app.postFrame();
	}

	app.ZSDestroyWindow();
}