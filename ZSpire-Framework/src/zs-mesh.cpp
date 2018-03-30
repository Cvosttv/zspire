#ifdef _WIN32
#include <glew.h>
#endif

#ifdef __linux__
#include <GL/glew.h>
#endif

#include "../includes/zs-resource.h"
#include "../includes/zs-math.h"
#include "../includes/zs-mesh.h"

ZSVERTEX vertices[] = {
	// positions              // texture coords
	ZSVERTEX(ZSVECTOR3(1.0f,  1.0f, 0.0f),		ZSVECTOR2(1.0f, 1.0f)),   // top right
	ZSVERTEX(ZSVECTOR3(1.0f, -1.0f, 0.0f),		ZSVECTOR2(1.0f, 0.0f)),   // bottom right
	ZSVERTEX(ZSVECTOR3(-1.0f, -1.0f, 0.0f),		ZSVECTOR2(0.0f, 0.0f)),   // bottom left
	ZSVERTEX(ZSVECTOR3(-1.0f,  1.0f, 0.0f),		ZSVECTOR2(0.0f, 1.0f))   // top left 
};
unsigned int ind[] = { 0,1,2, 0,2,3 };

ZSpire::Mesh plane2D;

void ZSpire::createPlane2D() {
	plane2D.InitializeMesh();

	plane2D.processMesh(vertices, ind, 4, 6);

}

ZSpire::Mesh* ZSpire::getPlaneMesh2D(){
	return &plane2D;
}

void ZSpire::Mesh::InitializeMesh() {
	glGenVertexArrays(1, &this->meshVAO);
	glGenBuffers(1, &this->meshVBO);
	glGenBuffers(1, &this->meshIBO);	
}

void ZSpire::Mesh::Release() {
	glDeleteVertexArrays(1, &this->meshVAO);
	glDeleteBuffers(1, &this->meshVBO);
	glDeleteBuffers(1, &this->meshIBO);
}

void ZSpire::Mesh::Draw() {
	glBindVertexArray(meshVAO);
	if(IndicesCount == MESH_NO_INDICES){
		glDrawArrays(GL_TRIANGLES, 0, VerticesCount);
	}
	else {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshIBO);
		glDrawElements(GL_TRIANGLES, IndicesCount, GL_UNSIGNED_INT, 0);
	}
}


void ZSpire::Mesh::processMesh(ZSVERTEX* vertsf, unsigned int* indices, unsigned int verticesCount, unsigned int indicesCount) {

	this->VerticesCount = verticesCount;
	this->IndicesCount = indicesCount;

	glBindVertexArray(meshVAO);
	glBindBuffer(GL_ARRAY_BUFFER, meshVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(ZSVERTEX) * VerticesCount, vertsf, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshIBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * IndicesCount, indices, GL_STATIC_DRAW);
	//Vertex Position 3 floats
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(ZSVERTEX), (void*)0);
	glEnableVertexAttribArray(0);
	//Vertex UV 2 floats
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(ZSVERTEX), (void*)(sizeof(float) * 3));
	glEnableVertexAttribArray(1);
	//Vertex Normals 3 floats
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(ZSVERTEX), (void*)(sizeof(float) * 5));
	glEnableVertexAttribArray(2);
	//Vertex Tangents 3 floats
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(ZSVERTEX), (void*)(sizeof(float) * 8));
	glEnableVertexAttribArray(3);
	//Vertex Bitangents 3 floats
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(ZSVERTEX), (void*)(sizeof(float) * 11));
	glEnableVertexAttribArray(4);
	//Bone IDS
	
	glVertexAttribIPointer(5, 4, GL_INT, sizeof(ZSVERTEX), (void*)(sizeof(unsigned int) * 14));
	glEnableVertexAttribArray(5);
	glVertexAttribIPointer(6, 4, GL_INT, sizeof(ZSVERTEX), (void*)(sizeof(unsigned int) * 18));
	glEnableVertexAttribArray(6);
	glVertexAttribIPointer(7, 4, GL_INT, sizeof(ZSVERTEX), (void*)(sizeof(unsigned int) * 22));
	glEnableVertexAttribArray(7);
	//Bone weights
	glVertexAttribPointer(8, 4, GL_FLOAT, GL_FALSE, sizeof(ZSVERTEX), (void*)(sizeof(float) * 26));
	glEnableVertexAttribArray(8);
	glVertexAttribPointer(9, 4, GL_FLOAT, GL_FALSE, sizeof(ZSVERTEX), (void*)(sizeof(float) * 30));
	glEnableVertexAttribArray(9);
	glVertexAttribPointer(10, 4, GL_FLOAT, GL_FALSE, sizeof(ZSVERTEX), (void*)(sizeof(float) * 34));
	glEnableVertexAttribArray(10);


}

void ZSpire::Mesh::processMesh(ZSVERTEX* vertsf, unsigned int verticesCount) {
	this->IndicesCount = MESH_NO_INDICES;
	this->VerticesCount = verticesCount;

	glBindVertexArray(meshVAO);
	glBindBuffer(GL_ARRAY_BUFFER, meshVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(ZSVERTEX) * verticesCount, vertsf, GL_STATIC_DRAW);


	//Vertex Position 3 floats
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(ZSVERTEX), (void*)0);
	glEnableVertexAttribArray(0);
	//Vertex UV 2 floats
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(ZSVERTEX), (void*)(sizeof(float) * 3));
	glEnableVertexAttribArray(1);
	//Vertex Normals 3 floats
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(ZSVERTEX), (void*)(sizeof(float) * 5));
	glEnableVertexAttribArray(2);
	//Vertex Tangents 3 floats
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(ZSVERTEX), (void*)(sizeof(float) * 8));
	glEnableVertexAttribArray(3);
	//Vertex Bitangents 3 floats
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(ZSVERTEX), (void*)(sizeof(float) * 11));
	glEnableVertexAttribArray(4);
	//Bone IDS

	glVertexAttribIPointer(5, 4, GL_INT, sizeof(ZSVERTEX), (void*)(sizeof(unsigned int) * 14));
	glEnableVertexAttribArray(5);
	glVertexAttribIPointer(6, 4, GL_INT, sizeof(ZSVERTEX), (void*)(sizeof(unsigned int) * 18));
	glEnableVertexAttribArray(6);
	glVertexAttribIPointer(7, 4, GL_INT, sizeof(ZSVERTEX), (void*)(sizeof(unsigned int) * 22));
	glEnableVertexAttribArray(7);
	//Bone weights
	glVertexAttribPointer(8, 4, GL_FLOAT, GL_FALSE, sizeof(ZSVERTEX), (void*)(sizeof(float) * 26));
	glEnableVertexAttribArray(8);
	glVertexAttribPointer(9, 4, GL_FLOAT, GL_FALSE, sizeof(ZSVERTEX), (void*)(sizeof(float) * 30));
	glEnableVertexAttribArray(9);
	glVertexAttribPointer(10, 4, GL_FLOAT, GL_FALSE, sizeof(ZSVERTEX), (void*)(sizeof(float) * 34));
	glEnableVertexAttribArray(10);

}