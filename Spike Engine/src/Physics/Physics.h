#pragma once

#include "../ECS/Scene/Scene.h"
#include "Math/Vector2.h"

namespace Spike {

	class Scene;

	struct Physics
	{
		Physics() = delete;

		static void SetGravity(Scene* scene, const Vector2& gravity);
		static Vector2 GetGravity(Scene* scene);
		static float GetPPM();

		const static float PPM;
	};
}