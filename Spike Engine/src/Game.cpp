#include "Game/Game.h"
#include "Core/SpikeEngine.h"

using namespace Spike;

Scene* mainScene;
Camera2D* mainCamera;
int speed = 600;

b2Body* body;
b2Body* body2;
b2Body* body3;
b2Body* body4;

void Game::Start()
{
	Application::EnableConsole();
	Application::SetMaxFPS(120);
	
	auto [scene, cam] = Application::CreateSceneAndCamera();
	mainScene = scene;
	mainCamera = cam;

	body = mainScene->CreateStaticBody(Vector2(610, 600), Vector2(600, 40));
	body2 = mainScene->CreateDynamicBody(Vector2(600, 300), Vector2(50, 50));
	body3 = mainScene->CreateDynamicBody(Vector2(580, 230), Vector2(50, 50));
	body4 = mainScene->CreateDynamicBody(Vector2(620, 140), Vector2(50, 50));
}

void Game::Update(float dt)
{
	Application::Clear(0, 0, 0, 0);

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



	Renderer2D::FillRotatedRect(body->GetPosition().x * Physics::PPM - 300.0f, body->GetPosition().y  * Physics::PPM - 20.0f, 600, 40, Math::ToDegrees(body->GetAngle()), Color::Green());
	Renderer2D::FillRotatedRect(body2->GetPosition().x * Physics::PPM - 25.0f, body2->GetPosition().y * Physics::PPM - 25.0f, 50, 50, Math::ToDegrees(body2->GetAngle()), Color::Red());
	Renderer2D::FillRotatedRect(body3->GetPosition().x * Physics::PPM - 25.0f, body3->GetPosition().y * Physics::PPM - 25.0f, 50, 50, Math::ToDegrees(body3->GetAngle()), Color::Yellow());
	Renderer2D::FillRotatedRect(body4->GetPosition().x * Physics::PPM - 25.0f, body4->GetPosition().y * Physics::PPM - 25.0f, 50, 50, Math::ToDegrees(body4->GetAngle()), Color::Magenta());
}

void Game::Exit()
{
	
}
