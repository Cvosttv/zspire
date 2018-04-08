#ifndef ZSMESH
#include "zs-mesh.h"
#endif

#ifndef ZSGAMEOBJECT
#include "zs-game-object.h"
#endif

#ifndef ZSSCENE

namespace ZSpire {


	class Scene {
	protected:
		std::vector<Texture> scene_textures;
		std::vector<Mesh> scene_meshes;

		std::vector<GameObject> game_objects;
		std::vector<Light> lights;
	public:
		void addObject(GameObject obj);
		void addLight(Light obj);
		unsigned int getObjectsCount();
		GameObject* getObjectAt(unsigned int index);
		GameObject* getObjectByLabel(const char* label);

		unsigned int getLightsCount();
		Light* getLightAt(unsigned int index);

		void addTexture(Texture texture);
		void addMesh(Mesh mesh);

		Texture* getTexturePtr(unsigned int index);
		Mesh* getMeshPtr(unsigned int index);

		Texture* findTextureResourceByLabel(const char* label);
		Mesh* findMeshResourceByLabel(const char* label, unsigned int index);

		void Release();
	};

	bool LoadSceneFromFile(const char* file_path, Scene* result);

}

#define ZSSCENE
#endif
