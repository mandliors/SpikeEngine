#pragma once

#include <iostream>

namespace Spike
{
	struct Vector3
	{
		float X, Y, Z;
		Vector3()
			: X(0), Y(0), Z(0) { }
		Vector3(float xC, float yC, float zC = 0)
			: X(xC), Y(yC), Z(zC) { }
		Vector3(const Vector3& other) = default;
		Vector3 Add(const Vector3& other) const;
		Vector3 Subtract(const Vector3& other) const;
		Vector3 Multiply(const Vector3& other) const;
		Vector3 Multiply(const float value) const;
		Vector3 Divide(const Vector3& other) const;
		Vector3 Divide(const float value) const;
		Vector3 operator+(const Vector3& other) const;
		Vector3& operator+=(const Vector3& other);
		Vector3 operator-(const Vector3& other) const;
		Vector3& operator-=(const Vector3& other);
		Vector3 operator*(const Vector3& other) const;
		Vector3 operator*(const float value) const;
		Vector3& operator*=(const Vector3& other);
		Vector3& operator*=(const float value);
		Vector3 operator/(const Vector3& other) const;
		Vector3 operator/(const float value) const;
		Vector3& operator/=(const Vector3& other);
		Vector3& operator/=(const float other);
		float Magnitude();
		float SquaredMagnitude();
		Vector3 Normalize();
		friend std::ostream& operator<<(std::ostream& stream, const Vector3& other);

		static Vector3 Empty();
		static Vector3 Identity();
		static Vector3 Up();
		static Vector3 Down();
		static Vector3 Left();
		static Vector3 Right();
		static Vector3 Forward();
		static Vector3 Backward();
	};
}