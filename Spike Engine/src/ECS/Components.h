#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "Math/Vector2.h"
#include "Rendering/Renderer2D.h"
#include "Rendering/Color.h"
#include "Core/Core.h"

namespace Spike {

	//basic
	struct Tag
	{
		std::string Name;

		Tag() = default;
		Tag(const Tag&) = default;
		Tag(std::string name)
			: Name(name) { }
	};
	struct Transform
	{
		Vector2 Position;
		Vector2 Size;
		int Rotation = 0;
		bool Active = true;

		Transform() = default;
		Transform(const Transform&) = default;
		Transform(const Vector2& position, const Vector2& size, int rotation)
			: Position(position), Size(size), Rotation(rotation) { }
	};

	//Rendering
	struct SpriteRenderer
	{
		Color RenderColor = Color::White();
		std::string Path;

		SpriteRenderer() = default;
		SpriteRenderer(const SpriteRenderer&) = default;
		SpriteRenderer(const Color& color)
			: RenderColor(color) { }
		SpriteRenderer(const std::string& path, const Color& color = Color::White())
			: Path(path), RenderColor(color) { }
	};
	struct TextRenderer
	{
		Color RenderColor = Color::White();
		std::string Text;

		TextRenderer() = default;
		TextRenderer(const TextRenderer&) = default;
		TextRenderer(const std::string& text, const Color& color = Color::White())
			: Text(text), RenderColor(color) { }
	};

	//Physics
	struct Rigidbody2D
	{
		b2Body* Body = nullptr;
	};
	struct StaticRigidbody2D : Rigidbody2D
	{
		StaticRigidbody2D() = delete;
		StaticRigidbody2D(Scene* scene, const Vector2& position, const Vector2& size)
		{
			b2BodyDef bodyDef;
			bodyDef.position.Set((position.X - size.X / 2) / Physics::PPM, (position.Y - size.Y / 2) / Physics::PPM);
			Body = scene->GetPhysicsWorld()->CreateBody(&bodyDef);
			b2PolygonShape shape;
			shape.SetAsBox(size.X / 2 / Physics::PPM, size.Y / 2 / Physics::PPM);
			b2Fixture* fixture = Body->CreateFixture(&shape, 0.0f);
			fixture->SetSensor(true);
		}
	};
	struct KinematicRigidbody2D : Rigidbody2D
	{
		KinematicRigidbody2D() = delete;
		KinematicRigidbody2D(Scene* scene, const Vector2& position, const Vector2& size)
		{
			b2BodyDef bodyDef;
			bodyDef.type = b2_kinematicBody;
			bodyDef.position.Set((position.X - size.X / 2) / Physics::PPM, (position.Y - size.Y / 2) / Physics::PPM);
			Body = scene->GetPhysicsWorld()->CreateBody(&bodyDef);
			b2PolygonShape shape;
			shape.SetAsBox(size.X / 2 / Physics::PPM, size.Y / 2 / Physics::PPM);
			b2FixtureDef fixtureDef;
			fixtureDef.shape = &shape;
			fixtureDef.density = 1.0f;
			fixtureDef.friction = 0.3f;
			b2Fixture* fixture = Body->CreateFixture(&fixtureDef);
			fixture->SetSensor(true);
		}
	};
	struct DynamicRigidbody2D : Rigidbody2D
	{
		DynamicRigidbody2D() = delete;
		DynamicRigidbody2D(Scene* scene, const Vector2& position, const Vector2& size)
		{
			b2BodyDef bodyDef;
			bodyDef.type = b2_dynamicBody;
			bodyDef.position.Set((position.X - size.X / 2) / Physics::PPM, (position.Y - size.Y / 2) / Physics::PPM);
			Body = scene->GetPhysicsWorld()->CreateBody(&bodyDef);
			b2PolygonShape shape;
			shape.SetAsBox(size.X / 2 / Physics::PPM, size.Y / 2 / Physics::PPM);
			b2FixtureDef fixtureDef;
			fixtureDef.shape = &shape;
			fixtureDef.density = 1.0f;
			fixtureDef.friction = 0.3f;
			b2Fixture* fixture = Body->CreateFixture(&fixtureDef);
			fixture->SetSensor(true);
		}
	};
}