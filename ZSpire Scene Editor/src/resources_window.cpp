#define _CRT_SECURE_NO_WARNINGS

#include "imgui.h"
#include <SDL.h>

#include "../includes/zs-math.h"
#include "../includes/geometry.h"
#include "../includes/zs-texture.h"

#include "../includes/Resources.h"
#include "../includes/resources_window.h"


#include "../includes/property_inspector.h"

void ZSWindows::DrawResourcesWindow(SDL_Window * window) {
	bool show = true;
	ImGui::Begin("Game resources", &show, ImGuiWindowFlags_MenuBar); // создаём окно

	unsigned int res_meshes_count = getMeshesCount();
	unsigned int res_textures_count = getTexturesCount();

	if (ImGui::TreeNode("Textures"))
	{
		if (ImGui::Button("(NEW)") == true) {
			TextureResource tr;

			strcpy(tr.name , "texture");

			addTexture(tr);
		}


		for (unsigned int i = 0; i < res_textures_count; i++) {
			if (getTextureAt(i)->isRemoved == false) {
				if (ImGui::Button(getTextureAt(i)->name) == true) {
					ZSWindows::Inspector::selectTexture(i);
				}
			}
		}
		ImGui::TreePop();
	}

	if (ImGui::TreeNode("Meshes"))
	{

		for (unsigned int i = 0; i < res_meshes_count; i++) {
			if (ImGui::Button(getMeshAt(i)->name) == true) {
				ZSWindows::Inspector::selectMesh(i);
			}
		}
		ImGui::TreePop();
	}

	ImGui::End(); // end window


}