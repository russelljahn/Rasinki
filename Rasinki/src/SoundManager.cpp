#include "SoundManager.h"
#include <assert.h>

SoundManager::SoundManager() {
	mAudioRate = 22050;
	mAudioFormat = AUDIO_S16;
	mAudioChannels=2;
	mAudioBuffers = 4096;

	SDL_Init(SDL_INIT_AUDIO);

	if (Mix_OpenAudio(mAudioRate, mAudioFormat, mAudioChannels, mAudioBuffers))
		assert(false);
	sound = Mix_LoadWAV("src/sound.wav");
	sound2 = Mix_LoadWAV("src/coin2.wav");
	sound3 = Mix_LoadWAV("src/glass_shatter2.wav");
	assert (sound != NULL);

	soundEnabled = true;
}
SoundManager::~SoundManager() {
	Mix_CloseAudio();
	SDL_Quit();
}
void SoundManager::playSound1() {
	if(soundEnabled) {
		Mix_PlayChannel(-1, sound, 0);
	}
}

void SoundManager::playSound2() {
	if(soundEnabled) {
		Mix_PlayChannel(-1, sound2, 0);
	}
}

void SoundManager::playSound3() {
	if(soundEnabled) {
		Mix_PlayChannel(-1, sound3, 0);
	}
}

bool SoundManager::toggleSound() {
	soundEnabled = !soundEnabled;
}