#ifndef ZSRESOURCE
#include "../includes/zs-resource.h"
#endif

namespace ZSpire {

	struct ZSLOADEDMESHINFO {
		unsigned int amount_meshes;
	};

	ZSpire::Mesh* LoadMeshFromBuffer(void* buffer, size_t size, ZSLOADEDMESHINFO* loadinfo);

	ZSpire::Mesh* LoadMeshesFromFile(const char* file_path, ZSLOADEDMESHINFO* loadinfo);

	ZSpire::Mesh* LoadMeshesFromResourceDesc(ZSResourceDesc* desc, ZSLOADEDMESHINFO* loadinfo);
}