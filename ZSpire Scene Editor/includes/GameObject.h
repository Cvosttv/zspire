class GameObject {
public:

	bool exist = true;
	char label[512];

	Transform transform;

	void setLabel(const char* label);
};

void addObject(GameObject object);

void createNewObject();

GameObject getObject(uint pos);

GameObject* getObjectPtr(uint pos);

uint getObjectsAmount();