#ifdef _WIN32
#include <glew.h>
#endif

#ifdef __linux__
#include <GL/glew.h>
#endif

#include <fstream>
#include <sstream>
#include <iostream>

#include "../includes/zs-errors-checker.h"
#include "../includes/zs-math.h"

#include "../includes/zs-transform.h"

#include "../includes/zs-camera.h"

#include "../includes/zs-light.h"

#include "../includes/zs-shader.h"

void ZSpire::Shader::InitializeShader() {
	VS_GL_ID = glCreateShader(GL_VERTEX_SHADER);
	FS_GL_ID = glCreateShader(GL_FRAGMENT_SHADER);

	SHADER_GL_ID = glCreateProgram();
}

void ZSpire::Shader::Use() {
	glUseProgram(this->SHADER_GL_ID);
}

void ZSpire::Shader::bindUniforms() {
	setUniformInt("diffuse", 0);
	setUniformInt("normal", 1);

	setUniformInt("b_diffuse", 5);
	setUniformInt("b_normal", 6);
	setUniformInt("b_frag_pos", 7);
}

bool ZSpire::Shader::compileFromBuffer(const char* VS_CONTENT, const char* FS_CONTENT) {
	glShaderSource(this->VS_GL_ID, 1, &VS_CONTENT, NULL);
	glCompileShader(this->VS_GL_ID);

	checkCompileErrors(VS_GL_ID, "VERTEX");

	glShaderSource(this->FS_GL_ID, 1, &FS_CONTENT, NULL);
	glCompileShader(this->FS_GL_ID);

	checkCompileErrors(FS_GL_ID, "FRAGMENT");

	glAttachShader(SHADER_GL_ID, VS_GL_ID);
	glAttachShader(SHADER_GL_ID, FS_GL_ID);
	glLinkProgram(SHADER_GL_ID);

	bindUniforms();

	return true;
}

bool ZSpire::Shader::compileFromFile(const char* VS_SHADER_PATH, const char* FS_SHADER_PATH) {

	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	// ensure ifstream objects can throw exceptions:
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		// open files
		vShaderFile.open(VS_SHADER_PATH);
		fShaderFile.open(FS_SHADER_PATH);
		std::stringstream vShaderStream, fShaderStream;
		// read file's buffer contents into streams
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		// close file handlers
		vShaderFile.close();
		fShaderFile.close();
		// convert stream into string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		return false;
	}
	const char* vShaderCode = vertexCode.c_str();
	const char * fShaderCode = fragmentCode.c_str();

	int Lengths[1];
	Lengths[0] = (GLint)strlen(vShaderCode);
	glShaderSource(this->VS_GL_ID, 1, &vShaderCode, Lengths);
	glCompileShader(this->VS_GL_ID);

	checkCompileErrors(VS_GL_ID, "VERTEX", VS_SHADER_PATH);

	Lengths[0] = (GLint)strlen(fShaderCode);
	glShaderSource(this->FS_GL_ID, 1, &fShaderCode, Lengths);
	glCompileShader(this->FS_GL_ID);	

	checkCompileErrors(FS_GL_ID, "FRAGMENT", FS_SHADER_PATH);

	glAttachShader(SHADER_GL_ID, VS_GL_ID);
	glAttachShader(SHADER_GL_ID, FS_GL_ID);
	glLinkProgram(SHADER_GL_ID);

	checkCompileErrors(FS_GL_ID, "PROGRAM");

	//Clean up
	glDeleteShader(VS_GL_ID);
	glDeleteShader(FS_GL_ID);

	bindUniforms();

	return true;
}



void ZSpire::Shader::setUniformInt(const char* uniform_string, int value){
	Use();
	unsigned int uniform_id = glGetUniformLocation(this->SHADER_GL_ID, uniform_string);
	glUniform1i(uniform_id, value);
}

void ZSpire::Shader::setUniformFloat(const char* uniform_string, float value) {
	Use();
	unsigned int uniform_id = glGetUniformLocation(this->SHADER_GL_ID, uniform_string);
	glUniform1f(uniform_id, value);
}

void ZSpire::Shader::setUniformColor3(const char* uniform, ZSRGBCOLOR color) {
	Use();
	unsigned int uniform_id = glGetUniformLocation(this->SHADER_GL_ID, uniform);
	glUniform3f(uniform_id, color.gl_r, color.gl_g, color.gl_b);

}

void ZSpire::Shader::setUniformMat4x4(const char* uniform_string, ZSMATRIX4x4 value) {
	Use();
	unsigned int uniform_id = glGetUniformLocation(this->SHADER_GL_ID, uniform_string);
	glUniformMatrix4fv(uniform_id, 1, GL_FALSE, &value.m[0][0]);
}

void ZSpire::Shader::setUniformVec3(const char* uniform_string, ZSVECTOR3 value) {
	Use();
	unsigned int uniform_id = glGetUniformLocation(this->SHADER_GL_ID, uniform_string);
	glUniform3f(uniform_id, value.X, value.Y, value.Z);
}

void ZSpire::Shader::setTransform( ZSpire::Transform* translation) {
	unsigned int uniform_id = glGetUniformLocation(this->SHADER_GL_ID, "object_transform");
	glUniformMatrix4fv(uniform_id, 1, GL_FALSE, &translation->translation_matrix.m[0][0]);
}

void ZSpire::Shader::updateCamera(){
	unsigned int proj_id = glGetUniformLocation(this->SHADER_GL_ID, "cam_projection");
	unsigned int view_id = glGetUniformLocation(this->SHADER_GL_ID, "cam_view");

	glUniformMatrix4fv(proj_id, 1, GL_FALSE, &getCameraProjectionMatrix().m[0][0]);
	glUniformMatrix4fv(view_id, 1, GL_FALSE, &getCameraViewMatrix().m[0][0]);
}

void ZSpire::Shader::setLight(unsigned int index, Light* light) {
	std::string pos;
	pos = "lights[" + std::to_string(index) + "].pos";

	std::string color;
	pos = "lights[" + std::to_string(index) + "].color";

	std::string dir;
	pos = "lights[" + std::to_string(index) + "].dir";

	setUniformVec3(pos.c_str(), light->getPosition());
	setUniformVec3(dir.c_str(), light->getDirection());
	setUniformVec3(pos.c_str(), light->getPosition());
}