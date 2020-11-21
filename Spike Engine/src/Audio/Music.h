#pragma once

#include "SDL_mixer.h"
#include <string>
#include <vector>

namespace Spike {

	class Music
	{
	public:
		Music(Mix_Music* music);
		~Music();

		void Play(bool loop = false);
		void SafePlay(bool loop = false);
		void Loop(int amount = -1);
		void Pause();
		void Resume();
		void Stop();
		void SetVolume(int volume);
		void Mute(bool mute = true);
		void Unmute();
		
		void __UNLOAD();

	//private:
		Mix_Music* m_Music = nullptr;
		int m_Volume = 100;
		bool m_Muted = false;
	};
}