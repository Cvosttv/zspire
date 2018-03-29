
#ifndef ZSRESOURCES
#define ZSRESOURCES
#endif

#ifndef ZSMESH
#include "zs-mesh.h"
#endif

#ifndef ZSTEXTURE
#include "zs-texture.h"
#endif

struct MeshResource {

	ZSpire::Mesh* meshes;
	char name[64];

	char file_path[128];

	char file_to_write_path[128];


	bool isInPack = false;
	unsigned int byte_start;
	unsigned int byte_end;

	bool isRemoved = false;

	MeshResource() {
		file_path[0] = '\0';
		file_to_write_path[0] = '\0';
	}

};

struct TextureResource {

	ZSpire::Texture texture;
	char name[64];

	char file_path[128];

	char file_to_write_path[128];

	bool isInPack = false;
	unsigned int byte_start;
	unsigned int byte_end;

	bool isRemoved = false;

	TextureResource() {
		file_path[0] = '\0';
		file_to_write_path[0] = '\0';
	}

};


unsigned int getMeshesCount();
MeshResource* getMeshAt(unsigned int index);
void addMesh(MeshResource mesh);

unsigned int getTexturesCount();
TextureResource* getTextureAt(unsigned int index);
void addTexture(TextureResource mesh);

void loadResources(const char* path);

TextureResource* getTexturePtrByName(const char* name);

MeshResource* getMeshPtrByName(const char* name);