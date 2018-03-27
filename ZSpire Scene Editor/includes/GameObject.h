class GameObject {
public:

	bool exist = true;
	char label[255];

	char dtexture_name[64];
	char ntexture_name[64];
	char mesh_name[64];
	int meshIndex = 0;

	ZSpire::Transform transform;

	void setLabel(const char* label);

	GameObject() {
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