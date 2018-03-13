#include <glew.h>

#include <fstream>
#include <sstream>
#include <iostream>

#include "../includes/zs-math.h"
#include "../includes/zs-transform.h"

#include "../includes/zs-shader.h"

void ZSpire::Shader::InitializeShader() {
	VS_GL_ID = glCreateShader(GL_VERTEX_SHADER);
	FS_GL_ID = glCreateShader(GL_FRAGMENT_SHADER);

	SHADER_GL_ID = glCreateProgram();
}

void ZSpire::Shader::Use() {
	glUseProgram(this->SHADER_GL_ID);
}

bool ZSpire::Shader::compileFromBuffer(const char* VS_CONTENT, const char* FS_CONTENT) {
	glShaderSource(this->VS_GL_ID, 1, &VS_CONTENT, NULL);
	glCompileShader(this->VS_GL_ID);

	glShaderSource(this->FS_GL_ID, 1, &FS_CONTENT, NULL);
	glCompileShader(this->FS_GL_ID);

	glAttachShader(SHADER_GL_ID, VS_GL_ID);
	glAttachShader(SHADER_GL_ID, FS_GL_ID);
	glLinkProgram(SHADER_GL_ID);

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

	checkCompileErrors(VS_GL_ID, "VERTEX");

	Lengths[0] = (GLint)strlen(fShaderCode);
	glShaderSource(this->FS_GL_ID, 1, &fShaderCode, Lengths);
	glCompileShader(this->FS_GL_ID);	

	checkCompileErrors(FS_GL_ID, "FRAGMENT");

	glAttachShader(SHADER_GL_ID, VS_GL_ID);
	glAttachShader(SHADER_GL_ID, FS_GL_ID);
	glLinkProgram(SHADER_GL_ID);

	checkCompileErrors(FS_GL_ID, "PROGRAM");

	//Clean up
	glDeleteShader(VS_GL_ID);
	glDeleteShader(FS_GL_ID);

	return true;
}

void ZSpire::Shader::checkCompileErrors(GLuint shader, const char* type)
{
	GLint success;
	GLchar infoLog[1024];
	if (strcmp(type, "PROGRAM"))
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
}

void ZSpire::Shader::setUniformInt(const char* uniform_string, int value){
	Use();
	unsigned int uniform_id = glGetUniformLocation(this->SHADER_GL_ID, uniform_string);
	glUniform1i(uniform_id, value);
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

void ZSpire::Shader::setTransform( ZSpire::Transform translation) {
	unsigned int uniform_id = glGetUniformLocation(this->SHADER_GL_ID, "object_transform");
	glUniformMatrix4fv(uniform_id, 1, GL_FALSE, &translation.translation_matrix.m[0][0]);
}