#include "Math.h"

float Spike::Math::Sin(float value)
{
	return (float)sin(value);
}
float Spike::Math::Cos(float value)
{
	return (float)cos(value);
}
float Spike::Math::Tan(float value)
{
	return (float)tan(value);
}
float Spike::Math::Map(float value, float min, float max, float from, float to)
{
	return (from * (max - value) + to * (value - min)) / (max - min);
}
float Spike::Math::Clamp(float t, float x, float y)
{
	return t < x ? x : t > y ? y : t;
}
float Spike::Math::ToDegrees(float value)
{
	return value * 57.2957795;
}
float Spike::Math::ToRadians(float value)
{
	return value * 0.0174532925f;
}
Spike::Vector2 Spike::Math::Lerp(const Vector2& a, const Vector2& b, float t)
{
	return a + (b - a) * t;
}
Spike::Vector3 Spike::Math::Lerp(const Vector3& a, const Vector3& b, float t)
{
	return a + (b - a) * t;
}