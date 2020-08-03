#include "Entity.h"

namespace Spike {

	Entity::Entity(entt::entity entityId, Scene* scene)
		: m_EntityId(entityId), m_Scene(scene) { }
}