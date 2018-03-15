namespace ZSpire {

	class Scene {
	protected:
		std::vector<GameObject> game_objects;
	public:
		void addObject(GameObject obj);
		unsigned int getObjectsCount();
		GameObject* getObjectAt(unsigned int index);
	};

	bool LoadSceneFromFile(const char* file_path, Scene* result);

}