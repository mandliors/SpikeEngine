#include "Time.h"

namespace Spike {

	int Time::s_ReferenceTimeTicks = 0;

	void Time::SetReferenceTime(int ticks)
	{
		s_ReferenceTimeTicks = ticks;
	}
	int Time::GetElapsedMillis()
	{
		return SDL_GetTicks() - s_ReferenceTimeTicks;
	}
	int Time::GetElapsedSeconds()
	{
		return (SDL_GetTicks() - s_ReferenceTimeTicks) / 1000;
	}
	int Time::GetElapsedMillisSinceInit()
	{
		return SDL_GetTicks();
	}
	int Time::GetElapsedSecondsSinceInit()
	{
		return SDL_GetTicks() / 1000;
	}
	float Time::GetDeltaTime()
	{
		return s_DeltaTime;
	}

	float Time::s_DeltaTime = 0;
}