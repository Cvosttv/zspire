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

ZSpire::AudioSource asurce;

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
	dec.WIDTH = 1280;
	dec.HEIGHT = 720;
	dec.isResizable = false;
	strcpy_s(dec.WINDOW_TITLE , "Demo");
	dec.isFullscreen = true;
	dec.isVsyncEnabled = true;

	if (!app.createWindow(dec)) {
		app.MSGBox("Failed to launch engine!", "Cant create engine instance");
	}
	

	if(!ZSpire::InitOpenAL_Device())app.MSGBox("TEST", "test");


	ZSpire::LoadGlyphes("text/glyph48.DDS", "text/glyph48.fnt");

	texture.InitializeTexture();
	texture.LoadDDSFromFile("ext_road_night.DDS");

	shader.InitializeShader();
	shader.compileFromFile("shaders/object.vs", "shaders/object.fs");

	text_shader.InitializeShader();
	text_shader.compileFromFile("shaders/text/text2d.vs", "shaders/text/text2d.fs");

	asurce.Open("test.wav", true);


	mesh.InitializeMesh();
	mesh.processMesh(vertices,ind, 4, 6);
	
	mesh2 = ZSpire::LoadMeshesFromFile("BIG.FBX");

	transform.setPosition(ZSVECTOR3(1,0,0));
	transform.updateMatrix();

	ZSpire::LoadSceneFromFile("scene.scn", &scene);
	ZSpire::setForwardObjectShader(&shader);


	scene.getObjectAt(1)->setMesh(&mesh2[0]);
	scene.getObjectAt(1)->setDiffuseTexture(&texture);
	
	ZSpire::InitializeCamera();
	ZSpire::setCameraProjectionType(CAMERA_PROJECTION_PERSPECTIVE);
	ZSpire::updateCameraMatrix();

	asurce.Play();
	
	while (true) {

		app.PollEvents();

		ZSpire::MouseState* ms = ZSpire::getMouseState();

		if (ZSpire::isKeyPressed(SDLK_a) == true) {
			app.ZSDestroyWindow();
		}

		if (ms->x > 300) {
		//	app.ZSDestroyWindow();
		}

		app.gl_clear();

		shader.Use();
		shader.setTransform(&transform);

		texture.Use(0);

		mesh.Draw();

		ZSpire::DrawString(L"test", text_shader, 100, 100, ZSRGBCOLOR(0,0,0));

		ZSpire::RenderSceneForward(&scene);

		app.postFrame();

		ZSpire::clearQueue();
	}

	app.ZSDestroyWindow();
}