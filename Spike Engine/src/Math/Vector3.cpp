#include "Vector3.h"

namespace Spike {

	Vector3 Vector3::Add(const Vector3& other) const
	{
		Vector3 temp(*this);
		temp += other;
		return temp;
	}
	Vector3 Vector3::Subtract(const Vector3& other) const
	{
		Vector3 temp(*this);
		temp -= other;
		return temp;
	}
	Vector3 Vector3::Multiply(const Vector3& other) const
	{
		Vector3 temp(*this);
		temp *= other;
		return temp;
	}
	Vector3 Vector3::Multiply(const float value) const
	{
		Vector3 temp(*this);
		temp *= value;
		return temp;
	}
	Vector3 Vector3::Divide(const Vector3& other) const
	{
		Vector3 temp(*this);
		temp /= other;
		return temp;
	}
	Vector3 Vector3::Divide(const float value) const
	{
		Vector3 temp(*this);
		temp /= value;
		return temp;
	}
	Vector3 Vector3::operator+(const Vector3& other) const
	{
		return Add(other);
	}
	Vector3& Vector3::operator+=(const Vector3& other)
	{
		X += other.X;
		Y += other.Y;
		Z += other.Z;
		return *this;
	}
	Vector3 Vector3::operator-(const Vector3& other) const
	{
		return Subtract(other);
	}
	Vector3& Vector3::operator-=(const Vector3& other)
	{
		X -= other.X;
		Y -= other.Y;
		Z -= other.Z;
		return *this;
	}
	Vector3 Vector3::operator*(const Vector3& other) const
	{
		return Multiply(other);
	}
	Vector3 Vector3::operator*(const float value) const
	{
		return Multiply(value);
	}
	Vector3& Vector3::operator*=(const Vector3& other)
	{
		X *= other.X;
		Y *= other.Y;
		Z *= other.Z;
		return *this;
	}
	Vector3& Vector3::operator*=(const float value)
	{
		X *= value;
		Y *= value;
		Z *= value;
		return *this;
	}
	Vector3 Vector3::operator/(const Vector3& other) const
	{
		return Divide(other);
	}
	Vector3 Vector3::operator/(const float value) const
	{
		return Divide(value);
	}
	Vector3& Vector3::operator/=(const Vector3& other)
	{
		X /= other.X;
		Y /= other.Y;
		Z /= other.Z;
		return *this;
	}
	Vector3& Vector3::operator/=(const float value)
	{
		X /= value;
		Y /= value;
		Z /= value;
		return *this;
	}
	bool operator==(const Vector3& a, const Vector3& b)
	{
		return (a.X == b.X && a.Y == b.Y && a.Z == b.Z);
	}
	float Vector3::Magnitude()
	{
		return sqrt(X * X + Y * Y + Z * Z);
	}
	float Vector3::SquaredMagnitude()
	{
		return X * X + Y * Y + Z * Z;
	}
	Vector3 Vector3::Normalize()
	{
		return *this / Magnitude();
	}
	std::ostream& operator<<(std::ostream& stream, const Vector3& other)
	{
		stream << "{" << other.X << ", " << other.Y << ", " << other.Z << "}";
		return stream;
	}

	Vector3 Vector3::Empty()
	{
		Vector3 vec = Vector3(0, 0, 0);
		return vec;
	}
	Vector3 Vector3::Identity()
	{
		Vector3 vec = Vector3(1, 1, 1);
		return vec;
	}
	Vector3 Vector3::Up()
	{
		Vector3 vec = Vector3(0, -1, 0);
		return vec;
	}
	Vector3 Vector3::Down()
	{
		Vector3 vec = Vector3(0, 1, 0);
		return vec;
	}
	Vector3 Vector3::Left()
	{
		Vector3 vec = Vector3(-1, 0, 0);
		return vec;
	}
	Vector3 Vector3::Right()
	{
		Vector3 vec = Vector3(1, 0, 0);
		return vec;
	}
	Vector3 Vector3::Forward()
	{
		Vector3 vec = Vector3(0, 0, -1);
		return vec;
	}
	Vector3 Vector3::Backward()
	{
		Vector3 vec = Vector3(0, 0, 1);
		return vec;
	}
}