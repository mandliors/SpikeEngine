#pragma once

#include "ECS/EnTT/entt.hpp"
#include "Physics/Box2D/box2d.h"
#include "Physics/Physics.h"
#include "ECS/Camera2D/Camera2D.h"

namespace Spike {

	class Entity;

	class Scene
	{
	public:
		Scene()
			: m_World(new b2World({ 0.0f, 9.81f })) { }
		~Scene();

		void Init();
		void Update();
		Camera2D* CreateCamera(const Vector2& position = Vector2::Empty(), float rotation = 0.0f, float scale = 1.0f);
		void SetActiveCamera(int index);
		Entity& CreateEntity(const std::string& name = std::string());
		void DestroyEntity(Entity* entity);
		int GetEntityCount();
		b2World* GetPhysicsWorld();
		void SetGravity(const Vector2& gravity);
		Vector2 GetGravity();
		void SetTimeStep(float ts);

	private:
		entt::registry m_Registry;
		b2World* m_World = nullptr;
		float m_TimeStep = 0.0f;
		std::vector<Camera2D*> m_Cameras;
		std::vector<Entity*> m_Entities;
		Camera2D* m_ActiveCamera = nullptr;

		friend class Entity;
	};
}

