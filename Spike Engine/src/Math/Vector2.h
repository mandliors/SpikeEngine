#pragma once

#include "SDL.h"
#include <iostream>
#include <math.h>

namespace Spike
{
	struct Vector2
	{
		float X, Y;
		Vector2()
			: X(0), Y(0) { }
		Vector2(float xC, float yC)
			: X(xC), Y(yC) { }
		Vector2(const Vector2& other) = default;
		Vector2 Add(const Vector2& other) const;
		Vector2 Subtract(const Vector2& other) const;
		Vector2 Multiply(const Vector2& other) const;
		Vector2 Multiply(const float value) const;
		Vector2 Divide(const Vector2& other) const;
		Vector2 Divide(const float value) const;
		Vector2 operator+(const Vector2& other) const;
		Vector2& operator+=(const Vector2& other);
		Vector2 operator-(const Vector2& other) const;
		Vector2& operator-=(const Vector2& other);
		Vector2 operator*(const Vector2& other) const;
		Vector2 operator*(const float value) const;
		Vector2& operator*=(const Vector2& other);
		Vector2& operator*=(const float value);
		Vector2 operator/(const Vector2& other) const;
		Vector2 operator/(const float value) const;
		Vector2& operator/=(const Vector2& other);
		Vector2& operator/=(const float other);
		friend bool operator==(const Vector2& a, const Vector2& b);
		float Magnitude();
		float SquaredMagnitude();
		Vector2 Normalize();
		friend std::ostream& operator<<(std::ostream& stream, const Vector2& other);

		static SDL_Rect VecsToRect(const Vector2& vec, const Vector2& vec2);
		static Vector2 Empty();
		static Vector2 Identity();
		static Vector2 Up();
		static Vector2 Down();
		static Vector2 Left();
		static Vector2 Right();
	};
}