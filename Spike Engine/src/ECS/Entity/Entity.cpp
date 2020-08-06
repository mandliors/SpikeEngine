#include "Entity.h"
#include "ECS/Components.h"

namespace Spike {

	Entity::Entity(entt::entity entityId, Scene* scene)
		: m_EntityId(entityId), m_Scene(scene) { }

	entt::entity Entity::GetEntityID()
	{
		return m_EntityId;
	}
	void Entity::Destroy()
	{
		m_Scene->DestroyEntity(this);
	}
	Scene* Entity::GetScene()
	{
		return m_Scene;
	}
	b2Body* Entity::GetBody()
	{
		if (HasComponent<Rigidbody2D>()) 
			return GetComponent<Rigidbody2D>().Body;
		else
			return nullptr;
	}
}