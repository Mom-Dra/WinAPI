#pragma once
#include "CObject.h"
#include "framework.h"
#include <vector>
#include "Vector2.h"

class CStar : public CObject
{
private:
	std::vector<POINT> points;
	std::vector<Vector2> vPoints;
	int radius;
	int count;

public:
	explicit CStar(const Vector2& center, const int& speed, const int& radius, const int& count, const Vector2& moveDir);

	void Update(const float& deltaTime) override;
	void Draw(const HDC& hdc) const override;
	bool Collision() override;

private:	
	void TranslateAndRotate(const Vector2& nV, float angle) override;
	void SetPoints(const Matrix3x3& m) override;
};

