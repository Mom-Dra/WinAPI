#pragma once
#include "Object.h"
#include "Vector2.h"

class Ball : public Object
{
private:
	Vector2 center;
	float radius;

public:
	explicit inline constexpr Ball(const Vector2& center, float radius);

	inline void Draw(const HDC& hdc) const override;
	inline constexpr void Update(const float deltaTime) override;
};

inline constexpr Ball::Ball(const Vector2& center, float radius) : Object{ center }, radius{ radius }
{

}

inline void Ball::Draw(const HDC& hdc) const
{
	Ellipse(hdc, center.x - radius, center.y - radius, center.x + radius, center.y + radius);
}

inline constexpr void Ball::Update(const float deltaTime)
{

}

