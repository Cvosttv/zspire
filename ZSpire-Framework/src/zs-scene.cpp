#define _CRT_SECURE_NO_WARNINGS

#include <vector>
#include "stdio.h"

#include "../includes/zs-math.h"

#include "../includes/zs-mesh.h"

#include "../includes/zs-texture.h"

#include "../includes/zs-transform.h"

#include "../includes/zs-game-object.h"

#include "../includes/zs-light.h"

#include "../includes/zs-scene.h"

ZSpire::GameObject* ZSpire::Scene::getObjectAt(unsigned int index){
	return &this->game_objects[index];
}

unsigned int ZSpire::Scene::getObjectsCount() {
	return (unsigned int)game_objects.size();
}

void ZSpire::Scene::addObject(GameObject obj) {
	this->game_objects.push_back(obj);
}

bool ZSpire::LoadSceneFromFile(const char* file_path, Scene* result) {
	FILE* scene_file = fopen(file_path, "rb");
	char header[5];
	fread(header, 1, 4, scene_file);
	
	if (header[0] != 'D' || header[1] != 'S' || header[2] != 'C' || header[3] != 'N') {
		return false;
	}


	while (true) {
		char prefix[120];
		int step = fscanf(scene_file, "%s", prefix);

		if (step == EOF) break;

		
		if (strcmp(prefix, "mes") == 0) {
			char mesh_path[128];
			fscanf(scene_file, "%s", mesh_path);

		}
		if (strcmp(prefix, "obj") == 0) {
			GameObject obj;


			char header0[120];

			while (true) {
				int step = fscanf(scene_file, "%s", header0);

				if (step == EOF || strcmp(header0, "end") == 0) { break; }

				if (strcmp(header0, "str") == 0) {
					char label[120];
					fscanf(scene_file, "%s", label);

					obj.setLabel(label);
				}

				if (strcmp(header0, "_tr") == 0) {
					fseek(scene_file, 1, SEEK_CUR);
					ZSVECTOR3 position;
					fread(&position.X, sizeof(float), 1, scene_file);
					fread(&position.Y, sizeof(float), 1, scene_file);
					fread(&position.Z, sizeof(float), 1, scene_file);

					obj.setPosition(position);

					fseek(scene_file, 1, SEEK_CUR);
				}
				if (strcmp(header0, "_rt") == 0) {
					fseek(scene_file, 1, SEEK_CUR);

					ZSVECTOR3 rotation;

					fread(&rotation.X, sizeof(float), 1, scene_file);
					fread(&rotation.Y, sizeof(float), 1, scene_file);
					fread(&rotation.Z, sizeof(float), 1, scene_file);

					obj.setRotation(rotation);

					fseek(scene_file, 1, SEEK_CUR);
				}
				if (strcmp(header0, "_sc") == 0) {
					fseek(scene_file, 1, SEEK_CUR);
				
					ZSVECTOR3 scale;

					fread(&scale.X, sizeof(float), 1, scene_file);
					fread(&scale.Y, sizeof(float), 1, scene_file);
					fread(&scale.Z, sizeof(float), 1, scene_file);

					obj.setScale(scale);

					fseek(scene_file, 1, SEEK_CUR);
				}


			}
			result->addObject(obj);
		}
	}



	fclose(scene_file);
}

ZSpire::GameObject* ZSpire::Scene::getObjectByLabel(const char* label) {
	for (unsigned int i = 0; i < game_objects.size(); i ++) {
		if (strcmp(game_objects[i].getLabel(), label) == 0) return &game_objects[i];
	}
	return nullptr;
}