namespace ZSpire {

	class Scene {
	protected:
		std::vector<GameObject> game_objects;
		std::vector<Light> lights;
	public:
		void addObject(GameObject obj);
		unsigned int getObjectsCount();
		GameObject* getObjectAt(unsigned int index);
		GameObject* getObjectByLabel(const char* label);

		unsigned int getLightsCount();
		Light* getLightAt(unsigned int index);
	};

	bool LoadSceneFromFile(const char* file_path, Scene* result);

}