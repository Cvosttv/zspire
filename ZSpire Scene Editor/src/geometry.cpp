typedef unsigned int uint;

#include "../includes/zs-math.h"
#include <glew.h>

#include <vector>
#include "../includes/geometry.h"

void Mesh::_free() {
	if (this->loaded == true) {
		glDeleteVertexArrays(1, &this->VAO);
		glDeleteBuffers(1, &this->VBO);
		glDeleteBuffers(1, &this->EBO);

		loaded = false;
	}
}

void Mesh::initMesh() {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

}


void processMesh(Mesh* mesh, ZSVERTEX* vertsf, uint* indices) {


	
	glBindVertexArray(mesh->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->VBO);
	
	glBufferData(GL_ARRAY_BUFFER, sizeof(ZSVERTEX) * mesh->vertices_count, vertsf, GL_STATIC_DRAW);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * mesh->indices_count, indices, GL_STATIC_DRAW);
	
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
	glVertexAttribIPointer(5, 4, GL_INT, sizeof(ZSVERTEX), (void*)(sizeof(uint) * 14));
	glEnableVertexAttribArray(5);
	glVertexAttribIPointer(6, 4, GL_INT, sizeof(ZSVERTEX), (void*)(sizeof(uint) * 18));
	glEnableVertexAttribArray(6);
	glVertexAttribIPointer(7, 4, GL_INT, sizeof(ZSVERTEX), (void*)(sizeof(uint) * 22));
	glEnableVertexAttribArray(7);
	//Bone weights
	glVertexAttribPointer(8, 4, GL_FLOAT, GL_FALSE, sizeof(ZSVERTEX), (void*)(sizeof(float) * 26));
	glEnableVertexAttribArray(8);
	glVertexAttribPointer(9, 4, GL_FLOAT, GL_FALSE, sizeof(ZSVERTEX), (void*)(sizeof(float) * 30));
	glEnableVertexAttribArray(9);
	glVertexAttribPointer(10, 4, GL_FLOAT, GL_FALSE, sizeof(ZSVERTEX), (void*)(sizeof(float) * 34));
	glEnableVertexAttribArray(10);
	

}

void processMesh(Mesh* mesh, ZSVERTEX* vertsf, uint* indices, uint vertices_count, uint indices_count) {


	mesh->indices_count = indices_count;
	mesh->vertices_count = vertices_count;
	processMesh(mesh, vertsf, indices);
}

void processMesh(Mesh* mesh, ZSVERTEX* vertsf) {


	
	glBindVertexArray(mesh->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(ZSVERTEX) * mesh->vertices_count, vertsf, GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(ZSVERTEX), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(ZSVERTEX), (void*)(sizeof(float) * 3));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(ZSVERTEX), (void*)(sizeof(float) * 5));
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(ZSVERTEX), (void*)(sizeof(float) * 8));
	glEnableVertexAttribArray(3);

	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(ZSVERTEX), (void*)(sizeof(float) * 11));
	glEnableVertexAttribArray(4);

	//Bone IDS
	glVertexAttribIPointer(5, 4, GL_INT, sizeof(ZSVERTEX), (void*)(sizeof(uint) * 14));
	glEnableVertexAttribArray(5);
	glVertexAttribIPointer(6, 4, GL_INT, sizeof(ZSVERTEX), (void*)(sizeof(uint) * 18));
	glEnableVertexAttribArray(6);
	glVertexAttribIPointer(7, 4, GL_INT, sizeof(ZSVERTEX), (void*)(sizeof(uint) * 22));
	glEnableVertexAttribArray(7);
	//Bone weights
	glVertexAttribPointer(8, 4, GL_FLOAT, GL_FALSE, sizeof(ZSVERTEX), (void*)(sizeof(float) * 26));
	glEnableVertexAttribArray(8);
	glVertexAttribPointer(9, 4, GL_FLOAT, GL_FALSE, sizeof(ZSVERTEX), (void*)(sizeof(float) * 30));
	glEnableVertexAttribArray(9);
	glVertexAttribPointer(10, 4, GL_FLOAT, GL_FALSE, sizeof(ZSVERTEX), (void*)(sizeof(float) * 34));
	glEnableVertexAttribArray(10);
	
}




void drawMesh(Mesh mesh) {

	glBindVertexArray(mesh.VAO);

	glDrawElements(GL_TRIANGLES, mesh.indices_count, GL_UNSIGNED_INT, 0);
}
void drawMeshInstanced(Mesh mesh, uint offsets) {

	glBindVertexArray(mesh.VAO);

	glDrawElementsInstanced(GL_TRIANGLES, mesh.indices_count, GL_UNSIGNED_INT, 0, offsets);
}


void drawMeshNI(Mesh mesh) {

	glBindVertexArray(mesh.VAO);

	glDrawArrays(GL_TRIANGLES, 0, mesh.vertices_count); // ������� � ������� 0, ����� 3 ������� -> ���� �����������
}

void drawMeshInstancedNI(Mesh mesh, uint offsets) {

	glBindVertexArray(mesh.VAO);

	glDrawArraysInstanced(GL_TRIANGLES, 0, mesh.vertices_count, offsets); // ������� � ������� 0, ����� 3 ������� -> ���� �����������
}

void processMeshSkybox(Mesh* mesh, ZSVECTOR3* vertsf) {



	glBindVertexArray(mesh->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(ZSVECTOR3) * 36, vertsf, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(ZSVECTOR3), (void*)0);
	glEnableVertexAttribArray(0);


}