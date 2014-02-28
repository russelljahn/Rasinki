#include <stdio.h>
#include <stdlib.h>
#include "SDL.h"
#include "SDL_mixer.h"

class SoundManager {
	public:
		SoundManager();
		~SoundManager();
		void playSound();
	private:
		int mAudioRate;
		Uint16 mAudioFormat;
		int mAudioChannels;
		int mAudioBuffers;

		Mix_Chunk* sound;
};