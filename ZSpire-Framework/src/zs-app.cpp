#define ZS_Framework
#include "../includes/zspire.h"

#include <SDL.h>
#include <vector>

#include "../includes/zs-math.h"

#include "../includes/zs-transform.h"

#include "../includes/zs-camera.h"

#include "../includes/zs-app.h"



#include "../includes/zs-shader.h"

#include "../includes/zs-text-renderer.h"

#include "../includes/zs-input.h"

#include "../includes/zs-deffered-render.h"

#ifdef _WIN32
#include <windows.h>
#endif


#ifdef _WIN32
#include <glew.h>
#endif

#ifdef __linux__
#include <GL/glew.h>
#endif

#include <GL/gl.h>

#ifdef USE_VULKAN
#include "../includes/zs-vulkan.h"
#endif

SDL_Window *window;
SDL_GLContext glcontext;

bool ZSpire::ZSpireApp::createWindow(ZSWindowDesc desc){

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
	{
		MessageBox(NULL, "Creating OpenGL 4.6 instance failed! ", TEXT("Error initializing OpenGL 4.6"), MB_OK);
		return false;
	}

	setCameraProjectionResolution((float)desc.WIDTH, (float)desc.HEIGHT);
	updateCameraMatrix();
	setLocalScreenSize(desc.WIDTH, desc.HEIGHT);
	DefferedRender::set_gBufferSize(desc.WIDTH, desc.HEIGHT);

#ifdef USE_GL
	// Setup window
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, NULL);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
	if (desc.OGL_VERSION == OPENGL4_6) {
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
	}
	if (desc.OGL_VERSION == OPENGL3_3) {
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	}
	
#endif

#ifdef USE_VULKAN
	ZSpire::Vulkan::InitVulkan();
	ZSpire::Vulkan::InitDevice(0);
#endif

	SDL_DisplayMode current;
	SDL_GetCurrentDisplayMode(0, &current);
	current.refresh_rate = 60;

	int RESIZABLE_FLAG = SDL_WINDOW_RESIZABLE;
	if (desc.isResizable == false) RESIZABLE_FLAG = 0;

	int GPU_API;

#ifdef USE_GL
	GPU_API = SDL_WINDOW_OPENGL;
#endif

#ifdef USE_VULKAN
	GPU_API = SDL_WINDOW_VULKAN;
#endif

	window = SDL_CreateWindow(desc.WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, desc.WIDTH, desc.HEIGHT, GPU_API | RESIZABLE_FLAG);

	if (desc.isFullscreen == true) {
		SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

	}
	glcontext = SDL_GL_CreateContext(window);
	SDL_GL_SetSwapInterval((int)desc.isVsyncEnabled); // Enable vsync

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
#ifdef _WIN32
		MessageBox(NULL, "Creating OpenGL 4.6 instance failed! ", TEXT("Error initializing OpenGL 4.6"), MB_OK);
#endif
		return false;
	}

	return true;
}

void ZSpire::ZSpireApp::ZSDestroyWindow() {
	SDL_GL_DeleteContext(glcontext);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void ZSpire::ZSpireApp::MSGBox(const char* title, const char* message) {
#ifdef _WIN32
	MessageBox(NULL, message, title, MB_OK);
#endif
}

void ZSpire::ZSpireApp::PollEvents() {
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type) {



	case SDL_KEYDOWN: {
		int cc = event.key.keysym.sym;
		addKeyToQueue(cc);
		break;
	}

	case SDL_MOUSEMOTION: {
		setMouseStateXYPOSvalue(event.motion.x, event.motion.y);
		setMouseStateRelativeXYPOSvalue(event.motion.xrel, event.motion.yrel);
			break;
	}

	case SDL_MOUSEBUTTONDOWN: {
		switch (event.button.button) {
		case SDL_BUTTON_LEFT: {
			setMouseStateLeftButtonDownBool(true);
			break;
		}
		case SDL_BUTTON_RIGHT: {
			setMouseStateRightButtonDownBool(true);
			break;
		}
		case SDL_BUTTON_MIDDLE: {
			setMouseStateWheelButtonDownBool(true);
			break;
		}
		}
		break;
	}


	}
}

void ZSpire::ZSpireApp::setWindowProperties(ZSWindowDesc desc) {
	
	unsigned int rWIDTH;
	unsigned int rHeight;

	SDL_DisplayMode DM;
	SDL_GetCurrentDisplayMode(0, &DM);
	auto WIDTH = DM.w;
	auto HEIGHT = DM.h;

	rWIDTH = desc.WIDTH;
	rHeight = desc.HEIGHT;

	SDL_SetWindowSize(window, rWIDTH, rHeight);
	
	setCameraProjectionResolution((float)rWIDTH, (float)rHeight);
	updateCameraMatrix();
	setLocalScreenSize(rWIDTH, rHeight);

	glViewport(0,0, rWIDTH, rHeight);
}

void ZSpire::ZSpireApp::postFrame() {

	SDL_GL_SwapWindow(window);
}

void ZSpire::ZSpireApp:: gl_clear() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

char* ZSpire::ZSpireApp::getGpuNameGL() {

	const GLubyte* renderer = glGetString(GL_RENDERER);
	return (char*)renderer;
}

char* ZSpire::ZSpireApp::getGpuVendorGL() {

	const GLubyte* vendor = glGetString(GL_VENDOR);
	return (char*)vendor;
}