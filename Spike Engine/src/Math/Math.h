#pragma once

#include "Vector2.h"
#include "Vector3.h"
#include <math.h>
#include <vector>

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
		
		template<typename... Args>
		static float Min(Args&&... args)
		{
			std::vector<float> numbers = { static_cast<float>(args)... };
			if (numbers.size() == 0)
				return 0.0f;
			float min = numbers[0];
			for (size_t i = 1; i < numbers.size(); i++)
			{
				if (numbers[i] < min)
					min = numbers[i];
			}
			return min;
		}
		template<typename... Args>
		static float Max(Args&&... args)
		{
			std::vector<float> numbers = { static_cast<float>(args)... };
			if (numbers.size() == 0)
				return 0.0f;
			float max = numbers[0];
			for (size_t i = 1; i < numbers.size(); i++)
			{
				if (numbers[i] > max)
					max = numbers[i];
			}
			return max;
		}
		static float Sin(float value);
		static float Cos(float value);
		static float Tan(float value);
		static float Asin(float value);
		static float Acos(float value);
		static float Atan(float value);
		static float Atan2(float a, float b);
		static float Map(float value, float min, float max, float from, float to);
		static float Clamp(float t, float x, float y);
		static float Constrain(float t, float x, float y);
		static float ToDegrees(float value);
		static float ToRadians(float value);
		static Spike::Vector2 Lerp(const Vector2& a, const Vector2& b, float t);
		static Spike::Vector3 Lerp(const Vector3& a, const Vector3& b, float t);
		static bool OverlapPoint(const Vector2& point, const Vector2& position, const Vector2& size);
	};
}