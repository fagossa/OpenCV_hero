//#include "windows.h"
#include "stdio.h"
//#include "conio.h"

#include "cv.h"
#include "highgui.h"
#include "MusicManager.h"

#include "fmod.hpp"
#include "fmod_errors.h"

MusicManager::MusicManager(void) {
	channel = 0;
	system = 0;
}

MusicManager::~MusicManager(void) {
}

void MusicManager::init(void) {

}
void MusicManager::playBlackground(void) {
	if(!system) {
		result = FMOD_System_Create(&this->system);
		result = FMOD_System_Init(this->system, 32, FMOD_INIT_NORMAL, NULL);
		initSounds();
	}
	result = FMOD_System_PlaySound(this->system, FMOD_CHANNEL_FREE, this->sound1, 0, &channel);
}

void MusicManager::playHit(void) {
	if(!system) {
		result = FMOD_System_Create(&this->system);
		result = FMOD_System_Init(this->system, 32, FMOD_INIT_NORMAL, NULL);
		initSounds();
	}
	result = FMOD_System_PlaySound(this->system, FMOD_CHANNEL_FREE, this->sound2, 0, &channel);
}

void MusicManager::initSounds() {
	result = FMOD_System_CreateSound(this->system, "drumloop.wav", FMOD_HARDWARE, 0, &this->sound1);
	result = FMOD_System_CreateSound(this->system, "swish.wav", FMOD_HARDWARE, 0, &this->sound2);
	result = FMOD_Sound_SetMode(this->sound2, FMOD_LOOP_OFF);
}

void MusicManager::release(void) {
	result = FMOD_Sound_Release(this->sound1);
    result = FMOD_System_Close(this->system);
    result = FMOD_System_Release(this->system);
}
