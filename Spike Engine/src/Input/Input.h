#pragma once

#include "SDL.h"
#include "Math/Vector2.h"

namespace Spike
{
	class Input
	{
	public:
		Input() = delete;
		~Input();

		static void Init();
		static void Update();

		//mouse
		static bool s_CurrentButtonState[5];
		static bool s_OldButtonState[5];
		static int s_WheelDelta;
		static bool s_MouseMotion;
		static Vector2 GetMousePosition();
		static void SetMousePosition(SDL_Window* win, Vector2& pos);
		static Vector2 GetGlobalMousePosition();
		static void SetMouseGlobalPosition(Vector2& pos);
		static bool GetMouseButtonDown(int i);
		static bool GetMouseButton(int i);
		static bool GetMouseButtonUp(int i);
		static int GetMouseWheel();
		static bool GetMouseMotion();
		//keyboard
		static const Uint8* s_CurrentKeyState;
		static Uint8* s_OldKeyState;
		static int s_Length;
		static bool GetKeyDown(int i);
		static bool GetKey(int i);
		static bool GetKeyUp(int i);
	};
}