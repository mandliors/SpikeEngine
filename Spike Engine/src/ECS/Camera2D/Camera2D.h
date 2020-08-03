#pragma once

#include "Math/Vector2.h"

namespace Spike {

	class Camera2D
	{
	public:
		Camera2D() = default;
		Camera2D(const Camera2D&) = default;
		Camera2D(const Vector2& position, float rotation, float scale)
			: m_Position(position)
			, m_Rotation(rotation)
			, m_Scale(scale) { }
		
		void SetPosition(const Vector2& position);
		Vector2 GetPosition();
		void SetRotation(float rotation);
		float GetRotation();
		void SetScale(float scale);
		float GetScale();

	private:
		Vector2 m_Position = Vector2::Empty();
		float m_Rotation = 0.0f;
		float m_Scale = 1.0f;
	};
}