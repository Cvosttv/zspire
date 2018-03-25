typedef unsigned int uint;
#include "imgui.h"
#include <SDL.h>
#include <vector>

#include "../includes/zs-math.h"
#include "../includes/Camera.hpp"
#include "../includes/Light.h"
#include "../includes/zs-transform.h"
#include "../includes/GameObject.h"
#include "../includes/property_inspector.h"

#include "../includes/zs-texture.h"
#include "../includes/geometry.h"

#include "../includes/Resources.h"

int selected_gameobject = -1;
int selected_mesh = -1;
int selected_texture = -1;

static bool alpha_preview = true;
static bool alpha_half_preview = false;
static bool options_menu = true;
static bool hdr = false;

int misc_flags = (hdr ? ImGuiColorEditFlags_HDR : 0) | (alpha_half_preview ? ImGuiColorEditFlags_AlphaPreviewHalf : (alpha_preview ? ImGuiColorEditFlags_AlphaPreview : 0)) | (options_menu ? 0 : ImGuiColorEditFlags_NoOptions);

void ZSWindows::DrawInspectorWindow(SDL_Window* window){

	ImGui::Begin("Properties"); // создаём окно

	if(selected_gameobject >= 0){
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
	

		ImGui::InputText("Texture string", obj->texture_name, 64);
		/*
		ImGui::Separator();

		ImGui::Checkbox("Is Audio Source", &obj->isAudioSource);
		ImGui::Checkbox("Is Camera", &obj->isCamera);
		ImGui::Checkbox("Is Audio Listener", &obj->isAudioListener);
		ImGui::Checkbox("Is Light", &obj->isLight);

		ImGui::Separator();

		int render_type = 0;

		if (obj->isDefaultRender == true) render_type = 0;
		if (obj->isInstancedRender == true) render_type = 1;
		if (obj->isDefaultRender != true * obj->isInstancedRender != true) render_type = 2;


		ImGui::RadioButton("Default Render", &render_type, 0);
		ImGui::RadioButton("Instanced Render", &render_type, 1);
		ImGui::RadioButton("No Render", &render_type, 2); 

		switch (render_type) {
		case 0: obj->isDefaultRender = true; obj->isInstancedRender = false; break;
		case 1: obj->isDefaultRender = false; obj->isInstancedRender = true; break;
		case 2: obj->isDefaultRender = false; obj->isInstancedRender = false; break;
		}

		ImGui::Separator();

		if (obj->isLight) {
			ImGui::RadioButton("Directional", &obj->light_type, 1);
			ImGui::RadioButton("Point", &obj->light_type, 2);
			ImGui::RadioButton("Spot", &obj->light_type, 3);

			float color[3] = { (float)obj->light.light_color.r / 256, (float)obj->light.light_color.g / 256, (float)obj->light.light_color.b / 256 };

			ImGui::ColorEdit3("Light Color##1", color, misc_flags);

			obj->light.light_color.r = (int)(color[0] * 256);
			obj->light.light_color.g = (int)(color[1] * 256);
			obj->light.light_color.b = (int)(color[2] * 256);
		}

		if (obj->isCamera) {
			ImGui::InputFloat("Z near", &obj->cam.nearPlane);
			ImGui::InputFloat("Z Far", &obj->cam.farPlane);

			ImGui::InputFloat("FOV", &obj->cam.fov);

			ImGui::Checkbox("Cull Faces", &obj->cam.cullFace);
			ImGui::Checkbox("Render Depth", &obj->cam.drawDepth);

		}*/
	}

	if (selected_texture >= 0) {
		TextureResource* obj = getTextureAt(selected_texture);

		ImGui::InputText("Label", obj->name, 64);
		ImGui::InputText("Path", obj->file_path, 128);

		if (ImGui::Button("Delete") == true) {
			obj->isRemoved = true;
			selected_texture = -1;
		}

	}

	if (selected_mesh >= 0) {
		MeshResource* obj = getMeshAt(selected_mesh);

		ImGui::InputText("Label", obj->name, 64);
		ImGui::InputText("Path", obj->file_path, 128);
		ImGui::InputText("Pack file", obj->file_to_write_path, 128);

		if (ImGui::Button("Delete") == true) {
			obj->isRemoved = true;
			selected_mesh = -1;
		}
	}

	ImGui::End(); // end window
}

void ZSWindows::Inspector::selectObject(unsigned int obj_to_select){
	selected_gameobject = (int)obj_to_select;
	selected_texture = -1;
	selected_mesh = -1;
}

void ZSWindows::Inspector::selectTexture(unsigned int texture_to_select){
	selected_gameobject = -1;
	selected_texture = (int)texture_to_select;
	selected_mesh = -1;
}

void ZSWindows::Inspector::selectMesh(unsigned int mesh_to_select) {
	selected_gameobject = -1;
	selected_texture = -1;
	selected_mesh = (int)mesh_to_select;
}