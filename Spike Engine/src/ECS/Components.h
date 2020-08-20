#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "Math/Vector2.h"
#include "Math/Math.h"
#include "Rendering/Renderer2D.h"
#include "Rendering/Color.h"
#include "Core/Core.h"
#include "ECS/EnTT/entt.hpp"
#include "ECS/Entity/Entity.h"

#include "Debug/Debug.h"

namespace Spike {

	//basic
	struct Tag
	{
		Tag() = default;
		Tag(const Tag&) = default;
		Tag(Entity* entity, std::string name = "Unnamed entity")
			: OwnerEntity(entity), Name(name) { }

		Entity* OwnerEntity;
		std::string Name;
	};
	struct Transform
	{
		Transform() = default;
		Transform(const Transform&) = default;
		Transform(Entity* entity, const Vector2& position = Vector2::Empty(), const Vector2& size = Vector2::Empty(), int rotation = 0.0f)
			: OwnerEntity(entity), Position(position), Size(size), Rotation(rotation) { }

		Vector2 Up()
		{
			Vector2 temp(1, tan(Rotation));
			return temp.Normalize();
		}
		void LookAt(const Vector2& point)
		{
			Vector2 direction = point - Position;
			float rotation = atan2(direction.Y, direction.X) + HALF_PI;
			if (OwnerEntity->GetBody() != nullptr)
				OwnerEntity->GetBody()->SetTransform(b2Vec2(OwnerEntity->GetComponent<Transform>().Position.X,
															OwnerEntity->GetComponent<Transform>().Position.Y), rotation);
			Rotation = Math::ToDegrees(rotation);
		}
		void Rotate(int rotation)
		{
			Rotation += rotation;
		}
		void Translate(const Vector2& position)
		{
			Position = position;
		}

		Entity* OwnerEntity;
		Vector2 Position;
		Vector2 Size;
		int Rotation = 0;
		bool Active = true;
	};

	//Rendering
	struct SpriteRenderer
	{
		SpriteRenderer() = default;
		SpriteRenderer(const SpriteRenderer&) = default;
		SpriteRenderer(Entity* entity, const Color& color = Color::White())
			: OwnerEntity(entity), RenderColor(color) { }
		SpriteRenderer(Entity* entity, const std::string& path, const Color& color = Color::White())
			: OwnerEntity(entity), Path(path), RenderColor(color) { }

		Entity* OwnerEntity;
		std::string Path;
		Color RenderColor;
	};
	struct TextRenderer
	{
		TextRenderer() = default;
		TextRenderer(const TextRenderer&) = default;
		TextRenderer(Entity* entity, const std::string& text, const Color& color = Color::White())
			: OwnerEntity(entity), Text(text), RenderColor(color) { }
		
		Entity* OwnerEntity;
		std::string Text;
		Color RenderColor = Color::White();
	};

	//Physics
	enum RIGIDBODY_TYPE
	{
		STATIC = 0, KINEMATIC, DYNAMIC
	};

	struct Rigidbody2D
	{
		Rigidbody2D() = delete;
		Rigidbody2D(const Rigidbody2D&) = default;
		Rigidbody2D(Entity* entity, RIGIDBODY_TYPE rbType = RIGIDBODY_TYPE::STATIC)
			: OwnerEntity(entity), RigidbodyType(rbType)
		{
			OwnerEntity = entity;
			Scene* scene = entity->GetScene();
			Transform& transform = entity->GetComponent<Transform>();
			b2BodyDef bodyDef;
			if (rbType == RIGIDBODY_TYPE::STATIC)
			{
				bodyDef.type = b2_staticBody;
				bodyDef.position.Set((transform.Position.X + transform.Size.X / 2) / Physics::PPM, (transform.Position.Y + transform.Size.Y / 2) / Physics::PPM);
				Body = scene->GetPhysicsWorld()->CreateBody(&bodyDef);
				b2PolygonShape shape;
				shape.SetAsBox(transform.Size.X / 2 / Physics::PPM, transform.Size.Y / 2 / Physics::PPM);
				b2Fixture* fixture = Body->CreateFixture(&shape, 0.0f);
				fixture->SetSensor(true);
			}
			else
			{
				bodyDef.type = (b2BodyType)rbType;
				bodyDef.position.Set((transform.Position.X + transform.Size.X / 2) / Physics::PPM, (transform.Position.Y + transform.Size.Y / 2) / Physics::PPM);
				Body = scene->GetPhysicsWorld()->CreateBody(&bodyDef);
				b2PolygonShape shape;
				shape.SetAsBox(transform.Size.X / 2 / Physics::PPM, transform.Size.Y / 2 / Physics::PPM);
				b2FixtureDef fixtureDef;
				fixtureDef.shape = &shape;
				fixtureDef.density = 1.0f;
				fixtureDef.friction = 0.3f;
				b2Fixture* fixture = Body->CreateFixture(&fixtureDef);
				fixture->SetSensor(true);
			}
		}

		float GetMass()
		{
			Body->GetMass();
		}
		void SetMass(float mass)
		{
			b2MassData massData;
			massData.mass = mass;
			Body->SetMassData(&massData);
		}
		void UseGravity(bool value)
		{
			Body->SetGravityScale(value ? 1.0f : 0.0f);
		}
		void SetGravityScale(float scale)
		{
			Body->SetGravityScale(scale);
		}
		float GetGravityScale()
		{
			return Body->GetGravityScale();
		}
		Vector2 GetVelocity()
		{
			return Vector2(Body->GetLinearVelocity().x, Body->GetLinearVelocity().y);
		}
		void SetVelocity(const Vector2& velocity)
		{
			Body->SetLinearVelocity(b2Vec2(velocity.X, velocity.Y));
		}
		void AddForce(const Vector2& force)
		{
			b2Vec2 vel = Body->GetLinearVelocity();
			Body->SetLinearVelocity(b2Vec2(vel.x + force.X, vel.y + force.Y));
		}

		Entity* OwnerEntity;
		b2Body* Body = nullptr;
		RIGIDBODY_TYPE RigidbodyType;
	};
	struct CircleCollider2D
	{
		CircleCollider2D() = delete;
		CircleCollider2D(Entity* entity, const Vector2& offset = Vector2::Empty())
			: OwnerEntity(entity)
		{
			Transform& transform = OwnerEntity->GetComponent<Transform>();
			b2Body* body = OwnerEntity->GetBody();
			body->DestroyFixture(body->GetFixtureList());
			b2CircleShape shape;
			shape.m_p.Set(offset.X, offset.Y);
			shape.m_radius = transform.Size.X / 2 / Physics::PPM;
			b2FixtureDef fixtureDef;
			fixtureDef.shape = &shape;
			fixtureDef.density = 1.0f;
			fixtureDef.friction = 0.3f;
			Collider = body->CreateFixture(&fixtureDef);
		}

		Entity* OwnerEntity;
		b2Fixture* Collider;
	};
	struct BoxCollider2D
	{
		BoxCollider2D() = delete;
		BoxCollider2D(Entity* entity, const Vector2& offset = Vector2::Empty())
			: OwnerEntity(entity)
		{
			if (offset == Vector2::Empty() && !OwnerEntity->HasComponent<CircleCollider2D>() && !OwnerEntity->HasComponent<BoxCollider2D>())
			{
				Collider = OwnerEntity->GetBody()->GetFixtureList();
				Collider->SetSensor(false);
			}
			else
			{
				Transform& transform = OwnerEntity->GetComponent<Transform>();
				b2Body* body = OwnerEntity->GetBody();
				body->DestroyFixture(body->GetFixtureList());
				b2PolygonShape shape;
				shape.SetAsBox(transform.Size.X / 2 / Physics::PPM, transform.Size.Y / 2 / Physics::PPM);
				b2FixtureDef fixtureDef;
				fixtureDef.shape = &shape;
				fixtureDef.density = 1.0f;
				fixtureDef.friction = 0.3f;
				Collider = body->CreateFixture(&fixtureDef);
			}
		}

		Entity* OwnerEntity;
		b2Fixture* Collider;
	};

	//Scripting
	struct ScriptableEntity
	{
		virtual ~ScriptableEntity() { }

		template<typename T>
		T& GetComponent()
		{
			return m_Entity.GetComponent<T>();
		}

	protected:
		virtual void Setup() { }
		virtual void Update() { }
		virtual void Destroy() { }

	private:
		Entity m_Entity;
		friend class Scene;
	};
	struct NativeScript
	{
		NativeScript() = delete;
		NativeScript(Entity* entity)
			: OwnerEntity(entity) { }

		Entity* OwnerEntity;
		ScriptableEntity* Instance = nullptr;

		ScriptableEntity*(*InstantiateScript)() = nullptr;
		void(*DestroyScript)(NativeScript*) = nullptr;

		template<typename T>
		void Bind()
		{
			InstantiateScript = []() { return static_cast<ScriptableEntity*>(new T()); };
			DestroyScript = [](NativeScript* ns) { delete ns->Instance; ns->Instance = nullptr; };
		}
	};
}