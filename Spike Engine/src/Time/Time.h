#pragma once

#include "SDL.h"

namespace Spike {

	struct Time
	{
		Time() = delete;
		~Time() = default;

		static void SetReferenceTime(int ticks = SDL_GetTicks());
		static int GetElapsedMillis();
		static int GetElapsedSeconds();
		static int GetElapsedMillisSinceInit();
		static float GetDeltaTime();
		static int GetElapsedSecondsSinceInit();

		static float s_DeltaTime;
	
	private:
		static int s_ReferenceTimeTicks;
	};
}