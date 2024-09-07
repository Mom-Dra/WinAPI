#pragma once
#include "Block.h"
#include "Vector2.h"
#include "Matrix3x3.h"

class MoveableBlock : public Block
{
private:
	Vector2 moveDir;
	float speed;
	Matrix3x3 transformMatrix;

public:
	explicit inline constexpr MoveableBlock() noexcept;
	explicit inline constexpr MoveableBlock(const Vector2& center, float width, float height, float speed) noexcept;
	
	inline constexpr void SetMoveDir(const Vector2& moveDir) noexcept;
	inline constexpr void Update(const float deltaTime) override;
};

inline constexpr MoveableBlock::MoveableBlock() noexcept : Block{}, moveDir{ Vector2::Zero }, speed{ 100.0f }, transformMatrix{ Matrix3x3::Identity }
{
}

inline constexpr MoveableBlock::MoveableBlock(const Vector2& center, float width, float height, float speed) noexcept : Block{ center, width, height }, moveDir{ Vector2::Zero }, speed{ 100.0f }, transformMatrix{ Matrix3x3::Identity }
{

}

inline constexpr void MoveableBlock::SetMoveDir(const Vector2& moveDir) noexcept
{
	this->moveDir = moveDir;
}

inline constexpr void MoveableBlock::Update(const float deltaTime)
{
	transformMatrix.SetTranslation(moveDir * speed * deltaTime);
	SetCenter(transformMatrix * GetCenter());
}
