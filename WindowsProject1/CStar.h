#pragma once
#include "CObject.h"
#include "framework.h"
#include <vector>

class CStar : public CObject
{
private:
	std::vector<POINT> points;
	int radius;
	int count;

public:
	explicit CStar(const Vector2& center, const int& speed, const int& radius, const int& count, const Vector2& moveDir);

	void Update(const float& deltaTime) override;
	void Draw(const HDC& hdc) const override;
	bool Collision() override;
};

