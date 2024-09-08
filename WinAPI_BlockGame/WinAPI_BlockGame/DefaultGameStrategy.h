#pragma once
#include <vector>
#include "GameManager.h"
#include "IGameStrategy.h"
#include "Block.h"
#include "Ball.h"

class DefaultGameStrategy : public IGameStrategy
{
private:
	// 이 변수들을 상위 클래스로 빼는 방법도 고려!
	const int numOfWidthBlock{ 10 };
	const int numOfHeightBlock{ 4 };
	const float block_Width{ static_cast<float>(GameManager::WIDTH) / static_cast<float>(numOfWidthBlock + 2) };
	const float block_Height{ 25.0f };
	const float paddingX{ block_Width };
	const float paddingY{ block_Height * 2 };
	
	const int numOfBall{ 1 };
	const float radiusOfBall{ 5.0f };
	const float speedOfBall{ 600.0f };

	const Vector2 moveableBlockCenter{ static_cast<float>(GameManager::WIDTH / 2.0f), static_cast<float>(GameManager::HEIGHT - 100) };
	const float moveableBlockWidth{ block_Width * 2 };
	const float moveableBlockHeight{ block_Height };

public:
	inline constexpr explicit DefaultGameStrategy() = default;
	void CreateGame(std::list<Block>& blocks, std::vector<Ball>& balls, Block& moveableBlock) const noexcept override;
};