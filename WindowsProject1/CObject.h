#pragma once
#include "framework.h"
#include "Vector2.h"
#include "Matrix3x3.h"

class CObject
{
protected:
	Vector2 center;
	float angle;
	int speed;
	Vector2 moveDir;
	Matrix3x3 transposeMatrix;

	virtual void TranslateAndRotate(const Vector2& nV, float angle) = 0;
	virtual void SetPoints(const Matrix3x3& m)
	{

	}

public:
	explicit CObject(const Vector2& center, int speed, const Vector2& moveDir) : center{ center }, angle{ 0.0f }, speed { speed }, moveDir{ moveDir.Normalize() }, transposeMatrix{ Matrix3x3::Identity }
	{

	}

	void SetCenter(const Vector2& nCenter)
	{
		center = nCenter;
	}

	void SetAngle(float nAngle)
	{
		angle = nAngle;

		if (angle >= 360.0f) angle -= 360.0f;
	}

	virtual void Update(const float& deltaTime) = 0;
	virtual void Draw(const HDC& hdc) const = 0;
	virtual bool Collision() = 0;

	virtual ~CObject() = default;
};
