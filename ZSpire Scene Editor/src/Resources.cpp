#define _CRT_SECURE_NO_WARNINGS

#include <vector>
#include "stdio.h"

#include "../includes/zs-math.h"
#include "../includes/zs-texture.h"
#include "../includes/geometry.h"

#include "../includes/Resources.h"


std::vector<MeshResource> meshes;
std::vector<TextureResource> textures;

unsigned int getMeshesCount() {
	return meshes.size();
}

MeshResource* getMeshAt(unsigned int index) {
	return &meshes[index];
}

void addMesh(MeshResource mesh) {
	meshes.push_back(mesh);
}

unsigned int getTexturesCount() {
	return textures.size();
}

TextureResource* getTextureAt(unsigned int index) {
	return &textures[index];
}

void addTexture(TextureResource mesh) {

	textures.push_back(mesh);

}


void loadResources(const char* path){

	FILE* fl = fopen(path, "r");

	while (true) {
		char prefix[120];
		int step = fscanf(fl, "%s", prefix);

		if (step == EOF) break;


		if (strcmp(prefix, "tex") == 0) {
			TextureResource tr;

			fscanf(fl, "%s %s", tr.file_path, tr.name);

			addTexture(tr);

		}

		if (strcmp(prefix, "mesh") == 0) {
			MeshResource tr;

			fscanf(fl, "%s %s", tr.file_path, tr.name);

			addMesh(tr);

		}
	}
}