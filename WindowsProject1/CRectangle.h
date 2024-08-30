#pragma once
#include "CObject.h"
#include "framework.h"
#include <array>

class CRectangle : public CObject
{
private:
	std::array<POINT, 4> points;
	std::array<Vector2, 4> vPoints;
	int length;

public:
	explicit CRectangle(const Vector2& center, const int& speed, const int& length, const Vector2& moveDir);

	void Update(const float& deltaTime) override;
	void Draw(const HDC& hdc) const override;
	bool Collision() override;

private:
	void TranslateAndRotate(const Vector2& nV, float angle) override;
	void SetPoints(const Matrix3x3& m) override;
};

