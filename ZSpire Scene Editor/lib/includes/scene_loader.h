#ifndef ZSTEXTURE
#include "zs-texture.h"
#endif

#ifndef ZSMESH
#include "zs-mesh.h"
#endif

#ifndef ZSRESOURCES
#include "Resources.h"
#endif

struct PackFileState {
	char path[128];
	unsigned int written_bytes = 0;
};

bool IsSceneLoaded();

void LoadScene(const char* path);

void saveScene();

void createNewScene(const char* name);

