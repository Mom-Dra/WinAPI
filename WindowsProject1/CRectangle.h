#pragma once
#include "CObject.h"
#include "framework.h"
#include <array>

class CRectangle : public CObject
{
private:
	std::array<POINT, 4> points;
	int length;

public:
	explicit CRectangle(const Vector2& center, const int& speed, const int& length, const Vector2& moveDir);

	void Update(const float& deltaTime) override;
	void Draw(const HDC& hdc) const override;
	bool Collision() override;

private:
	void MovePositionAndRotation();
};

