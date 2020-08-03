#include "Scene.h"
#include "../Components.h"
#include "../Entity/Entity.h"

namespace Spike {

	Scene::~Scene()
	{
		/*auto sprites = m_Registry.view<SpriteRenderer>();
		for (auto sprite : sprites)
		{
			auto spriteRenderer = sprites.get<SpriteRenderer>(sprite);
			if (spriteRenderer.Texture)
				SDL_DestroyTexture(spriteRenderer.Texture);
		}*/

		for (Camera2D* cam : m_Cameras)
			delete cam;
		m_Cameras.clear();
	}
	void Scene::Init()
	{
		m_Registry = entt::registry();
	}
	void Scene::Update()
	{
		SPIKE_ASSERT(m_ActiveCamera, "Camera was NULL");

		//Physics update
		m_World.Step(m_TimeStep, 6, 2);

		//Rendering
		auto sprites = m_Registry.group<SpriteRenderer>(entt::get<Transform>);
		for (auto sprite : sprites)
		{
			auto [transform, spriteRenderer] = sprites.get<Transform, SpriteRenderer>(sprite);
			if (transform.Active)
			{
				if (spriteRenderer.Path.empty())
					Renderer2D::FillRotatedRect(transform.Position.X - m_ActiveCamera->GetPosition().X, transform.Position.Y - m_ActiveCamera->GetPosition().Y, transform.Size.X * m_ActiveCamera->GetScale(), transform.Size.Y * m_ActiveCamera->GetScale(), transform.Rotation - m_ActiveCamera->GetRotation(), spriteRenderer.RenderColor);
				else
				{
					SDL_Surface* temp = IMG_Load(spriteRenderer.Path.c_str());
					SDL_Texture* texture = SDL_CreateTextureFromSurface(Renderer2D::GetRenderer(), temp);
					Renderer2D::RenderRotatedTexture(texture, transform.Position - m_ActiveCamera->GetPosition(), transform.Size * m_ActiveCamera->GetScale(), transform.Rotation - m_ActiveCamera->GetRotation(), spriteRenderer.RenderColor);
					SDL_DestroyTexture(texture);
					SDL_FreeSurface(temp);
				}
			}
		}
		auto texts = m_Registry.group<TextRenderer>(entt::get<Transform>);
		for (auto text : texts)
		{
			auto [transform, textRenderer] = texts.get<Transform, TextRenderer>(text);
			if (transform.Active)
			{
				if (!textRenderer.Text.empty())
					Renderer2D::RenderRotatedText(textRenderer.Text, transform.Position.X, transform.Position.Y, transform.Rotation - m_ActiveCamera->GetRotation(), textRenderer.RenderColor);
			}
		}
	}

	b2Body* Scene::CreateStaticBody(const Vector2& position, const Vector2& size)
	{
		b2BodyDef bodyDef;
		bodyDef.position.Set(position.X / Physics::PPM, position.Y / Physics::PPM);
		b2Body* body = m_World.CreateBody(&bodyDef);
		b2PolygonShape shape;
		shape.SetAsBox(size.X / Physics::PPM / 2, size.Y / Physics::PPM / 2);
		body->CreateFixture(&shape, 0.0f);
		body->GetFixtureList()->SetSensor(true);
		return body;
	}

	b2Body* Scene::CreateDynamicBody(const Vector2& position, const Vector2& size)
	{
		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;
		bodyDef.position.Set(position.X / Physics::PPM, position.Y / Physics::PPM);
		b2Body* body = m_World.CreateBody(&bodyDef);
		b2PolygonShape shape;
		shape.SetAsBox(size.X / Physics::PPM / 2, size.Y / Physics::PPM / 2);
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &shape;
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 0.3f;
		body->CreateFixture(&fixtureDef);
		body->GetFixtureList()->SetSensor(true);
		return body;
	}

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
	Entity Scene::CreateEntity(const std::string& name)
	{
		Entity entity = Entity(m_Registry.create(), this);
		entity.AddComponent<Transform>();
		auto& tag = entity.AddComponent<Tag>();
		tag.Name = name.empty() ? "Unnamed" : name;
		return entity;
	}

	void Scene::SetTimeStep(float ts)
	{
		m_TimeStep = ts;
	}
}
