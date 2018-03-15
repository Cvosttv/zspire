#define ZS_App

#include "string.h"
#include <zspire.h>

ZSpire::ZSpireApp app;

ZSpire::Texture texture;
ZSpire::Shader shader;
ZSpire::Shader text_shader;
ZSpire::Mesh mesh;

ZSpire::Mesh* mesh2;

ZSpire::Transform transform;

ZSpire::Scene scene;

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
	dec.isResizable = false;
	strcpy_s(dec.WINDOW_TITLE , "Demo");

	dec.isVsyncEnabled = true;

	if (!app.createWindow(dec)) {
		app.MSGBox();
	}
	
	ZSpire::LoadGlyphes("text/glyph48.DDS", "text/glyph48.fnt");

	texture.InitializeTexture();
	texture.LoadDDSFromFile("ext_road_night.DDS");

	shader.InitializeShader();
	shader.compileFromFile("shaders/object.vs", "shaders/object.fs");

	text_shader.InitializeShader();
	text_shader.compileFromFile("shaders/text/text2d.vs", "shaders/text/text2d.fs");

	mesh.InitializeMesh();
	mesh.processMesh(vertices,ind, 4, 6);
	
	mesh2 = ZSpire::LoadMeshesFromFile("BIG.FBX");

	transform.setPosition(ZSVECTOR3(1,0,0));
	transform.updateMatrix();

	ZSpire::LoadSceneFromFile("scene.scn", &scene);
	ZSpire::setObjectShader(&shader);


	scene.getObjectAt(0)->setPosition(ZSVECTOR3(13,2,9));
	scene.getObjectAt(0)->setScale(ZSVECTOR3(0.005f, 0.005f, 0.005f));
	scene.getObjectAt(0)->setMesh(&mesh2[0]);
	scene.getObjectAt(0)->setTexture(&texture);
	
	ZSpire::InitializeCamera();
	ZSpire::setCameraProjectionType(CAMERA_PROJECTION_PERSPECTIVE);
	ZSpire::updateCameraMatrix();

	while (true) {
		
		app.gl_clear();

		shader.Use();
		shader.setTransform(&transform);

		texture.Use(0);

		mesh.Draw();
		//mesh2->Draw();

		ZSpire::DrawString(L"test", text_shader, 100, 100, ZSRGBCOLOR(0,0,0));

		ZSpire::RenderScene(&scene);

		app.postFrame();
	}

	app.ZSDestroyWindow();
}