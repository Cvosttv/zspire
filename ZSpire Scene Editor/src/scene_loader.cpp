#define _CRT_SECURE_NO_WARNINGS
typedef unsigned int uint;
#include "stdio.h"
#include "string.h"
#include <cstdio>
#include <process.h>
#include <windows.h>
#include <vector>
#include <string>

#include "../includes/zs-math.h"
#include "../includes/geometry.h"
#include "../includes/scene_loader.h"
#include "../includes/Camera.hpp"
#include "../includes/Light.h"
#include "../includes/zs-transform.h"
#include "../includes/GameObject.h"

#include "../includes/zs-texture.h"

#include <stddef.h>
#include <fcntl.h>
#include <sys/stat.h>

#include "../includes/Resources.h"

bool isSceneLoaded = false;
char loadedScenePath[256];

bool IsSceneLoaded() {
	return isSceneLoaded;
}

unsigned int getFileSize(const char* path) {
	struct stat buff;

	FILE *part = fopen(path, "rb");
	fstat(_fileno(part), &buff);

	return buff.st_size;
}
void readBFile(char* content, const char* file, uint size) {
	FILE* fileP = fopen(file, "rb");

	fread(content, 1, size, fileP);
	fclose(fileP);
}


void LoadScene(const char* path){
	strcpy(loadedScenePath, path);
	FILE* scene_file;
	fopen_s(&scene_file, path, "rb");

	char reslist_file[128];
	strcpy(reslist_file, path);
	strcat(reslist_file, "_reslist");

	loadResources(reslist_file);

	if(scene_file == NULL){
	//Failed opening file
	}
	char header[5];
	fread(header,1, 4, scene_file);
	if (header[0] != 'D' || header[1] != 'S' || header[2] != 'C' || header[3] != 'N') {
		//Incorrect scene
		//return false;
	}

	while(true){
		char prefix[120];
		int step = fscanf(scene_file, "%s", prefix);
		
		if (step == EOF) break;

		
		if (strcmp(prefix, "obj") == 0) {
			GameObject obj;


			char header0[120];

			while (true) {
				int step = fscanf(scene_file, "%s", header0);

				if (step == EOF || strcmp(header0, "end") == 0) { break; }

				if (strcmp(header0, "str") == 0) {
					char label[120];
					fscanf(scene_file, "%s", label);

					strcpy(obj.label, label);
				}

				if (strcmp(header0, "tex") == 0) {
					char texture[64];
					fscanf(scene_file, "%s", texture);

					strcpy(obj.texture_name, texture);
				}

				if (strcmp(header0, "_sc") == 0) {
					fseek(scene_file, 1, SEEK_CUR);

					float scX;
					float scY;
					float scZ;

					fread(&scX, sizeof(float), 1, scene_file);
					fread(&scY, sizeof(float), 1, scene_file);
					fread(&scZ, sizeof(float), 1, scene_file);

					fseek(scene_file, 1, SEEK_CUR);

					obj.transform.setScale(ZSVECTOR3(scX, scY, scZ));

				}
				if (strcmp(header0, "_tr") == 0) {
					fseek(scene_file, 1, SEEK_CUR);

					float posX;
					float posY;
					float posZ;

					fread(&posX, sizeof(float), 1, scene_file);
					fread(&posY, sizeof(float), 1, scene_file);
					fread(&posZ, sizeof(float), 1, scene_file);

					obj.transform.setPosition(ZSVECTOR3(posX, posY, posZ));

					fseek(scene_file, 1, SEEK_CUR);
				}
				if (strcmp(header0, "_rt") == 0) {
					fseek(scene_file, 1, SEEK_CUR);

					float rotX;
					float rotY;
					float rotZ;

					fread(&rotX, sizeof(float), 1, scene_file);
					fread(&rotY, sizeof(float), 1, scene_file);
					fread(&rotZ, sizeof(float), 1, scene_file);

					obj.transform.setRotation(ZSVECTOR3(rotX, rotY, rotZ));

					fseek(scene_file, 1, SEEK_CUR);
				}

				

			}
			addObject(obj);

		}
	}

	isSceneLoaded = true;
	fclose(scene_file);

}

void saveScene(){
	remove("textures.pack"); //remove old pack file 
	remove("meshes.pack"); //remove old pack file 

	unsigned int processed_size = 0;

	FILE* scene_write = fopen(loadedScenePath, "wb");
	FILE* resource_map_write = fopen((std::string(loadedScenePath) + "_reslist").c_str(), "w");

	fprintf(scene_write, "DSCN\n");

	unsigned int res_meshes_count = getMeshesCount();
	unsigned int res_textures_count = getTexturesCount();

	for (unsigned int i = 0; i < res_textures_count; i++) {
		if (getTextureAt(i)->isRemoved == false) {
			
			fprintf(resource_map_write, "tex %s %s %s\n", getTextureAt(i)->file_path, getTextureAt(i)->name, getTextureAt(i)->file_to_write_path);


			uint source_size = getFileSize(getTextureAt(i)->file_path);

			char* content = (char*)malloc(source_size + 1);
			readBFile(content, getTextureAt(i)->file_path, source_size);

			

			FILE* toWrite = fopen(getTextureAt(i)->file_to_write_path, "ab");

			fwrite(content, 1, source_size, toWrite);
			fclose(toWrite);
			processed_size += source_size;
			
			int startbyte = processed_size - source_size;
			fprintf(scene_write, "tex %s %s ", getTextureAt(i)->name , getTextureAt(i)->file_to_write_path);
			fwrite(&startbyte, 4, 1, scene_write);
			fwrite(&processed_size, 4, 1, scene_write);
			fprintf(scene_write, "\n");
		}
	}
	
	for (unsigned int i = 0; i < res_meshes_count; i++) {
		if (getMeshAt(i)->isRemoved == false) {

			fprintf(resource_map_write, "mesh %s %s %s \n", getMeshAt(i)->file_path, getMeshAt(i)->name, getMeshAt(i)->file_to_write_path);


			uint source_size = getFileSize(getMeshAt(i)->file_path);

			char* content = (char*)malloc(source_size + 1);
			readBFile(content, getMeshAt(i)->file_path, source_size);



			FILE* toWrite = fopen(getMeshAt(i)->file_to_write_path, "ab");

			fwrite(content, 1, source_size, toWrite);
			fclose(toWrite);
			processed_size += source_size;

			int startbyte = processed_size - source_size;
			fprintf(scene_write, "mesh %s %s ", getMeshAt(i)->name, getMeshAt(i)->file_to_write_path);
			fwrite(&startbyte, 4, 1, scene_write);
			fwrite(&processed_size, 4, 1, scene_write);
			fprintf(scene_write, "\n");
		}
	}


	fclose(resource_map_write);

	for (uint i = 0; i < getObjectsAmount(); i++) {
		GameObject obj;
		obj = getObject(i);
		fprintf(scene_write, "obj\n");

		if(strlen(obj.label) >= 1)
			fprintf(scene_write, "str %s\n", obj.label);

		if (strlen(obj.texture_name) >= 1)
			fprintf(scene_write, "tex %s\n", obj.texture_name);

		float scX = obj.transform._getScale().X;
		float scY = obj.transform._getScale().Y;
		float scZ = obj.transform._getScale().Z;
		
		float posX = obj.transform._getPosition().X;
		float posY = obj.transform._getPosition().Y;
		float posZ = obj.transform._getPosition().Z;

		float rotX = obj.transform._getRotation().X;
		float rotY = obj.transform._getRotation().Y;
		float rotZ = obj.transform._getRotation().Z;

		fprintf(scene_write, "_tr ");
		fwrite(&posX, sizeof(float), 1, scene_write);
		fwrite(&posY, sizeof(float), 1, scene_write);
		fwrite(&posZ, sizeof(float), 1, scene_write);
		fprintf(scene_write, "\n");
		
	
		fprintf(scene_write, "_sc ");
		fwrite(&scX, sizeof(float), 1, scene_write);
		fwrite(&scY, sizeof(float), 1, scene_write);
		fwrite(&scZ, sizeof(float), 1, scene_write);
		fprintf(scene_write, "\n");


		fprintf(scene_write, "_rt ");
		fwrite(&rotX, sizeof(float), 1, scene_write);
		fwrite(&rotY, sizeof(float), 1, scene_write);
		fwrite(&rotZ, sizeof(float), 1, scene_write);
		fprintf(scene_write, "\n");




		fprintf(scene_write, "end\n");
	}

	fclose(scene_write);
}

void createNewScene(const char* name) {
	isSceneLoaded = true;
	strcpy_s(loadedScenePath, name);

	FILE* scenereslist_write = fopen((std::string(name) + "_reslist").c_str(), "w");
	fclose(scenereslist_write);
}