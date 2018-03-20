#include <AL/al.h>
#include <AL/alc.h>

#include <glew.h>

#include <iostream>
#include <string>
#include "../includes/zs-errors-checker.h"


bool ZSpire::CheckALCError()
{
	ALenum errCode;
	std::string err = "ALC error: ";
	if((errCode = alcGetError(NULL)) != ALC_NO_ERROR)
	{
		err += (char *)alcGetString(0, errCode);
		printf("%s", err.data());
		return AL_FALSE;
	}
	return AL_TRUE;
}

bool ZSpire::CheckALError()
{
	ALenum errCode;
	std::string err = "OpenAL error: ";
	if ((errCode = alGetError()) != AL_NO_ERROR)
	{
		err += (char *)alGetString(errCode);
		printf("%s", err.data());
		return AL_FALSE;
	}
	return AL_TRUE;
}

void ZSpire::checkCompileErrors(unsigned int shader, const char* type)
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