#include "Input.h"

namespace Spike {

	bool Input::s_CurrentButtonState[5];
	bool Input::s_OldButtonState[5];
	int Input::s_WheelDelta = 0;
	bool Input::s_MouseMotion = false;
	const Uint8* Input::s_CurrentKeyState = nullptr;
	Uint8* Input::s_OldKeyState = nullptr;
	int Input::s_Length = 1;
	//Vector2 Input::s_PreviousMousePosition = Vector2::Empty();        *NOT WORKING*
	//Vector2 Input::s_PreviousGlobalMousePosition = Vector2::Empty();  *NOT WORKING*

	void Input::Init()
	{
		for (size_t i = 0; i < 5; i++)
		{
			s_CurrentButtonState[i] = false;
			s_OldButtonState[i] = false;
		}
		s_CurrentKeyState = SDL_GetKeyboardState(&s_Length);
		s_OldKeyState = new Uint8[s_Length];

	}
	void Input::Update()
	{
		//s_PreviousMousePosition = GetMousePosition();                 *NOT WORKING*
		//s_PreviousGlobalMousePosition = GetGlobalMousePosition();     *NOT WORKING*
		memcpy(s_OldButtonState, s_CurrentButtonState, 5);
		s_WheelDelta = 0;
		s_MouseMotion = false;
		memcpy(s_OldKeyState, s_CurrentKeyState, s_Length);
		SDL_PumpEvents();
	}

	void Input::Close()
	{

	}

	//mouse
	Vector2 Input::GetMousePosition()
	{
		int x, y;
		SDL_GetMouseState(&x, &y);
		return Vector2(x, y);
	}
	void Input::SetMousePosition(SDL_Window* win, Vector2& pos)
	{
		SDL_WarpMouseInWindow(win, pos.X, pos.Y);
	}

	//Vector2 Input::GetPreviousMousePosition()            *NOT WORKING*
	//{													   *NOT WORKING*
	//	return s_PreviousMousePosition;					   *NOT WORKING*
	//}													   *NOT WORKING*
	//													   *NOT WORKING*
	//Vector2 Input::GetPreviousGlobalMousePosition()	   *NOT WORKING*
	//{													   *NOT WORKING*
	//	return s_PreviousGlobalMousePosition;			   *NOT WORKING*
	//}*/												   *NOT WORKING*

	Vector2 Input::GetGlobalMousePosition()
	{
		int x, y;
		SDL_GetGlobalMouseState(&x, &y);
		return Vector2(x, y);;
	}
	void Input::SetMouseGlobalPosition(Vector2& pos)
	{
		SDL_WarpMouseGlobal(pos.X, pos.Y);
	}
	bool Input::GetMouseButtonDown(int i)
	{
		return s_CurrentButtonState[i] && !s_OldButtonState[i];
	}
	bool Input::GetMouseButton(int i)
	{
		return s_CurrentButtonState[i];
	}
	bool Input::GetMouseButtonUp(int i)
	{
		return s_OldButtonState[i] && !s_CurrentButtonState[i];
	}
	int Input::GetMouseWheel()
	{
		return s_WheelDelta;
	}
	bool Input::GetMouseMotion()
	{
		return s_MouseMotion;
	}

	//keyboard
	bool Input::GetKeyDown(int i)
	{
		return (s_CurrentKeyState[i] && !s_OldKeyState[i]);
	}
	bool Input::GetKey(int i)
	{
		return s_CurrentKeyState[i];
	}
	bool Input::GetKeyUp(int i)
	{
		return (s_OldKeyState[i] && !s_CurrentKeyState[i]);
	}

	std::vector<int> Input::GetKeysDown()
	{
		std::vector<int> keysDown;
		for (int i = 0; i < s_Length; i++)
			if (s_CurrentKeyState[i] && !s_OldKeyState[i]) keysDown.push_back(i);
		return keysDown;
	}

	std::vector<int> Input::GetMouseButtonsDown()
	{
		std::vector<int> buttonsDown;
		for (int i = 0; i < 5; i++)
			if (s_CurrentButtonState[i] && !s_OldButtonState[i]) buttonsDown.push_back(i);
		return buttonsDown;
	}
}