#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "../includes/zs-math.h"

#include "../includes/zs-mesh.h"

#include "../includes/zs-mesh-loader.h"

Assimp::Importer importer;
unsigned int loadflags = aiProcess_CalcTangentSpace | aiProcess_Triangulate;
unsigned int processed_meshes = 0;
ZSpire::Mesh* results_ptr;

void processMesh(aiMesh* mesh, const aiScene* scene) {
	unsigned int vertices = mesh->mNumVertices;
	unsigned int faces = mesh->mNumFaces;
	unsigned int bones = mesh->mNumBones;

	ZSVERTEX* vertices_arr = (ZSVERTEX*)malloc(sizeof(ZSVERTEX) * vertices);
	unsigned int* indices = (unsigned int*)malloc(sizeof(unsigned int) * faces * 3);

	for (unsigned int v = 0; v < vertices; v ++) {
		aiVector3D vertex_pos = mesh->mVertices[v];
		aiVector3D vertex_normal = mesh->mNormals[v];
		aiVector3D vertex_tangent = mesh->mTangents[v];
		aiVector3D vertex_bitangent = mesh->mBitangents[v];

		float U = mesh->mTextureCoords[0][v].x;
		float V = mesh->mTextureCoords[0][v].y;

		vertices_arr[v] = ZSVERTEX(ZSVECTOR3(vertex_pos.x, vertex_pos.y, vertex_pos.z), ZSVECTOR2(U, V),
			ZSVECTOR3(vertex_normal.x, vertex_normal.y, vertex_normal.z), ZSVECTOR3(vertex_tangent.x, vertex_tangent.y, vertex_tangent.z),
			ZSVECTOR3(vertex_bitangent.x, vertex_bitangent.y, vertex_bitangent.z)
			);
	}

	for (unsigned int i = 0; i < faces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			indices[i * 3 + j] = face.mIndices[j];
	}

	results_ptr[processed_meshes].InitializeMesh();
	results_ptr[processed_meshes].processMesh(vertices_arr, indices, vertices, faces * 3);
	processed_meshes += 1;

}

void processNode(aiNode* node, const aiScene* scene) {
	unsigned int child_nodes_amount = node->mNumChildren;
	unsigned int meshes_amount = node->mNumMeshes;

	//Iterate child nodes
	for (unsigned int i = 0; i < child_nodes_amount; i ++) {
		processNode(node->mChildren[i], scene);
	}
	//Iterate meshes
	for (unsigned int i = 0; i < meshes_amount; i ++) {
		processMesh(scene->mMeshes[node->mMeshes[i]], scene);
	}

}

ZSpire::Mesh* ZSpire::LoadMeshFromBuffer(void* buffer, size_t size) {

	Mesh* result;

	const aiScene* scene = importer.ReadFileFromMemory(buffer, size, loadflags);

	result = (Mesh*)malloc(sizeof(Mesh) * scene->mNumMeshes);

	results_ptr = result;

	processNode(scene->mRootNode, scene);

	
	return result;
}

ZSpire::Mesh* ZSpire::LoadMeshesFromFile(const char* file_path){

	Mesh* result;
	
	const aiScene* scene = importer.ReadFile(file_path, loadflags);

	result = (Mesh*)malloc(sizeof(Mesh) * scene->mNumMeshes);

	results_ptr = result;

	processNode(scene->mRootNode, scene);


	return result;

}