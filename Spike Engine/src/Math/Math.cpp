#include "Math.h"

namespace Spike {

	double Math::Abs(double value)
	{
		return value < 0 ? value * -1 : value;
	}
	double Math::Sin(double value)
	{
		return sin(value);
	}
	double Math::Cos(double value)
	{
		return cos(value);
	}
	double Math::Tan(double value)
	{
		return tan(value);
	}
	double Math::Asin(double value)
	{
		return asin(value);
	}
	double Math::Acos(double value)
	{
		return acos(value);
	}
	double Math::Atan(double value)
	{
		return atan(value);
	}
	double Math::Atan2(double a, double b)
	{
		return atan2(a, b);
	}
	double Math::Log(double value)
	{
		return log(value);
	}
	double Math::Map(double value, double min, double max, double from, double to)
	{
		return (from * (max - value) + to * (value - min)) / (max - min);
	}
	double Math::Clamp(double t, double x, double y)
	{
		return t < x ? x : t > y ? y : t;
	}
	double Math::Constrain(double t, double x, double y)
	{
		return Clamp(t, x, y);
	}
	double Math::ToDegrees(double value)
	{
		return value * 57.2957795;
	}
	double Math::ToRadians(double value)
	{
		return value * 0.0174532925f;
	}
	Vector2 Math::Lerp(const Vector2& a, const Vector2& b, double t)
	{
		return a + (b - a) * t;
	}
	Vector3 Math::Lerp(const Vector3& a, const Vector3& b, double t)
	{
		return a + (b - a) * t;
	}
}