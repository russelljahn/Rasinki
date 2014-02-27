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
	assert (sound != NULL);
}
SoundManager::~SoundManager() {
	Mix_CloseAudio();
	SDL_Quit();
}
void SoundManager::playSound() {
	Mix_PlayChannel(-1, sound, 1);
}