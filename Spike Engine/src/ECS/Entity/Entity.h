#pragma once

#include "Core/Core.h"
#include "ECS/EnTT/entt.hpp"
#include "ECS/Scene/Scene.h"
#include "ECS/Components.h"
#include <variant>

namespace Spike {

	class Entity
	{
	public:
		Entity() = default;
		Entity(entt::entity entityId, Scene* scene);
		Entity(const Entity&) = default;

		template<class T, typename... Args>
		T& AddComponent(Args&&... args)
		{
			SPIKE_ASSERT(!HasComponent<T>(), "Entity already has component!");

			if (std::is_same(T, Rigidbody2D))
			{
				Transform& transform = GetComponent<Transform>();
				return AddComponent<T>(m_EntityId, this, transform.Position, transform.Size);
			}

			return m_Scene->m_Registry.emplace<T>(m_EntityId, std::forward<Args>(args)...);
		}
		/*template<typename... Args>
		Rigidbody2D& AddComponent<Rigidbody2D>(Args&&... args)
		{
			SPIKE_ASSERT(!HasComponent<T>(), "Entity already has component!");

			Transform& transform = GetComponent<Transform>();
			return m_Scene->m_Registry.emplace<Rigidbody2D>(m_EntityId, this, transform.Position, transform.Size, std::forward<Args>(args)...);
		}*/
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
	private:
		entt::entity m_EntityId{ 0 };
		Scene* m_Scene = nullptr;
	};
}