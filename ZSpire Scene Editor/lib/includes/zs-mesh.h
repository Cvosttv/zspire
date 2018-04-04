#ifndef ZSMESH
#define ZSMESH
#endif

#ifndef ZSMATH
#include "zs-math.h"
#endif


#define MESH_NO_INDICES -1

namespace ZSpire {
	class Mesh {
	protected:
		unsigned int meshVAO;
		unsigned int meshVBO;
		unsigned int meshIBO;

		unsigned int IndicesCount;
		int VerticesCount = MESH_NO_INDICES;
	public:
		unsigned int resource_index = 0;
		char resource_string[64];
		//ZSResourceDesc resource_desc;
		void InitializeMesh();
		void Release();
		void Draw();
		void processMesh(ZSVERTEX* vertsf, unsigned int* indices, unsigned int verticesCount, unsigned int indicesCount);
		void processMesh(ZSVERTEX* vertsf, unsigned int verticesCount );
	};

	void createPlane2D();
	Mesh* getPlaneMesh2D();

}