#include "EventManager.h"
#include "UI/SpikeUI/SpikeUI.h"

namespace Spike {

	bool EventManager::s_ImGuiInitialized = false;
	std::vector<EventDispatcher*> EventManager::s_EventDispatchers = std::vector<EventDispatcher*>();
	unsigned int EventManager::s_FPS = 0;

	void EventManager::Init() { }
	EventManager::~EventManager()
	{
		for (auto eventDispatcher : s_EventDispatchers)
			delete eventDispatcher;
		s_EventDispatchers.clear();
	}

	bool EventManager::HandleEvents()
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			for (auto eventDispatcher : s_EventDispatchers)
			{
				if (eventDispatcher->GetEventType() == event.type)
					eventDispatcher->Dispatch(event);
				else if (eventDispatcher->GetEventType() == -1)
					eventDispatcher->Dispatch(event);
			}
			switch (event.type)
			{
			case SDL_QUIT:
				return false;
			case SDL_KEYDOWN:
				Input::s_CurrentKeyState = SDL_GetKeyboardState(NULL);
				break;
			case SDL_KEYUP:
				Input::s_CurrentKeyState = SDL_GetKeyboardState(NULL);
				break;
			case SDL_MOUSEBUTTONDOWN:
				Input::s_CurrentButtonState[event.button.button - 1] = true;
				break;
			case SDL_MOUSEBUTTONUP:
				Input::s_CurrentButtonState[event.button.button - 1] = false;
				break;
			case SDL_MOUSEWHEEL:
				Input::s_WheelDelta = event.wheel.y;
				break;
			case SDL_MOUSEMOTION:
				if (event.motion.xrel != 0 || event.motion.yrel != 0)
					Input::s_MouseMotion = true;
				break;
			case SDL_WINDOWEVENT:
				if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
					SpikeUI::Recalculate();
				break;
			}
			if (s_ImGuiInitialized)
				UpdateImGui(&event);
		}
		return true;
	}
	void EventManager::SetFPS(unsigned int fps)
	{
		s_FPS = fps;
	}
	void EventManager::AddEventDispatcher(int eventType, void(*func)(SDL_Event& event))
	{
		EventDispatcher* eventDispatcher = new EventDispatcher(eventType, func);
		s_EventDispatchers.push_back(eventDispatcher);
	}
	void EventManager::AddEventDispatcher(void(*func)(SDL_Event& event))
	{
		EventDispatcher* eventDispatcher = new EventDispatcher(func);
		s_EventDispatchers.push_back(eventDispatcher);
	}
	void EventManager::UpdateImGui(SDL_Event* ev)
	{
		ImGui_ImplSDL2_ProcessEvent(ev);
		ImGuiIO& imGuiIO = ImGui::GetIO();
		imGuiIO.KeyMap[ImGuiKey_Tab] = ImGuiKey_Tab;
		imGuiIO.KeyMap[ImGuiKey_LeftArrow] = ImGuiKey_LeftArrow;
		imGuiIO.KeyMap[ImGuiKey_RightArrow] = ImGuiKey_RightArrow;
		imGuiIO.KeyMap[ImGuiKey_UpArrow] = ImGuiKey_UpArrow;
		imGuiIO.KeyMap[ImGuiKey_DownArrow] = ImGuiKey_DownArrow;
		imGuiIO.KeyMap[ImGuiKey_Home] = ImGuiKey_Home;
		imGuiIO.KeyMap[ImGuiKey_End] = ImGuiKey_End;
		imGuiIO.KeyMap[ImGuiKey_Delete] = ImGuiKey_Delete;
		imGuiIO.KeyMap[ImGuiKey_Backspace] = ImGuiKey_Backspace;
		imGuiIO.KeyMap[ImGuiKey_Enter] = ImGuiKey_Enter;
		imGuiIO.KeyMap[ImGuiKey_Escape] = ImGuiKey_Escape;
		imGuiIO.KeyMap[ImGuiKey_A] = ImGuiKey_A;
		imGuiIO.KeyMap[ImGuiKey_C] = ImGuiKey_C;
		imGuiIO.KeyMap[ImGuiKey_V] = ImGuiKey_V;
		imGuiIO.KeyMap[ImGuiKey_X] = ImGuiKey_X;
		imGuiIO.KeyMap[ImGuiKey_Y] = ImGuiKey_Y;
		imGuiIO.KeyMap[ImGuiKey_Z] = ImGuiKey_Z;
		//--------------------------------------
		imGuiIO.KeysDown[ImGuiKey_Tab] = Input::GetKey(SDL_SCANCODE_TAB);
		imGuiIO.KeysDown[ImGuiKey_LeftArrow] = Input::GetKey(SDL_SCANCODE_LEFT);
		imGuiIO.KeysDown[ImGuiKey_RightArrow] = Input::GetKey(SDL_SCANCODE_RIGHT);
		imGuiIO.KeysDown[ImGuiKey_UpArrow] = Input::GetKey(SDL_SCANCODE_UP);
		imGuiIO.KeysDown[ImGuiKey_DownArrow] = Input::GetKey(SDL_SCANCODE_DOWN);
		imGuiIO.KeysDown[ImGuiKey_Home] = Input::GetKey(SDL_SCANCODE_HOME);
		imGuiIO.KeysDown[ImGuiKey_End] = Input::GetKey(SDL_SCANCODE_END);
		imGuiIO.KeysDown[ImGuiKey_Delete] = Input::GetKey(SDL_SCANCODE_DELETE);
		imGuiIO.KeysDown[ImGuiKey_Backspace] = Input::GetKey(SDL_SCANCODE_BACKSPACE);
		imGuiIO.KeysDown[ImGuiKey_Enter] = Input::GetKey(SDL_SCANCODE_RETURN);
		imGuiIO.KeysDown[ImGuiKey_Escape] = Input::GetKey(SDL_SCANCODE_ESCAPE);
		imGuiIO.KeysDown[ImGuiKey_A] = Input::GetKey(SDL_SCANCODE_A);
		imGuiIO.KeysDown[ImGuiKey_C] = Input::GetKey(SDL_SCANCODE_C);
		imGuiIO.KeysDown[ImGuiKey_V] = Input::GetKey(SDL_SCANCODE_V);
		imGuiIO.KeysDown[ImGuiKey_X] = Input::GetKey(SDL_SCANCODE_X);
		imGuiIO.KeysDown[ImGuiKey_Y] = Input::GetKey(SDL_SCANCODE_Y);
		imGuiIO.KeysDown[ImGuiKey_Z] = Input::GetKey(SDL_SCANCODE_Z);

		int mouseX, mouseY;
		int wheel = Input::GetMouseWheel();
		const int buttons = SDL_GetMouseState(&mouseX, &mouseY);
		imGuiIO.DeltaTime = 1.0f / s_FPS;
		imGuiIO.MousePos = ImVec2(static_cast<float>(mouseX), static_cast<float>(mouseY));
		imGuiIO.MouseDown[0] = buttons & SDL_BUTTON(SDL_BUTTON_LEFT);
		imGuiIO.MouseDown[1] = buttons & SDL_BUTTON(SDL_BUTTON_RIGHT);
		imGuiIO.MouseWheel = static_cast<float>(wheel) / 2;
	}
}