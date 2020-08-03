#pragma once

#include "SDL.h"
#include "Input/Input.h"
#include "EventDispatcher.h"
#include "ImGui/imgui_impl_sdl.h"
#include <vector>

namespace Spike
{
	class EventManager
	{
	public:
		EventManager() = delete;
		~EventManager();

		static void Init();
		static bool HandleEvents();
		static void SetFPS(unsigned int fps);
		static void AddEventDispatcher(int eventType, void(*func)(SDL_Event& event));
		static void AddEventDispatcher(void(*func)(SDL_Event& event));
		
		static bool s_ImGuiInitialized;
	private:
		static void UpdateImGui(SDL_Event* ev);
		static std::vector<EventDispatcher*> s_EventDispatchers;
		static unsigned int s_FPS;
	};
}