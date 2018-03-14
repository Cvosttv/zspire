
struct Bone{
    char label[120];
    Mat4x4 offset;
};

struct Node {
	char label[120];
	uint* node_children;

	uint children_num = 0;

	Mat4x4 offset;

};

class Mesh{
public:
    uint VAO;
    uint VBO;
	uint EBO;

    uint vertices_count = 0;
    uint indices_count = 0;
    uint bones_count = 0;
	uint nodes_count;

    Bone* bones;
	Node nodes[200];

	char file_path[258];
	uint mesh_index = 0;
	uint mesh_file_type = 0;

    char label[256];
	Mat4x4 globalInverse;

	bool loaded = false;

	void _free();
	void initMesh();
	
};

struct AnimChannel {

	char bone_name[128];

	uint pos_keys_num = 0;
	uint scale_keys_num = 0;
	uint rot_keys_num = 0;

	AnimVec3* pos;
	AnimVec3* scale;
	AnimQuaternion* rot;
};

struct Animation {

	char label[120];
	float duration;
	uint channels_num;
	float tps;

	AnimChannel* channels;
};

void addMesh(Mesh mesh);

Mesh getMesh(uint pos);

Mesh* getMeshPtr(uint pos);

uint getMeshesSize();

uint getMeshID(const char* label);

void processMesh(Mesh* mesh, Vertex* vertsf, uint* indices);
void processMesh(Mesh* mesh, Vertex* vertsf, uint* indices, uint vertices_count, uint indices_count);

void processMesh(Mesh* mesh, Vertex* vertsf);
    



void drawMesh(Mesh mesh);
void drawMeshInstanced(Mesh mesh, uint offsets);


void drawMeshNI(Mesh mesh);
void drawMeshInstancedNI(Mesh mesh, uint offsets);

void processMeshSkybox(Mesh* mesh, Vector3* vertsf);