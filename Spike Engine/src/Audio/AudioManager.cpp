#include "AudioManager.h"

namespace Spike {

	std::vector<Sound*> AudioManager::s_Sounds = {};
	std::vector<Music*> AudioManager::s_Musics = {};

	Sound& AudioManager::LoadSound(const std::string& path)
	{
		Mix_Chunk* chunk = Mix_LoadWAV(path.c_str());
		Sound* sound = new Sound(chunk);
		s_Sounds.push_back(sound);
		return *sound;
	}
	Music& AudioManager::LoadMusic(const std::string& path)
	{
		Mix_Music* mus = Mix_LoadMUS(path.c_str());
		Music* music = new Music(mus);
		s_Musics.push_back(music);
		return *music;
	}
	void AudioManager::Close()
	{
		//Delete sounds
		for (auto sound : s_Sounds)
		{
			sound->__UNLOAD();
			delete sound;
		}

		//Delete musics
		for (auto music : s_Musics)
		{
			music->__UNLOAD();
			delete music;
		}
	}
}