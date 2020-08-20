#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "Core.h"
#include "Events/EventManager.h"
#include "Input/Input.h"
#include "Rendering/Renderer2D.h"
#include "Time/Time.h"
#include "UI/SpikeUI/SpikeUI.h"
#include "ECS/Scene/Scene.h"
#include "ECS/Camera2D/Camera2D.h"
#include "ImGui/imgui.h"
#include "ImGui/imgui_sdl.h"
#include "ImGui/imgui_impl_sdl.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Debug/Debug.h"
#include <Windows.h>
#include <iostream>
#include <vector>
#include <string>
#include <tuple>

#undef main

namespace Spike
{
	class Application
	{
	public:
		Application() = delete;
		~Application();

		//base
		static bool Init(std::string title, int width, int height, Uint32 windowFlags = SDL_WINDOW_RESIZABLE, Uint32 rendererFlags = SDL_RENDERER_ACCELERATED);
		static bool IsRunning() { return s_Running; }
		static void Update();
		static void Render();
		static void Close();
		static void SetTitle(std::string title);
		//window
		static SDL_Window* GetWindow();
		static void InitImGui();
		static void EnableConsole();
		static void SetMaxFPS(int fps);
		static unsigned int GetMaxFPS();
		static float GetFPS();
		static Vector2 GetScreenSize(Uint8 idx);
		static Vector2 GetWindowSize();
		static void SetWindowSize(const Vector2& size);
		static Vector2 GetWindowPosition();
		static void SetWindowPosition(const Vector2& pos);
		static void SafeToggleFullscreen();
		static void SafeToggleFullscreen(bool value);
		static void ToggleFullscreen();
		static void ToggleFullscreen(bool value);
		static void ToggleWindowedFullscreen();
		static void ToggleWindowedFullscreen(bool value);
		static void Clear(int r, int g, int b, int a = 255);
		//scene
		static Scene* CreateScene();
		static void SetActiveScene(int index);
		static std::tuple<Scene*, Camera2D*> CreateSceneAndCamera();

	private:
		//init
		static SDL_Window* s_Window;
		static ImGuiIO* s_ImGuiIO;
		static bool s_Running;
		static bool s_ImGuiInitialized;
		//size
		static bool s_Fullscreen;
		static bool s_WindowedFullscreen;
		//fps
		static float s_Now;
		static float s_Last;
		static float s_FPS;
		static unsigned int s_StartTicks;
		static unsigned int s_MaxFPS;
		static unsigned int s_Frames;
		//scene
		static std::vector<Scene*> m_Scenes;
		static Scene* m_ActiveScene;
	};
}