#include "Time.h"

namespace Spike {

	std::map<std::string, int> Time::s_ReferenceTimes = {};

	void Time::Bind(const std::string& id, int referenceTimeTicks)
	{
		s_ReferenceTimes.insert_or_assign(id, referenceTimeTicks);
	}
	void Time::Unbind(const std::string& id)
	{
		s_ReferenceTimes.erase(id);
	}
	void Time::SetReferenceTime(const std::string& id, int referenceTimeTicks)
	{
		s_ReferenceTimes.find(id)->second = referenceTimeTicks;
	}
	int Time::GetElapsedMillis()
	{
		return SDL_GetTicks();
	}
	int Time::GetElapsedMillis(const std::string& id)
	{
		return SDL_GetTicks() - s_ReferenceTimes.find(id)->second;
	}
	int Time::GetElapsedSeconds()
	{
		return SDL_GetTicks() / 1000;
	}
	int Time::GetElapsedSeconds(const std::string& id)
	{
		return (SDL_GetTicks() - s_ReferenceTimes.find(id)->second) / 1000;
	}
	float Time::GetDeltaTime()
	{
		return s_DeltaTime;
	}

	float Time::s_DeltaTime = 0;
}