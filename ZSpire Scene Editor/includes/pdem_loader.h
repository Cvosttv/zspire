#ifndef ZSMESH
#include "zs-mesh.h"
#endif


struct PDEMLoadParams {

	char path[256];
	int index;
	ZSpire::Mesh* result;

	ZSVERTEX* vertsArr;
	unsigned int* indsArr;

	bool reloading = false;

	PDEMLoadParams(const char* path, int index, ZSpire::Mesh* result, bool reloading){
		this->index = index;
		strcpy(this->path, path);
		this->result = result;
		this->reloading = reloading;
	}

};
bool LoadPDEM(const char* path, unsigned int index, ZSpire::Mesh* result, ZSVERTEX** vs, unsigned int** ids, bool reloading);
bool LoadPDEM(const char* path, unsigned int index, ZSpire::Mesh* result, ZSVERTEX** verticesArr, unsigned int** indicesArr, bool reloading);
unsigned __stdcall LoadPDEMTh(void* pArguments);

bool LoadPDEM(const char* path, unsigned int index, ZSpire::Mesh* result);