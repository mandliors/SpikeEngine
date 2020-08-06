#pragma once

#include "Core/Core.h"
#include "ECS/EnTT/entt.hpp"
#include "ECS/Scene/Scene.h"

namespace Spike {

	class Entity
	{
	public:
		Entity() = default;
		Entity(const Entity&) = default;
		Entity(entt::entity entityId, Scene* scene);

		template<typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{
			SPIKE_ASSERT(!HasComponent<T>(), "Entity already has component!");
			return m_Scene->m_Registry.emplace<T>(m_EntityId, this, std::forward<Args>(args)...);
		}
		template<typename T>
		T& GetComponent()
		{
			SPIKE_ASSERT(HasComponent<T>(), "Entity does not have component!");
			return m_Scene->m_Registry.get<T>(m_EntityId);
		}
		template<typename T>
		bool HasComponent()
		{
			return m_Scene->m_Registry.has<T>(m_EntityId);
		}
		template<typename T>
		void RemoveComponent()
		{
			SPIKE_ASSERT(HasComponent<T>(), "Entity does not have component!");
			m_Scene->m_Registry.remove<T>(m_EntityId);
		}
		entt::entity GetEntityID();
		void Destroy();
		Scene* GetScene();
		b2Body* GetBody();

	private:
		entt::entity m_EntityId{ 0 };
		Scene* m_Scene = nullptr;
	};
}