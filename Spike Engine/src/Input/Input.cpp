#include "Input.h"

bool Spike::Input::s_CurrentButtonState[5];
bool Spike::Input::s_OldButtonState[5];
int Spike::Input::s_WheelDelta = 0;
bool Spike::Input::s_MouseMotion = false;
const Uint8* Spike::Input::s_CurrentKeyState = nullptr;
Uint8* Spike::Input::s_OldKeyState = nullptr;
int Spike::Input::s_Length = 1;

Spike::Input::~Input()
{
	delete[] s_CurrentButtonState, s_OldButtonState;
}
void Spike::Input::Init()
{
	for (size_t i = 0; i < 5; i++)
	{
		s_CurrentButtonState[i] = false;
		s_OldButtonState[i] = false;
	}
	s_CurrentKeyState = SDL_GetKeyboardState(&s_Length);
	s_OldKeyState = new Uint8[s_Length];

}
void Spike::Input::Update()
{
	memcpy(s_OldButtonState, s_CurrentButtonState, 5);
	s_WheelDelta = 0;
	s_MouseMotion = false;
	memcpy(s_OldKeyState, s_CurrentKeyState, s_Length);
	SDL_PumpEvents();
}
//mouse
Spike::Vector2 Spike::Input::GetMousePosition()
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	Vector2 vec = Vector2(x, y);
	return vec;
}
void Spike::Input::SetMousePosition(SDL_Window* win, Spike::Vector2& pos)
{
	SDL_WarpMouseInWindow(win, pos.X, pos.Y);
}
Spike::Vector2 Spike::Input::GetGlobalMousePosition()
{
	int x, y;
	SDL_GetGlobalMouseState(&x, &y);
	Vector2 vec = Vector2(x, y);
	return vec;
}
void Spike::Input::SetMouseGlobalPosition(Spike::Vector2& pos)
{
	SDL_WarpMouseGlobal(pos.X, pos.Y);
}
bool Spike::Input::GetMouseButtonDown(int i)
{
	return s_CurrentButtonState[i] && !s_OldButtonState[i];
}
bool Spike::Input::GetMouseButton(int i)
{
	return s_CurrentButtonState[i];
}
bool Spike::Input::GetMouseButtonUp(int i)
{
	return s_OldButtonState[i] && !s_CurrentButtonState[i];
}
int Spike::Input::GetMouseWheel()
{
	return s_WheelDelta;
}
bool Spike::Input::GetMouseMotion()
{
	return s_MouseMotion;
}

//keyboard
bool Spike::Input::GetKeyDown(int i)
{
	return (s_CurrentKeyState[i] && !s_OldKeyState[i]);
}
bool Spike::Input::GetKey(int i)
{
	return s_CurrentKeyState[i];
}
bool Spike::Input::GetKeyUp(int i)
{
	return (s_OldKeyState[i] && !s_CurrentKeyState[i]);
}