#include "Math.h"

namespace Spike {

	float Math::Sin(float value)
	{
		return (float)sin(value);
	}
	float Math::Cos(float value)
	{
		return (float)cos(value);
	}
	float Math::Tan(float value)
	{
		return (float)tan(value);
	}
	float Math::Asin(float value)
	{
		return (float)asin(value);
	}
	float Math::Acos(float value)
	{
		return (float)acos(value);
	}
	float Math::Atan(float value)
	{
		return (float)atan(value);
	}
	float Math::Atan2(float a, float b)
	{
		return (float)atan2(a, b);
	}
	float Math::Map(float value, float min, float max, float from, float to)
	{
		return (from * (max - value) + to * (value - min)) / (max - min);
	}
	float Math::Clamp(float t, float x, float y)
	{
		return t < x ? x : t > y ? y : t;
	}
	float Math::Constrain(float t, float x, float y)
	{
		return Clamp(t, x, y);
	}
	float Math::ToDegrees(float value)
	{
		return value * 57.2957795;
	}
	float Math::ToRadians(float value)
	{
		return value * 0.0174532925f;
	}
	Vector2 Math::Lerp(const Vector2& a, const Vector2& b, float t)
	{
		return a + (b - a) * t;
	}
	Vector3 Math::Lerp(const Vector3& a, const Vector3& b, float t)
	{
		return a + (b - a) * t;
	}

	bool Math::OverlapPoint(const Vector2& point, const Vector2& position, const Vector2& size)
	{
		if (point.X < position.X || point.X > position.X + size.X) return false;
		if (point.Y < position.Y || point.Y > position.Y + size.Y) return false;
		return true;
	}
}