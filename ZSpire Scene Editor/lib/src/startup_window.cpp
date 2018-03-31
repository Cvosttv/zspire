#include "imgui.h"
#include <SDL.h>

#include "../includes/scene_loader.h"
#include "../includes/startup_window.h"

void ZSWindows::DrawStartupWindow(SDL_Window * window) {
	ImGui::Begin("Startup Window"); // создаём окно
	char SceneLoadPath[256] = "scene.scn";
	ImGui::InputText("Scene path", SceneLoadPath, 255);

	if (ImGui::Button("Load...")) {

		char buf[512];
		strcpy(buf, "Loading scene - ");
		strcat(buf, SceneLoadPath);
		strcat(buf, " ...");

		//window->setTitle(buf);

		LoadScene(SceneLoadPath);

		//window->setTitle(SceneLoadPath);
	}

	if (ImGui::Button("Create new")) {

		createNewScene(SceneLoadPath);

		
	}

	ImGui::End(); // end window
}
