#pragma once

#include "SDL.h"
#include <map>
#include <string>

namespace Spike {

	struct Time
	{
		Time() = delete;
		~Time() = default;

		static void Bind(const std::string& id, int referenceTimeTicks = SDL_GetTicks());
		static void Unbind(const std::string& id);
		static void SetReferenceTime(const std::string& id, int referenceTimeTicks = SDL_GetTicks());
		static int GetElapsedMillis();
		static int GetElapsedMillis(const std::string& id);
		static int GetElapsedSeconds();
		static int GetElapsedSeconds(const std::string& id);
		static float GetDeltaTime();

		static float s_DeltaTime;
	
	private:
		static std::map<std::string, int> s_ReferenceTimes;
	};
}