#define _CRT_SECURE_NO_WARNINGS
typedef unsigned int uint;


#include "../includes/DMath.h"

#include <glew.h>

#include <vector>

#include "../includes/geometry.h"
#include "string.h"
#include "../includes/pdem_loader.h"
#include "stdio.h"
//#include "plurs\logger.h"

#include "stdlib.h"
#include <process.h>


unsigned __stdcall LoadPDEMTh(void* pArguments)
{

	Vertex* vs = nullptr;
	uint* ids = nullptr;


	LoadPDEM(((PDEMLoadParams*)pArguments)->path, ((PDEMLoadParams*)pArguments)->index, ((PDEMLoadParams*)pArguments)->result
		, &vs, &ids, ((PDEMLoadParams*)pArguments)->reloading);

	((PDEMLoadParams*)pArguments)->vertsArr = vs;
	((PDEMLoadParams*)pArguments)->indsArr = ids;


	_endthreadex(0);
	return 0;
}



bool LoadPDEM(const char* path, uint index, Mesh* result, Vertex** verticesArr, uint** indicesArr, bool reloading) {

	FILE* model = fopen(path, "rb");

	strcpy(result->file_path, path);
	result->mesh_index = index;
	result->mesh_file_type = 0;

	if (model == NULL) {
		return false;
	}
	char header[5];
	fread(header, 1, 4, model);

	if (header[0] != 'P' || header[1] != 'D' || header[2] != 'E' || header[3] != 'M') {
		//dlogger::Log(TYPE_ERROR, "%s %s %s", "Perhaps, scene file ", path, " is incorrect");
		return false;
	}
	char prefix[120];
	uint overpassed = 0;
	uint nodes_processed = 0;

	while (true) {
		int step = fscanf(model, "%s", prefix);
		if (step == EOF) {
			break;
		}
		if (reloading == false && strcmp(prefix, "nds") == 0) {
			uint nodes_count;
			fscanf(model, "%d", &nodes_count);
			result->nodes_count = nodes_count;

		}

		if (reloading == false && strcmp(prefix, "inv") == 0) {

			for (uint matx = 0; matx < 4; matx++) {
				for (uint maty = 0; maty < 4; maty++) {
					fscanf(model, "%f", &result->globalInverse.m[matx][maty]);
				}
			}

		}

		if (strcmp(prefix, "obj") == 0) {

			if (overpassed == index) {
				nodes_processed = 0;

				overpassed += 1;
				char label[30];
				uint vertices = 0;
				uint indices = 0;
				uint bones = 0;




				uint vertices_processed = 0;
				uint indices_processed = 0;
				uint bones_processed = 0;


				fscanf(model, "%s %d %d %d", label, &vertices, &indices, &bones);

				result->vertices_count = vertices;
				result->indices_count = indices;
				result->bones_count = bones;

				*verticesArr = (Vertex*)malloc(vertices * sizeof(Vertex));
				*indicesArr = (uint*)malloc(result->indices_count * sizeof(uint));
				if (reloading == false) {
					result->bones = (Bone*)malloc(bones * sizeof(Bone));
					strcpy(result->label, label);
				}

				while (true) {
					step = fscanf(model, "%s", prefix);
					if (strcmp(prefix, "end") == 0) {
						break;

					}
					if (strcmp(prefix, "v") == 0) {



						uint weights_amount = 0;
						fseek(model, 1, SEEK_CUR);

						fread(&((*verticesArr)[vertices_processed]), 14 * sizeof(float), 1, model);

						fseek(model, 1, SEEK_CUR);

						fscanf(model, "%d", &weights_amount);

						if (weights_amount > 12) {
							weights_amount = 12;
						}
						for (uint i = 0; i < weights_amount; i++) {


							fscanf(model, " %d %f", &(*verticesArr)[vertices_processed].boneID[i],
								&(*verticesArr)[vertices_processed].weight[i]);


						}

						vertices_processed += 1;

					}

					if (strcmp(prefix, "f") == 0) {
						fseek(model, 1, SEEK_CUR);
						for (uint i = 0; i < result->indices_count; i++) {
							uint value = 0;
							fscanf(model, "%d", &value);
							(*indicesArr)[indices_processed] = value;

							indices_processed += 1;
						}

					}


					if (reloading == false && strcmp(prefix, "b") == 0) {

						fscanf(model, "%s ", result->bones[bones_processed].label);
						for (uint matx = 0; matx < 4; matx++) {
							for (uint maty = 0; maty < 4; maty++) {
								fscanf(model, "%f", &result->bones[bones_processed].offset.m[matx][maty]);
							}
						}
						bones_processed += 1;
					}



				}
			}
			else {
				overpassed += 1;
				uint vertices = 0;
				uint indices = 0;
				uint bones = 0;
				char label[120];


				fscanf(model, "%s %d %d %d", label, &vertices, &indices, &bones);
				fseek(model, vertices * (56 + 2 + 2) + indices * 2, SEEK_CUR);
			}

		}

		if (reloading == false && strcmp(prefix, "nod") == 0) {

			char label[120];

			uint node_children_amount = 0;
			uint mesh_children_amount = 0;

			fscanf(model, "%s %d", label, &node_children_amount);

			strcpy(result->nodes[nodes_processed].label, label);

			result->nodes[nodes_processed].children_num = node_children_amount;

			result->nodes[nodes_processed].node_children = (uint*)malloc(node_children_amount * sizeof(uint));

			for (uint node = 0; node < node_children_amount; node++) {
				fscanf(model, " %d", &result->nodes[nodes_processed].node_children[node]);
			}

			fscanf(model, "%d", &mesh_children_amount);

			for (uint matx = 0; matx < 4; matx++) {
				for (uint maty = 0; maty < 4; maty++) {
					fscanf(model, "%f", &result->nodes[nodes_processed].offset.m[matx][maty]);
				}
			}
			nodes_processed += 1;
		}
	}

	fclose(model);
	result->loaded = true;

	return true;
}