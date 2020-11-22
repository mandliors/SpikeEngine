#pragma once

#include "SDL_mixer.h"
#include <string>
#include <vector>

namespace Spike {

	class Sound
	{
	public:
		Sound(Mix_Chunk* chunk);

		void Play(bool loop = false);
		void Loop(int amount = -1);
		void Stop();
		void SetVolume(int volume);
		void Mute(bool mute = true);
		void Unmute();

		void __UNLOAD();

	private:
		Mix_Chunk* m_Chunk = nullptr;
		int m_Channel = -1;
		int m_Volume = 100;
		bool m_Muted = false;
	};
}