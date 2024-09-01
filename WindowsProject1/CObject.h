#pragma once
#include "framework.h"
#include "Vector2.h"
#include "Matrix3x3.h"

class CObject
{
private:
	float radius;

protected:
	Vector2 center;

	float angle;
	int speed;
	Vector2 moveDir;
	Matrix3x3 transposeMatrix;
	bool isCollision;

	inline virtual void TranslateAndRotate(const Vector2& nV, float angle) = 0;
	inline virtual void SetPoints(const Matrix3x3& m);

public:
	inline explicit CObject(const Vector2& center, int speed, const Vector2& moveDir, float radius); 
	inline constexpr void SetCenter(const Vector2& nCenter);
	inline constexpr void SetAngle(float nAngle);

	inline virtual void Update(const float& deltaTime) = 0;
	inline virtual void Draw(const HDC& hdc) const = 0;
	inline bool CheckCollisionWithObject(CObject& other);
	inline constexpr void CheckCollisionWithWall(const int window_Width, const int window_Height);
	inline constexpr void InitCollision();
	inline constexpr bool GetCollision() const;

	virtual ~CObject() = default;
};

inline void CObject::SetPoints(const Matrix3x3& m)
{

}

inline CObject::CObject(const Vector2& center, int speed, const Vector2& moveDir, float radius) : radius{ radius }, center{ center }, angle{ 0.0f }, speed{ speed }, moveDir{ moveDir.Normalize() }, transposeMatrix{ Matrix3x3::Identity }, isCollision{ false }
{

}

inline constexpr void CObject::SetCenter(const Vector2& nCenter)
{
	center = nCenter;
}

inline constexpr void CObject::SetAngle(float nAngle)
{
	angle = nAngle;

	if (angle >= 360.0f) angle -= 360.0f;
}

inline bool CObject::CheckCollisionWithObject(CObject& other)
{
	float distance{ static_cast<float>(std::pow(center.x - other.center.x, 2)) + static_cast<float>(std::pow(center.y - other.center.y, 2)) };
	float SumRadius{ static_cast<float>(std::pow(radius + other.radius, 2)) };

	if (distance < SumRadius)
	{
		isCollision = true;
		other.isCollision = true;

		std::swap(speed, other.speed);
		std::swap(moveDir, other.moveDir);

		return true;
	}

	return false;
}

inline constexpr void CObject::CheckCollisionWithWall(const int window_Width, const int window_Height)
{
	// ╩С, го аб, ©Л
	// Reflect = Incident - 2 x (Incident.Dot(Normal)) x Normal

	Vector2 reflect{ moveDir };

	float left{ center.x - radius };
	float right{ center.x + radius };
	float up{ center.y - radius };
	float down{ center.y + radius };

	if (up < 0.0f)
	{
		reflect = moveDir - (Vector2::UnitY * (2 * moveDir.Dot(Vector2::UnitY)));
		isCollision = true;
	}
	else if (down > window_Height)
	{
		reflect = moveDir + Vector2::UnitY * (2 * moveDir.Dot(-Vector2::UnitY));
		isCollision = true;
	}

	moveDir = reflect;

	if (left < 0.0f)
	{
		reflect = moveDir - (Vector2::UnitX * (2 * moveDir.Dot(Vector2::UnitX)));
		isCollision = true;
	}
	else if (right > window_Width)
	{
		reflect = moveDir + Vector2::UnitX * (2 * moveDir.Dot(-Vector2::UnitX));
		isCollision = true;
	}

	moveDir = reflect;
}

inline constexpr bool CObject::GetCollision() const
{
	return isCollision;
}

inline constexpr void CObject::InitCollision()
{
	isCollision = false;
}