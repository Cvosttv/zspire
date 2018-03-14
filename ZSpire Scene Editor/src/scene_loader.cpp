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
	fopen_s(&scene_file, path, "r");

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

				if (strcmp(header0, "_mt") == 0) {
					char mat_name[256];
					fscanf(scene_file, "%s", mat_name);

					strcpy(obj.Material_name, mat_name);
					obj.mat_pos = getMaterialID(mat_name);
				}

				if (strcmp(header0, "_ms") == 0) {
					char mesh_name[256];
					fscanf(scene_file, "%s", mesh_name);

					strcpy(obj.Mesh_name, mesh_name);
					obj.mesh_pos = getMeshID(mesh_name);
				}

				if (strcmp(header0, "_sc") == 0) {
					fscanf(scene_file, "%f %f %f", &obj.transform.scale.x, &obj.transform.scale.y, &obj.transform.scale.z);

				}
				if (strcmp(header0, "_tr") == 0) {
					fscanf(scene_file, "%f %f %f", &obj.transform.pos.x, &obj.transform.pos.y, &obj.transform.pos.z);

				}
				if (strcmp(header0, "_rt") == 0) {
					fscanf(scene_file, "%f %f %f", &obj.transform.rotation.x, &obj.transform.rotation.y, &obj.transform.rotation.z);
					
				}

				if (strcmp(header0, "light_type") == 0) {

					fscanf(scene_file, "%d", &obj.light_type);
					if (obj.light_type > 0)
						obj.isLight = true;

				}
				if (strcmp(header0, "light_color") == 0) {
					fscanf(scene_file, "%i %i %i", &obj.light.light_color.r, &obj.light.light_color.g, &obj.light.light_color.b);
					obj.light.light_color.updateGL();
				}

				if (strcmp(header0, "light_att_params") == 0) {
					float linear;
					float quadratic;
					float maxlight;
					fscanf(scene_file, "%f %f %f", &maxlight, &linear, &quadratic);
					obj.light.setLightAttenuationParams(maxlight, linear, quadratic);
				}

				if (strcmp(header0, "default_render") == 0) {
					uint drender = 1;
					fscanf(scene_file, "%d", &drender);
					obj.isDefaultRender = (uint)drender;

				}

				if (strcmp(header0, "instanced_render") == 0) {
					uint irender = true;
					fscanf(scene_file, "%d", &irender);
					obj.isInstancedRender = (bool)irender;

				}

				if (strcmp(header0, "isCamera") == 0) {
					uint isCam;
					fscanf(scene_file, "%d", &isCam);
					obj.isCamera = (bool)isCam;
				}

				if (strcmp(header0, "aud_source") == 0) {
					uint isAudioSource;
					fscanf(scene_file, "%d", &isAudioSource);
					obj.isAudioSource = (uint)isAudioSource;
				}

				if (strcmp(header0, "isAudioListener") == 0) {
					uint isAud;
					fscanf(scene_file, "%d", &isAud);
					obj.isAudioListener = (bool)isAud;
					
				}

			}

		


			addObject(obj);

		}
	}

	isSceneLoaded = true;
	fclose(scene_file);

}

void saveScene(){
	FILE* scene_write = fopen(loadedScenePath, "w");

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

		fprintf(scene_write, "_mt %s\n", obj.Material_name);
		fprintf(scene_write, "_ms %s\n", obj.Mesh_name);

		fprintf(scene_write, "_tr %f %f %f\n", obj.transform.pos.x, obj.transform.pos.y, obj.transform.pos.z);
		fprintf(scene_write, "_sc %f %f %f\n", obj.transform.scale.x, obj.transform.scale.y, obj.transform.scale.z);
		fprintf(scene_write, "_rt %f %f %f\n", obj.transform.rotation.x, obj.transform.rotation.y, obj.transform.rotation.z);

		fprintf(scene_write, "default_render %d\n", obj.isDefaultRender);
		fprintf(scene_write, "instanced_render %d\n", obj.isInstancedRender);

		fprintf(scene_write, "isCamera %d\n", obj.isCamera);
		if (obj.isCamera == true) {
			fprintf(scene_write, "camera_proj %f %f %f\n", obj.cam.nearPlane, obj.cam.farPlane, obj.cam.fov);
			fprintf(scene_write, "camera_cullFace %d\n", obj.cam.cullFace);
			fprintf(scene_write, "camera_drawDepth %d\n", obj.cam.drawDepth);
		}


		fprintf(scene_write, "aud_source %d\n", obj.isAudioSource);
		fprintf(scene_write, "isAudioListener %d\n", obj.isAudioListener);

		if (obj.isLight == true) {
			fprintf(scene_write, "light_type %d\n", obj.light_type);
			fprintf(scene_write, "light_color %d %d %d\n", obj.light.light_color.r, obj.light.light_color.g, obj.light.light_color.b);
			fprintf(scene_write, "light_att_params %f %f %f\n", obj.light.maxlight, obj.light.linear, obj.light.quadratic);
		}
		else {
			fprintf(scene_write, "light_type %d\n", 0);
		}
		


		fprintf(scene_write, "end\n");
	}

	fclose(scene_write);
}