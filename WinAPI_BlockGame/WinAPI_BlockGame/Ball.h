#pragma once
#include "Object.h"
#include "Vector2.h"
#include "Matrix3x3.h"
#include "Block.h"
#include "MoveableBlock.h"
#include <cmath>
#include <algorithm>

class Ball : public Object
{
private:
	float radius;
	Vector2 moveDir;
	float speed;
	Matrix3x3 transformMatrix;

private:
	inline constexpr void SetMoveDir(const Vector2& moveDir) noexcept;

public:
	explicit inline constexpr Ball();
	explicit inline constexpr Ball(const Vector2& center, float radius, float speed);

	inline constexpr void Init() noexcept override;
	inline void Draw(const HDC& hdc) const noexcept override;
	inline constexpr void Update(const float deltaTime) override;
	bool CheckCollisionWithBlock(const Block& block) noexcept;
	bool CheckCollisionWithMoveableBlock(const MoveableBlock& block) noexcept;
	bool CheckCollisionWithWall(const int width, const int height) noexcept;
};

inline constexpr void Ball::SetMoveDir(const Vector2& moveDir) noexcept
{
	this->moveDir = moveDir;
}

inline constexpr Ball::Ball() : Ball{ Vector2::Zero, 1.0f , 10.0f }
{
}

inline constexpr Ball::Ball(const Vector2& center, float radius, float speed) : Object{ center }, radius{ radius }, moveDir{ -Vector2::UnitY }, speed{ speed }
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
	transformMatrix.SetTranslation(moveDir * speed * deltaTime);
	SetCenter(transformMatrix * GetCenter());
}
