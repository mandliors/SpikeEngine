#pragma once

#include "Vector2.h"
#include "Vector3.h"
#include <math.h>

#define PI 3.14159265
#define TWO_PI 6.283185307
#define HALF_PI 1.570796326
#define QUARTER_PI 0.785398163

namespace Spike
{
	struct Math
	{
		Math() = delete;
		~Math() = default;
		
		static float Sin(float value);
		static float Cos(float value);
		static float Tan(float value);
		static float Map(float value, float min, float max, float from, float to);
		static float Clamp(float t, float x, float y);
		static float ToDegrees(float value);
		static float ToRadians(float value);
		static Spike::Vector2 Lerp(const Vector2& a, const Vector2& b, float t);
		static Spike::Vector3 Lerp(const Vector3& a, const Vector3& b, float t);
	};
}