#pragma once
#include "framework.h"

class CObject
{
protected:
	POINT center;
	float speed;

public:
	explicit CObject(const POINT& center, const float& speed) : center{ center }, speed{ speed }
	{}

	virtual void Update() = 0;
	virtual void Draw(const HDC& hdc) const = 0;
	virtual bool Collision() = 0;

	virtual ~CObject() = default;
};

