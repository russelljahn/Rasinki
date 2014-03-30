#include <stdio.h>
#include <stdlib.h>
#include "SDL.h"
#include "SDL_mixer.h"

class SoundManager {
	public:
		SoundManager();
		~SoundManager();
		void playSound1();
		void playSound2();
		void playSound3();
		bool toggleSound();

	private:
		int mAudioRate;
		Uint16 mAudioFormat;
		int mAudioChannels;
		int mAudioBuffers;

		bool soundEnabled;

		Mix_Chunk* sound;
		Mix_Chunk* sound2;
		Mix_Chunk* sound3;
};