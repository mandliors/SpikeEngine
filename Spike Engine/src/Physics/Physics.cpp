#include "Physics.h"

namespace Spike {

	const float Physics::PPM = 50.0f;

	void Physics::SetGravity(Scene* scene, const Vector2& gravity)
	{
		scene->m_Gravity = b2Vec2(gravity.X, gravity.Y);
		scene->m_World.SetGravity(scene->m_Gravity);
	}

	Vector2 Physics::GetGravity(Scene* scene)
	{
		return Vector2(scene->m_Gravity.x, scene->m_Gravity.y);
	}

	float Physics::GetPPM()
	{
		return PPM;
	}

}