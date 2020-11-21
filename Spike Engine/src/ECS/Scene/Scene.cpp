#include "Scene.h"
#include "ECS/Components.h"
#include "ECS/Entity/Entity.h"
#include <thread>

namespace Spike {

	/*void UpdateThreadWrapper(Scene* scene)
	{
		scene->Update();
	}
	void RenderThreadWrapper(Scene* scene)
	{
		scene->Render();
	}*/
	
	Scene::~Scene()
	{
		/*auto sprites = m_Registry.view<SpriteRenderer>();
		for (auto sprite : sprites)
		{
			auto spriteRenderer = sprites.get<SpriteRenderer>(sprite);
			if (spriteRenderer.Texture)
				SDL_DestroyTexture(spriteRenderer.Texture);
		}*/

		//delete entities
		for (Entity* entity : m_Entities)
			delete entity;
		m_Entities.clear();

		//delete cameras
		for (Camera2D* cam : m_Cameras)
			delete cam;
		m_Cameras.clear();

		delete m_World;
	}
	void Scene::Init()
	{
		m_Registry = entt::registry();

		/*std::thread updateThread(UpdateThreadWrapper, this);
		std::thread renderThread(RenderThreadWrapper, this);
		
		m_UpdateThreadRunning = true;
		m_RenderThreadRunning = true;*/
	}
	void Scene::Update()
	{
		/*while (m_UpdateThreadRunning)
		{*/
		#pragma region Scripting
		m_Registry.view<NativeScript>().each([=](auto entity, auto& ns)
			{
				if (ns.Instance == nullptr)
				{
					ns.Instance = ns.InstantiateScript();
					ns.Instance->m_Entity = Entity(entity, this);
					ns.Instance->Setup();
				}

				ns.Instance->Update();
			});
		#pragma endregion

		#pragma region Physics
		m_World->Step(m_TimeStep, 6, 2);

		auto bodies = m_Registry.group<Rigidbody2D>(entt::get<Transform>);
		for (auto body : bodies)
		{
			auto [transform, rigidbody2D] = bodies.get<Transform, Rigidbody2D>(body);
			transform.Position = Vector2(rigidbody2D.Body->GetPosition().x * Physics::PPM - transform.Size.X / 2,
				rigidbody2D.Body->GetPosition().y * Physics::PPM - transform.Size.Y / 2);
			transform.Rotation = Math::ToDegrees(rigidbody2D.Body->GetAngle());
		}
		#pragma endregion
		//}
	}
	void Scene::Render()
	{
		/*while (m_RenderThreadRunning)
		{*/
		SPIKE_ASSERT(m_ActiveCamera, "Camera was NULL");

		auto sprites = m_Registry.group<SpriteRenderer>(entt::get<Transform>);

		for (auto sprite : sprites)
		{
			auto [transform, spriteRenderer] = sprites.get<Transform, SpriteRenderer>(sprite);
			if (transform.Active)
			{
				//TODO: No hard code
				//TODO: Fix camera (scale, rotation)
				if (transform.Position.X + transform.Size.X >= 0 && transform.Position.X <= 1280 &&
					transform.Position.Y + transform.Size.Y >= 0 && transform.Position.Y <= 720)
				{
					SDL_Point point = { 640, 360 };
					if (spriteRenderer.Path.empty())
						Renderer2D::FillRotatedRect(transform.Position.X - m_ActiveCamera->GetPosition().X,
							transform.Position.Y - m_ActiveCamera->GetPosition().Y,
							transform.Size.X * m_ActiveCamera->GetScale(),
							transform.Size.Y * m_ActiveCamera->GetScale(),
							transform.Rotation - m_ActiveCamera->GetRotation(), spriteRenderer.RenderColor);
					else
					{
						// TODO: Don't always load and create textures (big performance issue)
						SDL_Surface* temp = IMG_Load(spriteRenderer.Path.c_str());
						SDL_Texture* texture = SDL_CreateTextureFromSurface(Renderer2D::GetRenderer(), temp);
						Renderer2D::RenderRotatedTexture(texture, transform.Position - m_ActiveCamera->GetPosition(),
							transform.Size * m_ActiveCamera->GetScale(),
							transform.Rotation - m_ActiveCamera->GetRotation(), spriteRenderer.RenderColor);
						SDL_DestroyTexture(texture);
						SDL_FreeSurface(temp);
					}
				}
			}
		}
		auto texts = m_Registry.group<TextRenderer>(entt::get<Transform>);
		for (auto text : texts)
		{
			auto [transform, textRenderer] = texts.get<Transform, TextRenderer>(text);
			if (transform.Active)
			{
				if (transform.Position.X + transform.Size.X >= 0 && transform.Position.X <= 1280 &&
					transform.Position.Y + transform.Size.Y >= 0 && transform.Position.Y <= 720)
				{
					if (!textRenderer.Text.empty())
						Renderer2D::RenderRotatedText(textRenderer.Text, transform.Position.X, transform.Position.Y, transform.Rotation - m_ActiveCamera->GetRotation(), textRenderer.RenderColor);
				}
			}
		}
		//}
	}
	/*void Scene::StopThreads()
	{
		m_UpdateThreadRunning = false;
		m_RenderThreadRunning = false;
	}*/

	Camera2D* Scene::CreateCamera(const Vector2& position, float rotation, float scale)
	{
		Camera2D* cam = new Camera2D(position, rotation, scale);
		m_Cameras.push_back(cam);
		m_ActiveCamera = cam;
		return cam;
	}
	void Scene::SetActiveCamera(int index)
	{
		m_ActiveCamera = m_Cameras[index];
	}
	Entity& Scene::CreateEntity(const std::string& name)
	{
		Entity* entity = new Entity(m_Registry.create(), this);
		m_Entities.push_back(entity);
		entity->AddComponent<Transform>();
		auto& tag = entity->AddComponent<Tag>();
		tag.Name = name.empty() ? "Unnamed" : name;
		return *entity;
	}

	void Scene::DestroyEntity(Entity* entity)
	{
		for (size_t i = 0; i < m_Entities.size(); i++)
		{
			Entity* e = m_Entities[i];
			if (e->GetEntityID() == entity->GetEntityID())
			{
				m_Registry.destroy(e->GetEntityID());
				m_Entities.erase(m_Entities.begin() + i);
				delete e;
				break;
			}
		}
	}

	int Scene::GetEntityCount()
	{
		return m_Entities.size();
	}

	b2World* Scene::GetPhysicsWorld()
	{
		return m_World;
	}

	void Scene::SetGravity(const Vector2& gravity)
	{
		m_World->SetGravity(b2Vec2(gravity.X, gravity.Y));
	}

	Vector2 Scene::GetGravity()
	{
		b2Vec2 gravity = m_World->GetGravity();
		return Vector2(gravity.x, gravity.y);
	}

	void Scene::SetTimeStep(float ts)
	{
		m_TimeStep = ts;
	}
}
