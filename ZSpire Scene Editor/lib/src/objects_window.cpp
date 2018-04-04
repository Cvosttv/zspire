
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
			if (ImGui::MenuItem("New Light", "Ctrl+N+L")) { createNewLight(); }
			ImGui::EndMenu();
		}
		


		if (ImGui::BeginMenu("Scene"))
		{
			if (ImGui::MenuItem("Save Scene", "Ctrl+S")) { saveScene(); }

			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}
	if (ImGui::TreeNode("Objects"))
	{
		for (unsigned int n = 0; n < getObjectsAmount(); n++) {
			if (getObjectPtr(n)->deleted == false) {
				if (ImGui::Button(getObjectPtr(n)->label) == true) {
					ZSWindows::Inspector::selectObject(n);
				}
			}
		}

		ImGui::TreePop();
	}
	
	if (ImGui::TreeNode("Lights"))
	{
		for (unsigned int n = 0; n < getLightsAmount(); n++) {
			if (getLightPtr(n)->deleted == false) {
				if (ImGui::Button(getLightPtr(n)->label) == true) {
					ZSWindows::Inspector::selectLight(n);
				}
			}
		}


		ImGui::TreePop();
	}

	ImGui::End(); // end window


}