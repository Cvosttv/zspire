#define _CRT_SECURE_NO_WARNINGS

#include <vector>
#include "stdio.h"

#include "../includes/zs-math.h"

#include "../includes/zs-resource.h"

#include "../includes/zs-mesh.h"

#include "../includes/zs-mesh-loader.h"

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

void ZSpire::Scene::addLight(Light obj) {
	this->lights.push_back(obj);
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

		if (strcmp(prefix, "tex") == 0) {
			ZSResourceDesc rd;

			fscanf(scene_file, "%s %s", rd.label, rd.packFilePath);

			float aniso = 0;

			fseek(scene_file, 1, SEEK_CUR); //Jump over space
			fread(&rd.start_byte, 4, 1, scene_file); //Read 4 bytes (int) 
			fread(&rd.end_byte, 4, 1, scene_file);
			fread(&aniso, 4, 1, scene_file);
			fseek(scene_file, 1, SEEK_CUR); //Jump over \n sign

			Texture texture;
			texture.resource_desc = rd;
			texture.loadFromResourceDesk();
			texture.params.max_anisotropy = aniso;
			texture.setTextureParams();
			result->addTexture(texture);

		}

		if (strcmp(prefix, "mesh") == 0) {
			ZSResourceDesc rd;

			fscanf(scene_file, "%s %s", rd.label, rd.packFilePath);
			fseek(scene_file, 1, SEEK_CUR); //Jump over space
			fread(&rd.start_byte, 4, 1, scene_file); //Read 4 bytes (int) 
			fread(&rd.end_byte, 4, 1, scene_file);
			fseek(scene_file, 1, SEEK_CUR); //Jump over \n sign
			
			ZSLOADEDMESHINFO info;

			Mesh* loaded;
			loaded = LoadMeshesFromResourceDesc(&rd, &info);

			for (unsigned int i = 0; i < info.amount_meshes; i ++) {
				loaded[i].resource_index = i;
				strcpy(loaded[i].resource_string, rd.label);
				result->addMesh(loaded[i]);
			}

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

				if (strcmp(header0, "children") == 0) {
					unsigned int amount;
					
					fscanf(scene_file, "%d", &amount);

					for (unsigned int i = 0; i < amount; i++) {
						char label[120];
						fscanf(scene_file, "%s", label);

						//GameObject*
					}

					
				}

				if (strcmp(header0, "dtex") == 0) {
					char texture_l[120];
					fscanf(scene_file, "%s", texture_l);
					Texture* t = result->findTextureResourceByLabel(texture_l);

					obj.setDiffuseTexture(t);
				}

				if (strcmp(header0, "ntex") == 0) {
					char texture_l[120];
					fscanf(scene_file, "%s", texture_l);
					Texture* t = result->findTextureResourceByLabel(texture_l);

					obj.setNormalTexture(t);
				}

				if (strcmp(header0, "mesh") == 0) {
					char mesh_l[120];
					int index;
					fscanf(scene_file, "%s %d", mesh_l, &index);

					Mesh* m;

					if (strcmp(mesh_l, "@plane") == 0) {
						m = getPlaneMesh2D();
					}
					else {
						m = result->findMeshResourceByLabel(mesh_l, index);
					}
					obj.setMesh(m);
				}

				if (strcmp(header0, "tr") == 0) {
					fseek(scene_file, 1, SEEK_CUR);
					ZSVECTOR3 position;
					fread(&position.X, sizeof(float), 1, scene_file);
					fread(&position.Y, sizeof(float), 1, scene_file);
					fread(&position.Z, sizeof(float), 1, scene_file);

					obj.setPosition(position);

					fseek(scene_file, 1, SEEK_CUR);
				}
				if (strcmp(header0, "rt") == 0) {
					fseek(scene_file, 1, SEEK_CUR);

					ZSVECTOR3 rotation;

					fread(&rotation.X, sizeof(float), 1, scene_file);
					fread(&rotation.Y, sizeof(float), 1, scene_file);
					fread(&rotation.Z, sizeof(float), 1, scene_file);

					obj.setRotation(rotation);

					fseek(scene_file, 1, SEEK_CUR);
				}
				if (strcmp(header0, "sc") == 0) {
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


		if (strcmp(prefix, "light") == 0) {
			Light obj;

			char header0[120];

			while (true) {
				int step = fscanf(scene_file, "%s", header0);

				if (step == EOF || strcmp(header0, "end") == 0) { break; }

				if (strcmp(header0, "str") == 0) {
					char label[120];
					fscanf(scene_file, "%s", label);

					obj.setLabel(label);
				}
				if (strcmp(header0, "type") == 0) {
					fseek(scene_file, 1, SEEK_CUR);
					ZSLIGHTTYPE type;
					fread(&type, sizeof(int), 1, scene_file);

					obj.setLightType(type);

					fseek(scene_file, 1, SEEK_CUR);
				}

				if (strcmp(header0, "prms") == 0) {
					fseek(scene_file, 1, SEEK_CUR);

					float intensity;
					float range;

					fread(&intensity, sizeof(float), 1, scene_file);
					fread(&range, sizeof(float), 1, scene_file);

					obj.setLightIntensity(intensity);
					obj.setLightRange(range);

					fseek(scene_file, 1, SEEK_CUR);
				}

				if (strcmp(header0, "pos") == 0) {
					fseek(scene_file, 1, SEEK_CUR);
					ZSVECTOR3 position;
					fread(&position.X, sizeof(float), 1, scene_file);
					fread(&position.Y, sizeof(float), 1, scene_file);
					fread(&position.Z, sizeof(float), 1, scene_file);

					obj.setLightPosition(position);

					fseek(scene_file, 1, SEEK_CUR);
				}
				if (strcmp(header0, "rot") == 0) {
					fseek(scene_file, 1, SEEK_CUR);

					ZSVECTOR3 rotation;

					fread(&rotation.X, sizeof(float), 1, scene_file);
					fread(&rotation.Y, sizeof(float), 1, scene_file);
					fread(&rotation.Z, sizeof(float), 1, scene_file);

					obj.setLightRotation(rotation);

					fseek(scene_file, 1, SEEK_CUR);
				}

				if (strcmp(header0, "color") == 0) {
					fseek(scene_file, 1, SEEK_CUR);

					ZSRGBCOLOR color;

					fread(&color.r, sizeof(int), 1, scene_file);
					fread(&color.g, sizeof(int), 1, scene_file);
					fread(&color.b, sizeof(int), 1, scene_file);

					color.updateGL();
					obj.setLightColor(color);

					fseek(scene_file, 1, SEEK_CUR);
				}

			}
			result->addLight(obj);
		}

	}
	fclose(scene_file);
	return true;
}

ZSpire::GameObject* ZSpire::Scene::getObjectByLabel(const char* label) {
	for (unsigned int i = 0; i < game_objects.size(); i ++) {
		if (strcmp(game_objects[i].getLabel(), label) == 0) return &game_objects[i];
	}
	return nullptr;
}

unsigned int ZSpire::Scene::getLightsCount(){
	return (unsigned int)this->lights.size();
}
ZSpire::Light* ZSpire::Scene::getLightAt(unsigned int index){
	return &this->lights[index];
}

void ZSpire::Scene::addTexture(Texture texture){
	scene_textures.push_back(texture);
}
void ZSpire::Scene::addMesh(Mesh mesh) {
	scene_meshes.push_back(mesh);
}

ZSpire::Texture* ZSpire::Scene::findTextureResourceByLabel(const char* label) {
	for (unsigned int i = 0; i < scene_textures.size(); i ++) {
		if (strcmp(scene_textures[i].resource_desc.label, label) == 0)
			return &scene_textures[i];
			
	}
	return nullptr;
}

ZSpire::Mesh* ZSpire::Scene::findMeshResourceByLabel(const char* label, unsigned int index) {
	for (unsigned i = 0; i < scene_meshes.size(); i ++) {
		if (strcmp(scene_meshes[i].resource_string, label) == 0 && scene_meshes[i].resource_index == index)
			return &scene_meshes[i];
	
	}
	return nullptr;
}

ZSpire::Texture* ZSpire::Scene::getTexturePtr(unsigned int index){
	return &scene_textures[index];
}
ZSpire::Mesh* ZSpire::Scene::getMeshPtr(unsigned int index) {
	return &scene_meshes[index];
}

void ZSpire::Scene::Release() {
	for (unsigned int tex_i = 0; tex_i < scene_textures.size(); tex_i ++) {
		scene_textures[tex_i].Release();
	}

	for (unsigned int mesh_i = 0; mesh_i < scene_textures.size(); mesh_i++) {
		scene_meshes[mesh_i].Release();
	}
}