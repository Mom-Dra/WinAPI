#pragma once
#include "CObject.h"

class CCircle : public CObject
{
private:
	int radius;

public:
	inline explicit CCircle(const Vector2& center, const int& speed, const int& radius, const Vector2& moveDir);

	inline constexpr void Update(const float& deltaTime) override;
	inline void Draw(const HDC& hdc) const override;

private:
	inline constexpr void TranslateAndRotate(const Vector2& nV, float angle) override;
};

inline CCircle::CCircle(const Vector2& center, const int& speed, const int& radius, const Vector2& moveDir) : CObject{ center, speed, moveDir, static_cast<float>(radius) }, radius{ radius }
{

}

inline constexpr void CCircle::Update(const float& deltaTime)
{
	center.x += moveDir.x * speed * deltaTime;
	center.y += moveDir.y * speed * deltaTime;
}

inline void CCircle::Draw(const HDC& hdc) const
{
	Ellipse(hdc, static_cast<int>(center.x - radius), static_cast<int>(center.y + radius), static_cast<int>(center.x + radius), static_cast<int>(center.y - radius));
}

inline constexpr void CCircle::TranslateAndRotate(const Vector2& nV, float angle)
{

}