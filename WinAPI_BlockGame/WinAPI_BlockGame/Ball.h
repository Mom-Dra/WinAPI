#pragma once
#include "Object.h"
#include "Vector2.h"

class Ball : public Object
{
private:
	float radius;
	Vector2 moveDir;

public:
	explicit inline constexpr Ball(const Vector2& center, float radius);

	inline constexpr void Init() override;
	inline void Draw(const HDC& hdc) const override;
	inline constexpr void Update(const float deltaTime) override;
};

inline constexpr Ball::Ball(const Vector2& center, float radius) : Object{ center }, radius{ radius }, moveDir{ -Vector2::UnitY }
{

}

inline constexpr void Ball::Init()
{
	SetCenter(Vector2::Zero);
	moveDir = -Vector2::UnitY;
}

inline void Ball::Draw(const HDC& hdc) const
{
	Vector2 center{ GetCenter() };
	Ellipse(hdc, center.x - radius, center.y - radius, center.x + radius, center.y + radius);
}

inline constexpr void Ball::Update(const float deltaTime)
{

}
