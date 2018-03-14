
struct PDEMLoadParams {

	char path[256];
	int index;
	Mesh* result;

	Vertex* vertsArr;
	uint* indsArr;

	bool reloading = false;

	PDEMLoadParams(const char* path, int index, Mesh* result, bool reloading){
		this->index = index;
		strcpy(this->path, path);
		this->result = result;
		this->reloading = reloading;
	}

};
bool LoadPDEM(const char* path, uint index, Mesh* result, Vertex** vs, uint** ids, bool reloading);
unsigned __stdcall LoadPDEMTh(void* pArguments);
