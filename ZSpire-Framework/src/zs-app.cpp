#include <SDL.h>

#include "../includes/zs-app.h"

#include <windows.h>
#include <glew.h>

SDL_Window *window;
SDL_GLContext glcontext;

bool ZSpire::ZSpireApp::createWindow(ZSWindowDesc desc){

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
	{
		MessageBox(NULL, "Creating OpenGL 4.6 instance failed! ", TEXT("Error initializing OpenGL 4.6"), MB_OK);
		return false;
	}

	// Setup window
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, NULL);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
	SDL_DisplayMode current;
	SDL_GetCurrentDisplayMode(0, &current);
	window = SDL_CreateWindow(desc.WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, desc.WIDTH, desc.HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	glcontext = SDL_GL_CreateContext(window);
	SDL_GL_SetSwapInterval(1); // Enable vsync

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		MessageBox(NULL, "Creating OpenGL 4.6 instance failed! ", TEXT("Error initializing OpenGL 4.6"), MB_OK);

		return false;
	}

	return true;
}

void ZSpire::ZSpireApp::ZSDestroyWindow() {
	SDL_GL_DeleteContext(glcontext);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void ZSpire::ZSpireApp::MSGBox() {
	MessageBox(NULL, "Unsupported CPU detected!", TEXT("Your CPU doesn't support Streaming SIMD Extensions (SSE2). Engine terminated"), MB_OK);

}

void ZSpire::ZSpireApp::postFrame() {
	SDL_Event event;
	SDL_PollEvent(&event);
	SDL_GL_SwapWindow(window);
}

void ZSpire::ZSpireApp:: gl_clear() {
	glClearColor(1,1,1,1);
	glClear(GL_COLOR_BUFFER_BIT);
}
