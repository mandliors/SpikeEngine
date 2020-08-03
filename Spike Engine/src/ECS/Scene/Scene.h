#pragma once

#include "ECS/EnTT/entt.hpp"
#include "Physics/Box2D/box2d.h"
#include "Physics/Physics.h"
#include "../Camera2D/Camera2D.h"

namespace Spike {

	class Entity;
	struct Physics;

	class Scene
	{
	public:
		Scene() { }
		~Scene();

		void Init();
		void Update();
		b2Body* CreateStaticBody(const Vector2& position, const Vector2& size);
		b2Body* CreateDynamicBody(const Vector2& position, const Vector2& size);
		Camera2D* CreateCamera(const Vector2& position = Vector2::Empty(), float rotation = 0.0f, float scale = 1.0f);
		void SetActiveCamera(int index);
		Entity CreateEntity(const std::string& name = std::string());
		void SetTimeStep(float ts);
	private:
		entt::registry m_Registry;
		b2Vec2 m_Gravity = b2Vec2(0.0f, 9.81f);
		b2World m_World = b2World(m_Gravity);
		float m_TimeStep = 0.0f;
		std::vector<Camera2D*> m_Cameras;
		Camera2D* m_ActiveCamera = nullptr;

		friend class Entity;
		friend struct Physics;
	};
}

