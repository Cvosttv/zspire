#include <AL/al.h>
#include <AL/alc.h>

#include "../includes/zs-math.h"

#include "../includes/zs-audio-manager.h"

ALCdevice* AL_DEVICE;
ALCcontext* AL_CONTEXT;

bool ZSpire::InitOpenAL_Device(){
	AL_DEVICE = alcOpenDevice(0);

	if (!AL_DEVICE) return false;

	AL_CONTEXT = alcCreateContext(AL_DEVICE, 0);

	if (!alcMakeContextCurrent(AL_CONTEXT)) return false;

	return true;	
}

void ZSpire::setListenerPosition(ZSVECTOR3 position) {
	alListener3f(AL_POSITION, position.X, position.Y, position.Z);
}
void ZSpire::setListenerOrientation(ZSVECTOR3 target, ZSVECTOR3 up) {
	ALfloat listenerOri[] = { target.X, target.Y, target.Z, up.X, up.Y, up.Z };
	alListenerfv(AL_ORIENTATION, listenerOri);
}

void ZSpire::DestroyAL() {
	alcDestroyContext(AL_CONTEXT);
	alcCloseDevice(AL_DEVICE);
}