#define _CRT_SECURE_NO_WARNINGS

#include <AL/al.h>
#include <AL/alc.h>	
#include <AL/alut.h>

#include "../includes/zs-errors-checker.h"

#include "../includes/zs-math.h"
#include "../includes/zs-audio-source.h"



bool ZSpire::AudioSource::Open(const char* Filename)
{
	

	//mLooped = Looped;

	alGenSources(1, &mSourceID);
	if (!CheckALError()) return false;

	alGenBuffers(1, &mBufferID);


	alSourcef(mSourceID, AL_PITCH, 1.0f);
	alSourcef(mSourceID, AL_GAIN, 1.0f);
	alSource3f(mSourceID, AL_POSITION, 0,0,0);
	alSource3f(mSourceID, AL_VELOCITY, 0,0,0);
	//alSourcei(mSourceID, AL_LOOPING, mLooped);

	
	ALsizei size, freq;
	ALenum format;
	ALvoid *data;
	ALboolean loop = AL_FALSE;
	alutLoadWAVFile((char*)Filename, &format, &data, &size, &freq, &loop);

	alBufferData(mBufferID, format, data, size, freq);

	alSourcei(mSourceID, AL_BUFFER, mBufferID);

		return true;
}

void ZSpire::AudioSource::setGain(float gain){
	alSourcef(mSourceID, AL_GAIN, gain);
}

void ZSpire::AudioSource::setLoopingEnabled(bool enabled) {
	alSourcei(mSourceID, AL_LOOPING, enabled);
}

void ZSpire::AudioSource::Play()
{
	alSourcePlay(mSourceID);
	CheckALError();
}



void ZSpire::AudioSource::Stop()
{
	alSourceStop(mSourceID);
}

void ZSpire::AudioSource::setTranslation(ZSVECTOR3 position)
{
	alSource3f(mSourceID, AL_POSITION, position.X, position.Y, position.Z);
}


void ZSpire::AudioSource::Close()
{
	alSourceStop(mSourceID);
	if (alIsSource(mSourceID)) alDeleteSources(1, &mSourceID);
	
}