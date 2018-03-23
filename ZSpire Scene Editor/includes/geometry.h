
struct Bone{
    char label[120];
	ZSMATRIX4x4 offset;
};

struct Node {
	char label[120];
	unsigned int* node_children;

	unsigned int children_num = 0;

	ZSMATRIX4x4 offset;

};

class Mesh{
public:
	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;

	unsigned int vertices_count = 0;
	unsigned int indices_count = 0;
	unsigned int bones_count = 0;
	unsigned int nodes_count;

    Bone* bones;
	Node nodes[200];

	char file_path[258];
	unsigned int mesh_index = 0;
	unsigned int mesh_file_type = 0;

    char label[256];
	ZSMATRIX4x4 globalInverse;

	bool loaded = false;

	void _free();
	void initMesh();
	
};


void processMesh(Mesh* mesh, ZSVERTEX* vertsf, unsigned int* indices);
void processMesh(Mesh* mesh, ZSVERTEX* vertsf, unsigned int* indices, unsigned int vertices_count, unsigned int indices_count);

void processMesh(Mesh* mesh, ZSVERTEX* vertsf);
    



void drawMesh(Mesh mesh);
void drawMeshInstanced(Mesh mesh, unsigned int offsets);


void drawMeshNI(Mesh mesh);
void drawMeshInstancedNI(Mesh mesh, unsigned int offsets);

void processMeshSkybox(Mesh* mesh, ZSVECTOR3* vertsf);