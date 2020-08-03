#include "Camera2D.h"

namespace Spike {

	void Camera2D::SetPosition(const Vector2& position)
	{
		m_Position = position;
	}

	Vector2 Camera2D::GetPosition()
	{
		return m_Position;
	}

	void Camera2D::SetRotation(float rotation)
	{
		m_Rotation = rotation;
	}

	float Camera2D::GetRotation()
	{
		return m_Rotation;
	}

	void Camera2D::SetScale(float scale)
	{
		m_Scale = scale;
	}

	float Camera2D::GetScale()
	{
		return m_Scale;
	}
}