#include "Vector2.h"

namespace Spike {

	Vector2 Vector2::Add(const Vector2& other) const
	{
		Vector2 temp(*this);
		temp += other;
		return temp;
	}
	Vector2 Vector2::Subtract(const Vector2& other) const
	{
		Vector2 temp(*this);
		temp -= other;
		return temp;
	}
	Vector2 Vector2::Multiply(const Vector2& other) const
	{
		Vector2 temp(*this);
		temp *= other;
		return temp;
	}
	Vector2 Vector2::Multiply(const float value) const
	{
		Vector2 temp(*this);
		temp *= value;
		return temp;
	}
	Vector2 Vector2::Divide(const Vector2& other) const
	{
		Vector2 temp(*this);
		temp /= other;
		return temp;
	}
	Vector2 Vector2::Divide(const float value) const
	{
		Vector2 temp(*this);
		temp /= value;
		return temp;
	}
	Vector2 Vector2::operator+(const Vector2& other) const
	{
		return Add(other);
	}
	Vector2& Vector2::operator+=(const Vector2& other)
	{
		X += other.X;
		Y += other.Y;
		return *this;
	}
	Vector2 Vector2::operator-(const Vector2& other) const
	{
		return Subtract(other);
	}
	Vector2& Vector2::operator-=(const Vector2& other)
	{
		X -= other.X;
		Y -= other.Y;
		return *this;
	}
	Vector2 Vector2::operator*(const Vector2& other) const
	{
		return Multiply(other);
	}
	Vector2 Vector2::operator*(const float value) const
	{
		return Multiply(value);
	}
	Vector2& Vector2::operator*=(const Vector2& other)
	{
		X *= other.X;
		Y *= other.Y;
		return *this;
	}
	Vector2& Vector2::operator*=(const float value)
	{
		X *= value;
		Y *= value;
		return *this;
	}
	Vector2 Vector2::operator/(const Vector2& other) const
	{
		return Divide(other);
	}
	Vector2 Vector2::operator/(const float value) const
	{
		return Divide(value);
	}
	Vector2& Vector2::operator/=(const Vector2& other)
	{
		X /= other.X;
		Y /= other.Y;
		return *this;
	}
	Vector2& Vector2::operator/=(const float value)
	{
		X /= value;
		Y /= value;
		return *this;
	}
	bool operator==(const Vector2& a, const Vector2& b)
	{
		return (a.X == b.X && a.Y == b.Y);
	}
	float Vector2::Magnitude()
	{
		return sqrt(X * X + Y * Y);
	}
	float Vector2::SquaredMagnitude()
	{
		return X * X + Y * Y;
	}
	Vector2 Vector2::Normalize()
	{
		return *this / Magnitude();
	}
	std::ostream& operator<<(std::ostream& stream, const Vector2& other)
	{
		stream << "{" << other.X << ", " << other.Y << "}";
		return stream;
	}
	SDL_Rect Vector2::VecsToRect(const Vector2& vec, const Vector2& vec2)
	{
		SDL_Rect rect;
		rect.x = vec.X;
		rect.y = vec.Y;
		rect.w = vec2.X;
		rect.h = vec2.Y;
		return rect;
	}
	Vector2 Vector2::Empty()
	{
		Vector2 vec = Vector2(0, 0);
		return vec;
	}
	Vector2 Vector2::Identity()
	{
		Vector2 vec = Vector2(1, 1);
		return vec;
	}
	Vector2 Vector2::Up()
	{
		Vector2 vec = Vector2(0, -1);
		return vec;
	}
	Vector2 Vector2::Down()
	{
		Vector2 vec = Vector2(0, 1);
		return vec;
	}
	Vector2 Vector2::Left()
	{
		Vector2 vec = Vector2(-1, 0);
		return vec;
	}
	Vector2 Vector2::Right()
	{
		Vector2 vec = Vector2(1, 0);
		return vec;
	}
}