#include "Application.h"

namespace Spike {

	SDL_Window* Application::s_Window = nullptr;
	ImGuiIO* Application::s_ImGuiIO = nullptr;
	float Application::s_Now = 0;
	float Application::s_Last = 0;
	float Application::s_FPS = 0;
	unsigned int Application::s_StartTicks = 0;
	unsigned int Application::s_MaxFPS = 10000;
	unsigned int Application::s_Frames = 0;
	bool Application::s_ImGuiInitialized = false;
	bool Application::s_Running = true;
	bool Application::s_Fullscreen = false;
	bool Application::s_WindowedFullscreen = false;
	std::vector<Scene*> Application::m_Scenes = std::vector<Scene*>();
	Scene* Application::m_ActiveScene = nullptr;

	Application::~Application()
	{
		for (Scene* scene : m_Scenes)
			delete scene;
		m_Scenes.clear();
	}
	bool Application::Init(std::string title, int width, int height, Uint32 windowFlags, Uint32 rendererFlags)
	{
		bool success = true;
		HWND console = GetConsoleWindow();
		ShowWindow(console, SW_HIDE);
		if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
		{
			s_Window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, windowFlags);
			if (!Renderer2D::Init(s_Window, -1, rendererFlags))
				success = false;

			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) & imgFlags))
				success = false;

			EventManager::Init();
			EventManager::SetFPS(s_MaxFPS);
			Input::Init();
			SpikeUI::Init();

			s_StartTicks = SDL_GetTicks();
			s_Running = true;
		}
		else
			success = false;
		return success;
	}
	void Application::Update()
	{
		//FPS
		s_Now = SDL_GetTicks();
		Time::s_DeltaTime = (s_Now - s_Last) / 1000.0f;
		s_Last = s_Now;
		
		//Events, input
		Input::Update();
		if (!EventManager::HandleEvents())
			s_Running = false;
		
		//FPS
		s_FPS = s_Frames / ((SDL_GetTicks() - s_StartTicks) / 1000.0f);
		if (s_FPS > 2000000) s_FPS = 0;
		//s_FPS = 1.0f / Time::s_DeltaTime;

		//SpikeGUI
		SpikeUI::Update();

		if (s_ImGuiInitialized)
			ImGui::NewFrame();
	}
	void Application::Render()
	{
		//ImGui
		if (s_ImGuiInitialized)
		{
			ImGui::Render();
			ImGuiSDL::Render(ImGui::GetDrawData());
		}

		//Scene
		if (m_ActiveScene)
			m_ActiveScene->Update();

		//SpikeGUI
		SpikeUI::Render();

		SDL_RenderPresent(Renderer2D::GetRenderer());

		//FPS
		int frameTicks = SDL_GetTicks() - s_Last;
		if (frameTicks < 1000 / s_MaxFPS)
			SDL_Delay(1000 / s_MaxFPS - frameTicks);
		s_Frames++;
	}
	SDL_Window* Application::GetWindow()
	{
		return s_Window;
	}
	void Application::EnableConsole()
	{
		ShowWindow(GetConsoleWindow(), SW_SHOWNOACTIVATE);
	}
	void Application::SetMaxFPS(int fps)
	{
		s_MaxFPS = fps;
		EventManager::SetFPS(fps);
		for (Scene* scene : m_Scenes)
			scene->SetTimeStep(1.0f / (float)fps);
	}

	unsigned int Application::GetMaxFPS()
	{
		return s_MaxFPS;
	}

	float Application::GetFPS()
	{
		return s_FPS;
	}
	void Application::InitImGui()
	{
		if (!s_ImGuiInitialized)
		{
			ImGui::CreateContext();
			ImGuiSDL::Initialize(Renderer2D::GetRenderer(), GetWindowSize().X, GetWindowSize().Y);
			EventManager::s_ImGuiInitialized = true;
			s_ImGuiInitialized = true;
		}
	}
	void Application::Close()
	{
		Input::Close();
		SpikeUI::Close();
		Renderer2D::Close();
		if (s_ImGuiInitialized)
		{
			ImGuiSDL::Deinitialize();
			ImGui::DestroyContext();
		}
		SDL_DestroyWindow(s_Window);
		SDL_DestroyRenderer(Renderer2D::GetRenderer());
		IMG_Quit();
		TTF_Quit();
		SDL_Quit();
	}
	void Application::SetTitle(std::string title)
	{
		SDL_SetWindowTitle(s_Window, title.c_str());
	}
	Vector2 Application::GetScreenSize(Uint8 idx)
	{
		SDL_DisplayMode dm;
		SDL_GetCurrentDisplayMode(idx, &dm);
		return Vector2(dm.w, dm.h);
	}
	Vector2 Application::GetWindowSize()
	{
		int w, h;
		SDL_GetWindowSize(s_Window, &w, &h);
		return Vector2(w, h);
	}
	void Application::SetWindowSize(const Vector2& size)
	{
		SDL_SetWindowSize(s_Window, size.X, size.Y);
	}
	Vector2 Application::GetWindowPosition()
	{
		int x, y;
		SDL_GetWindowPosition(s_Window, &x, &y);
		return Vector2(x, y);
	}
	void Application::SetWindowPosition(const Vector2& pos)
	{
		SDL_SetWindowPosition(s_Window, (int)pos.X, (int)pos.Y);
	}
	void Application::SafeToggleFullscreen()
	{
		if (s_Fullscreen)
		{
			SDL_SetWindowFullscreen(s_Window, 0);
			SDL_RestoreWindow(s_Window);
		}
		else
		{
			Vector2 temp = GetScreenSize(0);
			SetWindowSize(Vector2(temp.X, temp.Y));
			SDL_SetWindowFullscreen(s_Window, SDL_WINDOW_FULLSCREEN);
		}
		s_Fullscreen = !s_Fullscreen;
		s_WindowedFullscreen = false;
	}
	void Application::SafeToggleFullscreen(bool value)
	{
		if (value)
		{
			Vector2 temp = GetScreenSize(0);
			SetWindowSize(Vector2(temp.X, temp.Y));
			SDL_SetWindowFullscreen(s_Window, SDL_WINDOW_FULLSCREEN);
			s_Fullscreen = true;
		}
		else
		{
			SDL_SetWindowFullscreen(s_Window, 0);
			SDL_RestoreWindow(s_Window);
			s_Fullscreen = false;
		}
		s_WindowedFullscreen = false;
	}
	void Application::ToggleFullscreen()
	{
		if (s_Fullscreen)
		{
			SDL_SetWindowFullscreen(s_Window, 0);
			SDL_RestoreWindow(s_Window);
		}
		else
			SDL_SetWindowFullscreen(s_Window, SDL_WINDOW_FULLSCREEN);
		s_Fullscreen = !s_Fullscreen;
		s_WindowedFullscreen = false;
	}
	void Application::ToggleFullscreen(bool value)
	{
		if (value)
		{
			SDL_SetWindowFullscreen(s_Window, SDL_WINDOW_FULLSCREEN);
			s_Fullscreen = true;
		}
		else
		{
			SDL_SetWindowFullscreen(s_Window, 0);
			SDL_RestoreWindow(s_Window);
			s_Fullscreen = false;
		}
		s_WindowedFullscreen = false;
	}
	void Application::ToggleWindowedFullscreen()
	{
		if (s_WindowedFullscreen)
			SDL_SetWindowFullscreen(s_Window, 0);
		else
		{
			ToggleFullscreen(false);
			SDL_RestoreWindow(s_Window);
			SDL_SetWindowFullscreen(s_Window, SDL_WINDOW_FULLSCREEN_DESKTOP);
		}
		s_WindowedFullscreen = !s_WindowedFullscreen;
		s_Fullscreen = false;
	}
	void Application::ToggleWindowedFullscreen(bool value)
	{
		if (value)
		{
			ToggleFullscreen(false);
			SDL_SetWindowFullscreen(s_Window, SDL_WINDOW_FULLSCREEN_DESKTOP);
			s_WindowedFullscreen = true;
		}
		else
		{
			SDL_SetWindowFullscreen(s_Window, 0);
			s_WindowedFullscreen = false;
		}
		s_Fullscreen = false;
	}
	void Application::Clear(int r, int g, int b, int a)
	{
		Renderer2D::Clear(r, g, b, a);
	}
	Scene* Application::CreateScene()
	{
		Scene* newScene = new Scene();
		newScene->Init();
		newScene->SetTimeStep(1.0f / (float)s_MaxFPS);
		m_Scenes.push_back(newScene);
		m_ActiveScene = newScene;
		return newScene;
	}
	void Application::SetActiveScene(int index)
	{
		m_ActiveScene = m_Scenes[index];
	}
	std::tuple<Scene*, Camera2D*> Application::CreateSceneAndCamera()
	{
		Scene* scene = new Scene();
		scene->Init();
		scene->SetTimeStep(1.0f / (float)s_MaxFPS);
		m_Scenes.push_back(scene);
		m_ActiveScene = scene;
		Camera2D* cam = scene->CreateCamera();
		return std::make_tuple(scene, cam);
	}
}