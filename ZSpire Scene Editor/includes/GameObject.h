class GameObject {
public:

	bool exist = true;
	char label[512];
	uint mesh_id;

	Transform transform;

	char Material_name[256];
	char Mesh_name[256];

	uint mat_pos;
	uint mesh_pos;

	bool isDefaultRender = true;
	bool isInstancedRender = false;

	//std::vector<ObjectScript> scripts;
	std::vector<int> children;

	bool isAudioSource = false;
	bool isCamera = false;
	bool isAudioListener;
	bool isLight = false;
	int light_type = 0;

	Light light;
	Camera cam;

	void setLabel(const char* label);
};

void addObject(GameObject object);

void createNewObject();

GameObject getObject(uint pos);

GameObject* getObjectPtr(uint pos);

uint getObjectsAmount();