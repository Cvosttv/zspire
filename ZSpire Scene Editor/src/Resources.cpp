#define _CRT_SECURE_NO_WARNINGS

#include <vector>
#include "stdio.h"

#include "../includes/zs-math.h"
#include "../includes/zs-texture.h"
#include "../includes/zs-mesh.h"

#include "../includes/zs-mesh-loader.h"

#include "../includes/Resources.h"


std::vector<MeshResource> meshes;
std::vector<TextureResource> textures;

unsigned int getMeshesCount() {
	return (unsigned int)meshes.size();
}

MeshResource* getMeshAt(unsigned int index) {
	return &meshes[index];
}

void addMesh(MeshResource mesh) {
	mesh.meshes = ZSpire::LoadMeshesFromFile(mesh.file_path);
	meshes.push_back(mesh);
}

unsigned int getTexturesCount() {
	return (unsigned int)textures.size();
}

TextureResource* getTextureAt(unsigned int index) {
	return &textures[index];
}

void addTexture(TextureResource texture) {
	texture.texture.LoadDDSFromFile(texture.file_path);
	textures.push_back(texture);

}


void loadResources(const char* path){

	FILE* fl = fopen(path, "r");

	while (true) {
		char prefix[120];
		int step = fscanf(fl, "%s", prefix);

		if (step == EOF) break;


		if (strcmp(prefix, "tex") == 0) {
			TextureResource tr;

			fscanf(fl, "%s %s %s", tr.file_path, tr.name, tr.file_to_write_path);

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