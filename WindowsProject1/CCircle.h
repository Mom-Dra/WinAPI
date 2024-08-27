#pragma once
#include "CObject.h"

class CCircle : public CObject
{
private:
	int radius;

public:
	explicit CCircle(const Vector2& center, const int& speed, const int& radius, const Vector2& moveDir);

	void Update(const float& deltaTime) override;
	void Draw(const HDC& hdc) const override;
	bool Collision() override;
};