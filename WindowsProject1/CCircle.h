#pragma once
#include "CObject.h"

class CCircle : public CObject
{
private:
	float radius;

public:
	explicit CCircle(const POINT& center, const float& speed, const float& radius);

	void Update() override;
	void Draw(const HDC& hdc) const override;
	bool Collision() override;
};