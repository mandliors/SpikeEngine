#pragma once

#include "SDL.h"

namespace Spike {
	
	class EventDispatcher
	{
	public:
		EventDispatcher(int eventType, void(*func)(SDL_Event& event));
		EventDispatcher(void(*func)(SDL_Event& event));
		~EventDispatcher() = default;

		int GetEventType();
		void Dispatch(SDL_Event& event);
	private:
		int m_EventType;
		void (*m_Function)(SDL_Event& event);
	};

}

