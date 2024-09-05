#pragma once
#include "Object.h"
#include "Vector2.h"
#include "Matrix3x3.h"

class Ball : public Object
{
private:
	float radius;
	Vector2 moveDir;
	Matrix3x3 transformMatrix;

public:
	explicit inline constexpr Ball();
	explicit inline constexpr Ball(const Vector2& center, float radius);

	inline constexpr void Init() noexcept override;
	inline void Draw(const HDC& hdc) const noexcept override;
	inline constexpr void Update(const float deltaTime) override;
};

inline constexpr Ball::Ball() : Ball{ Vector2::Zero, 1.0f }
{
}

inline constexpr Ball::Ball(const Vector2& center, float radius) : Object{ center }, radius{ radius }, moveDir{ -Vector2::UnitY }
{

}

inline constexpr void Ball::Init() noexcept
{
	SetCenter(Vector2::Zero);
	moveDir = -Vector2::UnitY;
}

inline void Ball::Draw(const HDC& hdc) const noexcept
{
	Vector2 center{ GetCenter() };
	Ellipse(hdc, center.x - radius, center.y - radius, center.x + radius, center.y + radius);
}

inline constexpr void Ball::Update(const float deltaTime)
{
	transformMatrix.SetTranslation(moveDir);

	SetCenter(transformMatrix * GetCenter());
}
