#include "Game/Game.h"
#include "Core/SpikeEngine.h"

#ifdef PhysicsTest

using namespace Spike;

class CreationScript;

Scene* mainScene;
Camera2D* mainCamera;
int speed = 600;


void Game::Start()
{
	Application::EnableConsole();
	Application::SetMaxFPS(60);

	auto [scene, cam] = Application::CreateSceneAndCamera();
	mainScene = scene;
	mainCamera = cam;

	//ground
	auto& ground = mainScene->CreateEntity();
	auto& t = ground.GetComponent<Transform>();
	t.Position = Vector2(100, 660);
	t.Size = Vector2(1080, 40);
	ground.AddComponent<Rigidbody2D>(RIGIDBODY_TYPE::STATIC);
	ground.AddComponent<BoxCollider2D>();
	ground.AddComponent<SpriteRenderer>(Color(140, 110, 110, 255));
	//wall1
	auto& wall = mainScene->CreateEntity();
	auto& wt = wall.GetComponent<Transform>();
	wt.Position = Vector2(100, 40);
	wt.Size = Vector2(40, 660);
	wall.AddComponent<Rigidbody2D>(RIGIDBODY_TYPE::STATIC);
	wall.AddComponent<BoxCollider2D>();
	wall.AddComponent<SpriteRenderer>(Color(140, 110, 110, 255));
	//wall2
	auto& wall2 = mainScene->CreateEntity();
	auto& wt2 = wall2.GetComponent<Transform>();
	wt2.Position = Vector2(1140, 40);
	wt2.Size = Vector2(40, 660);
	wall2.AddComponent<Rigidbody2D>(RIGIDBODY_TYPE::STATIC);
	wall2.AddComponent<BoxCollider2D>();
	wall2.AddComponent<SpriteRenderer>(Color(140, 110, 110, 255));
}

int x = 10;

void Game::Update(float dt)
{
	Application::Clear(0, 0, 0, 0);
	Application::SetTitle("Spike Engine - FPS: " + std::to_string(Application::GetFPS()));

	if (Input::GetMouseButton(0))
	{
		auto e = mainScene->CreateEntity();
		auto& t = e.GetComponent<Transform>();
		t.Position = Input::GetMousePosition();
		t.Size = Vector2(20, 20);
		e.AddComponent<Rigidbody2D>(RIGIDBODY_TYPE::DYNAMIC);
		e.AddComponent<NativeScript>().Bind<CreationScript>();

		if (rand() % 2 == 0)
		{
			e.AddComponent<BoxCollider2D>();
			e.AddComponent<SpriteRenderer>(Color::Random(false));
		}
		else
		{
			e.AddComponent<BoxCollider2D>();
			e.AddComponent<SpriteRenderer>(Color::Random(false));
			/*e.AddComponent<CircleCollider2D>();
			e.AddComponent<SpriteRenderer>("assets/circle.png", Color::Random(true));*/
		}
	}

	if (Input::GetKey(SDL_SCANCODE_W))
		mainCamera->SetPosition(mainCamera->GetPosition() + Vector2::Up() * speed * dt);
	else if (Input::GetKey(SDL_SCANCODE_S))
		mainCamera->SetPosition(mainCamera->GetPosition() + Vector2::Down() * speed * dt);
	if (Input::GetKey(SDL_SCANCODE_A))
		mainCamera->SetPosition(mainCamera->GetPosition() + Vector2::Left() * speed * dt);
	else if (Input::GetKey(SDL_SCANCODE_D))
		mainCamera->SetPosition(mainCamera->GetPosition() + Vector2::Right() * speed * dt);
	if (Input::GetKey(SDL_SCANCODE_Q))
		mainCamera->SetRotation(mainCamera->GetRotation() - speed / 2 * dt);
	else if (Input::GetKey(SDL_SCANCODE_E))
		mainCamera->SetRotation(mainCamera->GetRotation() + speed / 2 * dt);
	mainCamera->SetScale(mainCamera->GetScale() * (1.0f + Input::GetMouseWheel() * 0.2f));

	Renderer2D::RenderText("Object count: " + std::to_string(mainScene->GetEntityCount()), x++ % 1080, 10, Color::White());
}

void Game::Exit()
{

}

class CreationScript : public ScriptableEntity
{
public:
	void Setup()
	{
		Debug::Log("New entity was created");
	}
};

#endif