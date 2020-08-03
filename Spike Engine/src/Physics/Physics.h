#pragma once

#include "../ECS/Scene/Scene.h"
#include "Math/Vector2.h"

namespace Spike {

	class Scene;

	struct Physics
	{
		Physics() = delete;
		static float GetPPM();

		const static float PPM;
	};
}