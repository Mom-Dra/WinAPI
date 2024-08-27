#pragma once
#include "framework.h"
#include "Vector2.h"

class CObject
{
protected:
	Vector2 center;
	int speed;
	Vector2 moveDir;

public:
	explicit CObject(const Vector2& center, const int& speed, const Vector2& moveDir) : center{ center }, speed{ speed }, moveDir{ moveDir.Normalize() }
	{

	}

	virtual void Update(const float& deltaTime) = 0;
	virtual void Draw(const HDC& hdc) const = 0;
	virtual bool Collision() = 0;

	virtual ~CObject() = default;
};
