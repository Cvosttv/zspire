#ifndef ZSRESOURCE
#include "zs-resource.h"
#endif

namespace ZSpire {

	struct ZSLOADEDMESHINFO {
		unsigned int amount_meshes;
	};

	ZSpire::Mesh* LoadMeshFromBuffer(void* buffer, size_t size, ZSLOADEDMESHINFO* loadinfo = nullptr);

	ZSpire::Mesh* LoadMeshesFromFile(const char* file_path, ZSLOADEDMESHINFO* loadinfo = nullptr);

	ZSpire::Mesh* LoadMeshesFromResourceDesc(ZSResourceDesc* desc, ZSLOADEDMESHINFO* loadinfo = nullptr);
}