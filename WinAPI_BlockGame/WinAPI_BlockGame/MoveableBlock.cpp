#include "MoveableBlock.h"
#include "GameManager.h"

MoveableBlock::MoveableBlock() noexcept : MoveableBlock{ Vector2::Zero, 0.0f, 0.0f, GameManager::MOVEABLEBLOCKSPEED }
{

}

MoveableBlock::MoveableBlock(const Vector2& center, float width, float height, float speed) noexcept : Block{ center, width, height }, moveDir{ Vector2::Zero }, speed{ speed }, transformMatrix{ Matrix3x3::Identity }
{

}

void MoveableBlock::Update(const float deltaTime) noexcept
{
	transformMatrix.SetTranslation(moveDir * speed * deltaTime);

	Vector2 nextCenter{ transformMatrix * GetCenter() };
	float halfWidth{ GetWidth() / 2.0f };

	if (nextCenter.x + halfWidth >= GameManager::WIDTH || nextCenter.x - halfWidth <= 0.0f)
		return;
	
	SetCenter(nextCenter);
}