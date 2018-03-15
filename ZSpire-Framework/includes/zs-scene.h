namespace ZSpire {

	class Scene {
	protected:
		std::vector<GameObject> game_objects;
	public:

		unsigned int getObjectsCount();
		GameObject* getObjectAt(unsigned int index);
	};
}