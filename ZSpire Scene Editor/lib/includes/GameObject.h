#ifndef ZSTRANSFORM
#include "zs-transform.h"
#endif

#ifndef ZSRESOURCES
#include "Resources.h"
#endif

#ifndef ZSSHADER
#include "zs-shader.h"
#endif

class GameObject {
public:

	bool exist = true;
	bool deleted;
	char label[255];

	char dtexture_name[64];
	char ntexture_name[64];
	char mesh_name[64];
	int meshIndex = 0;

	ZSpire::Transform transform;
	TextureResource* diffuse_texture;
	TextureResource* normal_texture;
	MeshResource* mesh;

	bool hasMesh = false;
	bool hasDiffuseTexture = false;
	bool hasNormalTexture = false;

	void setLabel(const char* label);

	void Draw(ZSpire::Shader* shader);

	GameObject() {
		deleted = false;
		dtexture_name[0] = '\0';
		ntexture_name[0] = '\0';
		mesh_name[0] = '\0';
	}
	
};

void addObject(GameObject object);

void createNewObject();

GameObject getObject(unsigned int pos);

GameObject* getObjectPtr(unsigned int pos);

unsigned int getObjectsAmount();