#include <AL/al.h>
#include <AL/alc.h>

#include <string>
#include "../includes/zs-errors-checker.h"


ALboolean ZSpire::CheckALCError()
{
	ALenum errCode;
	std::string err = "ALC error: ";
	if((errCode = alcGetError(NULL)) != ALC_NO_ERROR)
	{
		err += (char *)alcGetString(0, errCode);
		//ERRMSG(Err.data());
		printf("%s", err.data());
		return AL_FALSE;
	}
	return AL_TRUE;
}

ALboolean ZSpire::CheckALError()
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