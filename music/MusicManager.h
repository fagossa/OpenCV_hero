#pragma once
#include "opencv2/highgui/highgui.hpp"

//#include "fmod.hpp"
//#include "fmod_errors.h"

/**
 *
 */
class MusicManager {
private:
    /*
	FMOD_SYSTEM      *system;
	FMOD_SOUND       *sound1;
	FMOD_SOUND       *sound2;
	FMOD_CHANNEL     *channel;
	FMOD_RESULT       result;
    */
	void initSounds(void);
public:
	void init(void);
	void playBlackground(void);
	void playHit(void);
	void release(void);
	MusicManager(void);
	~MusicManager(void);
};
