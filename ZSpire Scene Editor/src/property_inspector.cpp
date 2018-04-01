#define _CRT_SECURE_NO_WARNINGS


#include "imgui.h"
#include <SDL.h>
#include <vector>

#include "../includes/zs-math.h"
#include "../includes/Camera.hpp"
#include "../includes/Light.h"
#include "../includes/zs-transform.h"
#include "../includes/GameObject.h"
#include "../includes/property_inspector.h"

#include "../includes/zs-mesh-loader.h"

int selected_gameobject = NON_SHOWING;
int selected_mesh = NON_SHOWING;
int selected_texture = NON_SHOWING;
int selected_light = NON_SHOWING;

static bool alpha_preview = true;
static bool alpha_half_preview = false;
static bool options_menu = true;
static bool hdr = false;

char resource_prev_path[64];

int misc_flags = (hdr ? ImGuiColorEditFlags_HDR : 0) | (alpha_half_preview ? ImGuiColorEditFlags_AlphaPreviewHalf : (alpha_preview ? ImGuiColorEditFlags_AlphaPreview : 0)) | (options_menu ? 0 : ImGuiColorEditFlags_NoOptions);

void ZSWindows::DrawInspectorWindow(SDL_Window* window){

	ImGui::Begin("Properties"); // создаём окно

	if (selected_gameobject >= 0) {
		GameObject* obj = getObjectPtr(selected_gameobject);

		ImGui::InputText("Label", obj->label, 255);

		float translation[3] = { obj->transform._getPosition().X, obj->transform._getPosition().Y, obj->transform._getPosition().Z };
		float scale[3] = { obj->transform._getScale().X, obj->transform._getScale().Y, obj->transform._getScale().Z };
		float rotation[3] = { obj->transform._getRotation().X, obj->transform._getRotation().Y, obj->transform._getRotation().Z };

		ImGui::Separator();

		ImGui::InputFloat3("Translation", translation);
		ImGui::InputFloat3("Scale", scale);
		ImGui::InputFloat3("Rotation", rotation);

		obj->transform.setPosition(ZSVECTOR3(translation[0], translation[1], translation[2]));
		obj->transform.setScale(ZSVECTOR3(scale[0], scale[1], scale[2]));
		obj->transform.setRotation(ZSVECTOR3(rotation[0], rotation[1], rotation[2]));

		obj->transform.updateMatrix();

		ImGui::Separator();
		ImGui::InputText("Diffuse Texture string", obj->dtexture_name, 64);
		ImGui::InputText("Normal Texture string", obj->ntexture_name, 64);

		
		ImGui::Separator();
		ImGui::InputText("Mesh string", obj->mesh_name, 64);
		ImGui::InputInt("Mesh index", &obj->meshIndex, 1);

	
		RefreshObjectData(selected_gameobject);
		
		if (ImGui::Button("Delete") == true) {
			obj->deleted = true;
			selected_gameobject = NON_SHOWING;
		}
		
	}

	if (selected_texture >= 0) {
		TextureResource* obj = getTextureAt(selected_texture);

		strcpy(resource_prev_path, obj->file_path);

		ImGui::InputText("Label", obj->name, 64);
		ImGui::InputText("Path", obj->file_path, 128);
		ImGui::InputText("Pack file", obj->file_to_write_path, 128);

		ImGui::InputFloat("Max Anisotropy", &obj->texture.params.max_anisotropy, 1);

		obj->texture.setTextureParams();

		if (strcmp(resource_prev_path, obj->file_path) == 0) {

			FILE* test = fopen(obj->file_path, "r");
			if (test != NULL && obj->isLoaded == false) { //File exists
				obj->texture.LoadDDSFromFile(obj->file_path);
				obj->isLoaded = true;
				RefreshObjectsData();
			}
		if(test != NULL)
			fclose(test);
		}

		if (ImGui::Button("Delete") == true) {
			obj->isRemoved = true;
			selected_texture = NON_SHOWING;
			RefreshObjectsData();
		}

	}

	if (selected_mesh >= 0) {
		MeshResource* obj = getMeshAt(selected_mesh);

		strcpy(resource_prev_path, obj->file_path);

		ImGui::InputText("Label", obj->name, 64);
		ImGui::InputText("Path", obj->file_path, 128);
		ImGui::InputText("Pack file", obj->file_to_write_path, 128);
		//If has changed
		if (strcmp(resource_prev_path, obj->file_path) == 0) {
			
			FILE* test = fopen(obj->file_path, "r");
			if(test != NULL && obj->isLoaded == false){ //File exists
				obj->meshes = ZSpire::LoadMeshesFromFile(obj->file_path);
				obj->isLoaded = true;
				RefreshObjectsData();
			}
			if (test != NULL)
			fclose(test);
		}

		if (ImGui::Button("Delete") == true) {
			obj->isRemoved = true;
			selected_mesh = NON_SHOWING;
			RefreshObjectsData();
		}
	}

	if (selected_light >= 0) {

		Light* obj = getLightPtr(selected_light);

		ImGui::InputText("Label", obj->label, 255);

		float translation[3] = { obj->pos.X, obj->pos.Y, obj->pos.Z };

		ImGui::Separator();

		ImGui::InputFloat3("Translation", translation);

		obj->pos = ZSVECTOR3(translation[0], translation[1], translation[2]);

		float color[3] = { (float)obj->light_color.r / 256, (float)obj->light_color.g / 256, (float)obj->light_color.b / 256 };

		ImGui::ColorEdit3("Light Color##1", color, misc_flags);
		
		obj->light_color.r = (int)(color[0] * 256);
		obj->light_color.g = (int)(color[1] * 256);
		obj->light_color.b = (int)(color[2] * 256);

		if (ImGui::Button("Delete") == true) {
			obj->deleted = true;
			selected_light = NON_SHOWING;
		}

		
	}
	ImGui::End(); // end window
}

void ZSWindows::Inspector::selectLight(unsigned int light_to_select){
	
	selected_light = (int)light_to_select;
	selected_gameobject = NON_SHOWING;
	selected_texture = NON_SHOWING;
	selected_mesh = NON_SHOWING;
	
}

void ZSWindows::Inspector::selectObject(unsigned int obj_to_select){
	selected_gameobject = (int)obj_to_select;
	selected_texture = NON_SHOWING;
	selected_mesh = NON_SHOWING;
	selected_light = NON_SHOWING;
}

void ZSWindows::Inspector::selectTexture(unsigned int texture_to_select){
	selected_gameobject = NON_SHOWING;
	selected_texture = (int)texture_to_select;
	selected_mesh = NON_SHOWING;
	selected_light = NON_SHOWING;
}

void ZSWindows::Inspector::selectMesh(unsigned int mesh_to_select) {
	selected_gameobject = NON_SHOWING;
	selected_texture = NON_SHOWING;
	selected_mesh = (int)mesh_to_select;
	selected_light = NON_SHOWING;
}