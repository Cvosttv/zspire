#define _CRT_SECURE_NO_WARNINGS

typedef unsigned int uint;

#include <vector>

#include "../includes/Material.h"

std::vector<Material> materials;


bool LoadMaterial(Material* result, const char* filepath) {
	FILE* material_file = fopen(filepath, "r");
	strcpy(result->file_path, filepath);

	char header[5];

	if (header[0] != 'D' || header[1] != 'M' || header[2] != 'A' || header[3] != 'T') {
		//dlogger::Log(TYPE_ERROR, "%s %s %s", "Perhaps, file ", file_path, " isn't material file!");
		return false;
	}

	fclose(material_file);
	return true;
}

uint getMaterialsAmount(){
	return materials.size();
}

Material getMaterial(uint pos){
	return materials[pos];
}

Material* getMaterialPtr(uint pos) {
	return &materials[pos];
}

void addMaterial(Material material){
	bool hasEmpty = false;
	uint empty_pos = 0;

	for (uint i = 0; i < materials.size(); i ++) {
		if (materials[i].destroyed == true) {
			hasEmpty = true;
			empty_pos = i;
		}
	}

	if (hasEmpty == true) {
		materials[empty_pos] = material;
	}
	else {
		materials.push_back(material);
	}

}

uint getMaterialID(const char* material_label) {

	for (uint i = 0; i < getMaterialsAmount(); i ++) {
	
		if (strcmp(materials[i].label, material_label) == 0) return i;
	
	}

	return 0;
}