#define _CRT_SECURE_NO_WARNINGS
typedef unsigned int uint;
#include "stdio.h"
#include "string.h"
#include <process.h>
#include <windows.h>
#include <vector>

#include "../includes/DMath.h"
#include "../includes/geometry.h"
#include "../includes/pdem_loader.h"
#include "../includes/scene_loader.h"
#include "../includes/Material.h"
#include "../includes/Camera.hpp"
#include "../includes/DColor.h"
#include "../includes/Light.h"
#include "../includes/GameObject.h"

bool isSceneLoaded = false;
char loadedScenePath[256];

bool IsSceneLoaded() {
	return isSceneLoaded;
}

void ldPDEM(Mesh* mesh, const char* path, int index) {

	mesh->initMesh();
	PDEMLoadParams params(path, index, mesh, false);
	HANDLE hThread;
	unsigned threadID;
	hThread = (HANDLE)_beginthreadex(NULL, 0, &LoadPDEMTh, &params, 0, &threadID);


	while (WaitForSingleObject(hThread, 15) != WAIT_OBJECT_0) {
		//tick();
	};

	// Destroy the thread object.  
	CloseHandle(hThread);
	processMesh(mesh, params.vertsArr, params.indsArr);
	free(params.vertsArr);
	free(params.indsArr);

}

void LoadScene(const char* path){
	strcpy(loadedScenePath, path);
	FILE* scene_file;
	fopen_s(&scene_file, path, "rb");

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

		if (strcmp(prefix, "mat") == 0) {
			char mat_path[128];
			fscanf(scene_file, "%s", mat_path);
			Material mat;
		
			LoadMaterial(&mat, mat_path);

			addMaterial(mat);
		}
		if (strcmp(prefix, "mes") == 0) {
			char mesh_path[128];
			int mesh_index = 0;
			fscanf(scene_file, "%s %i", mesh_path, &mesh_index);
			
			if (mesh_index >= 0) {
				Mesh mesh;
				ldPDEM(&mesh, mesh_path, mesh_index);
				addMesh(mesh);
				
			}
			else {
				for (uint i = 0; i < (uint)mesh_index * -1; i++) {
					Mesh mesh;
					ldPDEM(&mesh, mesh_path, i);
					addMesh(mesh);
				}
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

					strcpy(obj.label, label);
				}

				

				if (strcmp(header0, "_sc") == 0) {
					fseek(scene_file, 1, SEEK_CUR);
					fread(&obj.transform.scale.x, sizeof(float), 1, scene_file);
					fread(&obj.transform.scale.y, sizeof(float), 1, scene_file);
					fread(&obj.transform.scale.z, sizeof(float), 1, scene_file);

					fseek(scene_file, 1, SEEK_CUR);
				}
				if (strcmp(header0, "_tr") == 0) {
					fseek(scene_file, 1, SEEK_CUR);
					fread(&obj.transform.pos.x, sizeof(float), 1, scene_file);
					fread(&obj.transform.pos.y, sizeof(float), 1, scene_file);
					fread(&obj.transform.pos.z, sizeof(float), 1, scene_file);

					fseek(scene_file, 1, SEEK_CUR);
				}
				if (strcmp(header0, "_rt") == 0) {
					fseek(scene_file, 1, SEEK_CUR);
					fread(&obj.transform.rotation.x, sizeof(float), 1, scene_file);
					fread(&obj.transform.rotation.y, sizeof(float), 1, scene_file);
					fread(&obj.transform.rotation.z, sizeof(float), 1, scene_file);

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
	FILE* scene_write = fopen(loadedScenePath, "wb");

	fprintf(scene_write, "DSCN\n");

	for (uint i = 0; i < getMeshesSize(); i ++) {
		fprintf(scene_write, "mes %s %d\n", getMesh(i).file_path, getMesh(i).mesh_index);
	}

	for (uint i = 0; i < getMaterialsAmount(); i++) {
		fprintf(scene_write, "mat %s\n", getMaterial(i).file_path);
	}

	for (uint i = 0; i < getObjectsAmount(); i++) {
		GameObject obj;
		obj = getObject(i);
		fprintf(scene_write, "obj\n");

		if(strlen(obj.label) >= 1)
			fprintf(scene_write, "str %s\n", obj.label);

		
		fprintf(scene_write, "_tr ");
		fwrite(&obj.transform.pos.x, sizeof(float), 1, scene_write);
		fwrite(&obj.transform.pos.y, sizeof(float), 1, scene_write);
		fwrite(&obj.transform.pos.z, sizeof(float), 1, scene_write);
		fprintf(scene_write, "\n");
		
	
		fprintf(scene_write, "_sc ");
		fwrite(&obj.transform.scale.x, sizeof(float), 1, scene_write);
		fwrite(&obj.transform.scale.y, sizeof(float), 1, scene_write);
		fwrite(&obj.transform.scale.z, sizeof(float), 1, scene_write);
		fprintf(scene_write, "\n");


		fprintf(scene_write, "_rt ");
		fwrite(&obj.transform.rotation.x, sizeof(float), 1, scene_write);
		fwrite(&obj.transform.rotation.y, sizeof(float), 1, scene_write);
		fwrite(&obj.transform.rotation.z, sizeof(float), 1, scene_write);
		fprintf(scene_write, "\n");




		fprintf(scene_write, "end\n");
	}

	fclose(scene_write);
}

void createNewScene(const char* name) {
	isSceneLoaded = true;
	strcpy_s(loadedScenePath, name);
}