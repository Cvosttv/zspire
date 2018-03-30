#define ZS_App

#include "string.h"
#include <zspire.h>

ZSpire::ZSpireApp app;

ZSpire::Texture texture;
ZSpire::Shader shader;
ZSpire::Shader text_shader;

ZSpire::Shader deffered_object_shader;
ZSpire::Shader deffered_light_shader;


ZSpire::Transform transform;

ZSpire::Scene scene;

ZSpire::AudioSource asurce;


int main() {

	ZSpire::ZSWindowDesc dec;
	dec.WIDTH = 1280;
	dec.HEIGHT = 720;
	dec.isResizable = false;
	strcpy(dec.WINDOW_TITLE , "Demo");
	dec.isFullscreen = false;
	dec.isVsyncEnabled = true;
	dec.OGL_VERSION = OPENGL4_6;

	if (!app.createWindow(dec)) {
		app.MSGBox("Failed to launch engine!", "Cant create engine instance");
	}
	
	ZSpire::createPlane2D();

	if(!ZSpire::InitOpenAL_Device())app.MSGBox("TEST", "test");


	ZSpire::LoadGlyphes("text/glyph48.DDS", "text/glyph48.fnt");

	//texture.InitializeTexture();
	//texture.LoadDDSFromFile("ext_road_night.DDS");

	shader.InitializeShader();
	shader.compileFromFile("shaders/object.vs", "shaders/object.fs");

	text_shader.InitializeShader();
	text_shader.compileFromFile("shaders/text/text2d.vs", "shaders/text/text2d.fs");

	deffered_object_shader.InitializeShader();
	deffered_object_shader.compileFromFile("shaders/object.vs", "shaders/deffered/object.fs");

	deffered_light_shader.InitializeShader();
	deffered_light_shader.compileFromFile("shaders/deffered/lighting.vs", "shaders/deffered/lighting.fs");



	asurce.Open("test.wav");

	
	ZSpire::ZSLOADEDMESHINFO inf;

	transform.setPosition(ZSVECTOR3(1,0,0));
	transform.updateMatrix();

	ZSpire::LoadSceneFromFile("scene.scn", &scene);
	//ZSpire::ForwardRender::setForwardObjectShader(&shader);
	ZSpire::DefferedRender::Init_gBuffer();
	ZSpire::DefferedRender::setDefferedShaders(&deffered_object_shader, &deffered_light_shader);

	//scene.getObjectAt(1)->setMesh(&mesh2[0]);
	//scene.getObjectAt(1)->setDiffuseTexture(&texture);
	
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
			ZSpire::ZSWindowDesc wd;
			wd.WIDTH = 1600;
			wd.HEIGHT = 900;

		//	app.setWindowProperties(wd);
		}

		app.gl_clear();

		shader.Use();
		shader.setTransform(&transform);

		//ZSpire::getPlaneMesh2D()->Draw();

		ZSpire::DrawString(L"abcdefgh test", text_shader, 100, 100, ZSRGBCOLOR(255,255,0));

	//	ZSpire::ForwardRender::RenderSceneForward(&scene);
		ZSpire::DefferedRender::RenderScene(&scene);

		app.postFrame();

		ZSpire::clearQueue();
	}

	app.ZSDestroyWindow();
}
