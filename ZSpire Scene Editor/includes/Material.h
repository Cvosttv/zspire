class Material {
public:
	char label[256];
	char file_path[256];

	bool destroyed = false;
};




bool LoadMaterial(Material* result, const char* filepath);

uint getMaterialsAmount();

Material getMaterial(uint pos);

Material* getMaterialPtr(uint pos);

void addMaterial(Material material);

uint getMaterialID(const char* material_label);