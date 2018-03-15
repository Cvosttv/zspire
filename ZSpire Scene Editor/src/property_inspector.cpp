typedef unsigned int uint;
#include "imgui.h"
#include <SDL.h>
#include <vector>

#include "../includes/DMath.h"
#include "../includes/Camera.hpp"
#include "../includes/DColor.h"
#include "../includes/Light.h"
#include "../includes/GameObject.h"
#include "../includes/property_inspector.h"

int selected_gameobject = -1;

static bool alpha_preview = true;
static bool alpha_half_preview = false;
static bool options_menu = true;
static bool hdr = false;

int misc_flags = (hdr ? ImGuiColorEditFlags_HDR : 0) | (alpha_half_preview ? ImGuiColorEditFlags_AlphaPreviewHalf : (alpha_preview ? ImGuiColorEditFlags_AlphaPreview : 0)) | (options_menu ? 0 : ImGuiColorEditFlags_NoOptions);

void DEWindows::DrawInspectorWindow(SDL_Window* window){

	ImGui::Begin("Properties"); // создаём окно

	if(selected_gameobject >= 0){
		GameObject* obj = getObjectPtr(selected_gameobject);

		ImGui::InputText("Label", obj->label, 255);
		
		float translation[3] = { obj->transform.pos.x, obj->transform.pos.y, obj->transform.pos.z };
		float scale[3] = { obj->transform.scale.x, obj->transform.scale.y, obj->transform.scale.z };
		float rotation[3] = { obj->transform.rotation.x, obj->transform.rotation.y, obj->transform.rotation.z };

		ImGui::Separator();

		ImGui::InputFloat3("Translation", translation);
		ImGui::InputFloat3("Scale", scale);
		ImGui::InputFloat3("Rotation", rotation);

		obj->transform.pos = Vector3(translation[0], translation[1], translation[2]);
		obj->transform.scale = Vector3(scale[0], scale[1], scale[2]);
		obj->transform.rotation = Vector3(rotation[0], rotation[1], rotation[2]);
	
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

	ImGui::End(); // end window
}

void DEWindows::Inspector::selectObject(uint obj_to_select){
	selected_gameobject = (int)obj_to_select;
}