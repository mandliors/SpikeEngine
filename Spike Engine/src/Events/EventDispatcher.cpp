#include "EventDispatcher.h"

namespace Spike {

	EventDispatcher::EventDispatcher(int eventType, void(*func)(SDL_Event& event))
	{
		m_EventType = eventType;
		m_Function = func;
	}
	EventDispatcher::EventDispatcher(void(*func)(SDL_Event& event))
	{
		m_EventType = -1;
		m_Function = func;
	}
	int EventDispatcher::GetEventType()
	{
		return m_EventType;
	}
	void EventDispatcher::Dispatch(SDL_Event& event)
	{
		m_Function(event);
	}
}