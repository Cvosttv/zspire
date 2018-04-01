#define _CRT_SECURE_NO_WARNINGS

#include <vector>
#include "stdio.h"
#include <cstring>

#include "../includes/zs-math.h"
#include "../includes/zs-texture.h"
#include "../includes/zs-mesh.h"

#include "../includes/zs-mesh-loader.h"

#include "../includes/Resources.h"

#include "../includes/GameObject.h"

std::vector<MeshResource> meshes;

std::vector<TextureResource> textures;


void RefreshObjectData(int i) {
	MeshResource* me = getMeshPtrByName(getObjectPtr(i)->mesh_name);

	if (me != nullptr) {
		getObjectPtr(i)->mesh = me;
		getObjectPtr(i)->hasMesh = true;
	}


	TextureResource* de = getTexturePtrByName(getObjectPtr(i)->dtexture_name);

	if (de != nullptr) {
		getObjectPtr(i)->diffuse_texture = de;
		getObjectPtr(i)->hasDiffuseTexture = true;
	}

	TextureResource* ne = getTexturePtrByName(getObjectPtr(i)->ntexture_name);

	if (ne != nullptr) {
		getObjectPtr(i)->normal_texture = ne;
		getObjectPtr(i)->hasNormalTexture = true;
	}

}

void RefreshObjectsData() {
	for (unsigned int i = 0; i < getObjectsAmount(); i++) {
		RefreshObjectData(i);
	}

}

unsigned int getMeshesCount() {
	return (unsigned int)meshes.size();
}

MeshResource* getMeshAt(unsigned int index) {
	return &meshes[index];
}

void addMesh(MeshResource mesh) {
	if (strlen(mesh.file_path) > 0) {
		mesh.meshes = ZSpire::LoadMeshesFromFile(mesh.file_path);
		mesh.isLoaded = true;
	}
	meshes.push_back(mesh);

	RefreshObjectsData();

}

unsigned int getTexturesCount() {
	return (unsigned int)textures.size();
}

TextureResource* getTextureAt(unsigned int index) {
	return &textures[index];
}

void addTexture(TextureResource texture) {
	if(strlen(texture.file_path) > 0)
	texture.texture.LoadDDSFromFile(texture.file_path);
	
	texture.texture.setTextureParams();
	
	textures.push_back(texture);

	RefreshObjectsData();
}


void loadResources(const char* path){

	FILE* fl = fopen(path, "r");

	while (true) {
		char prefix[120];
		int step = fscanf(fl, "%s", prefix);

		if (step == EOF) break;


		if (strcmp(prefix, "tex") == 0) {
			TextureResource tr;

			fscanf(fl, "%s %s %s %f", tr.file_path, tr.name, tr.file_to_write_path, &tr.texture.params.max_anisotropy);

			addTexture(tr);

		}

		if (strcmp(prefix, "mesh") == 0) {
			MeshResource tr;

			fscanf(fl, "%s %s %s", tr.file_path, tr.name, tr.file_to_write_path);

			addMesh(tr);

		}
	}

	fclose(fl);
}

TextureResource* getTexturePtrByName(const char* name) {
	unsigned int textures_num = getTexturesCount();

	for (unsigned int i = 0; i < textures_num; i++) {
		if (strcmp(name, getTextureAt(i)->name) == 0) return getTextureAt(i);
	}
	return nullptr;
}

MeshResource* getMeshPtrByName(const char* name) {
	unsigned int meshes_count = getMeshesCount();

	for (unsigned int i = 0; i < meshes_count; i++) {
		if (strcmp(name, getMeshAt(i)->name) == 0) return getMeshAt(i);
	}
	return nullptr;
}
