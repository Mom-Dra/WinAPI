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
	explicit MoveableBlock() noexcept;
	explicit MoveableBlock(const Vector2& center, float width, float height, float speed) noexcept;
	
	inline constexpr void SetMoveDir(const Vector2& moveDir) noexcept;
	void Update(const float deltaTime) noexcept override;
};

inline constexpr void MoveableBlock::SetMoveDir(const Vector2& moveDir) noexcept
{
	this->moveDir = moveDir;
}

