#include "imgui.h"
#include <SDL.h>

#include "../includes/scene_loader.h"
#include "../includes/startup_window.h"

void DEWindows::DrawStartupWindow(SDL_Window * window) {
	ImGui::Begin("Startup Window"); // создаём окно
	char SceneLoadPath[256] = "scene.scn";
	ImGui::InputText("Scene path", SceneLoadPath, 255);

	if (ImGui::Button("Load...")) {

		char buf[512];
		strcpy_s(buf, "Loading scene - ");
		strcat_s(buf, SceneLoadPath);
		strcat_s(buf, " ...");

		//window->setTitle(buf);

		LoadScene(SceneLoadPath);

		//window->setTitle(SceneLoadPath);
	}

	if (ImGui::Button("Create new")) {

		createNewScene(SceneLoadPath);

		
	}

	ImGui::End(); // end window
}