
#include "imgui.h"
#include <SDL.h>
#include <vector>

#include "../includes/zs-math.h"
#include "../includes/Camera.hpp"
#include "../includes/Light.h"
#include "../includes/property_inspector.h"
#include "../includes/zs-transform.h"
#include "../includes/GameObject.h"
#include "../includes/objects_window.h"
#include "../includes/scene_loader.h"



void ZSWindows::DrawObjectListWindow(SDL_Window * window){
	bool show = true;
	ImGui::Begin("Game objects", &show, ImGuiWindowFlags_MenuBar); // создаём окно

	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("Objects"))
		{
			if (ImGui::MenuItem("New Object", "Ctrl+N")) { createNewObject(); }
			ImGui::EndMenu();
		}
		


		if (ImGui::BeginMenu("Scene"))
		{
			if (ImGui::MenuItem("Save Scene", "Ctrl+S")) { saveScene(); }

			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}

	ImGui::BeginChild("Scrolling");
	for (unsigned int n = 0; n < getObjectsAmount(); n++) {
		if (ImGui::Button(getObject(n).label) == true) {
			ZSWindows::Inspector::selectObject(n);
		}

	}

	ImGui::EndChild();

	

	ImGui::End(); // end window


}