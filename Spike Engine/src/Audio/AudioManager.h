#pragma once

#include "Sound.h"
#include "Music.h"
#include <string>
#include <vector>

namespace Spike {

	class AudioManager
	{
	public:
		AudioManager() = delete;

		static Sound& LoadSound(const std::string& path);
		static Music& LoadMusic(const std::string& path);
		static void Close();

	private:
		static std::vector<Sound*> s_Sounds;
		static std::vector<Music*> s_Musics;
	};
}