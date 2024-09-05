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
	
	const float ballCount{ 1.0f };
	const float radius{ 5.0f };

public:
	inline constexpr explicit DefaultGameStrategy() = default;
	inline constexpr void CreateGame(std::vector<Block>& blocks, std::vector<Ball>& balls, Block& wall) const noexcept override;
};

inline constexpr void DefaultGameStrategy::CreateGame(std::vector<Block>& blocks, std::vector<Ball>& balls, Block& wall) const noexcept
{
	// 블럭 갯수 맞춰주기
	int numOfBlock{ numOfWidthBlock * numOfHeightBlock };

	if (blocks.size() < numOfBlock)
	{
		int extraBlock{ numOfBlock - static_cast<int>(blocks.size()) };
		blocks.reserve(numOfBlock);

		for (int i{ 0 }; i < extraBlock; ++i)
		{
			blocks.emplace_back(Vector2::Zero, block_Width, block_Height);
		}
	}
	else
	{
		blocks.resize(numOfBlock);
	}

	// 블럭 포지션 설정
	Vector2 pos{ block_Width / 2 + paddingX, block_Height / 2 + paddingY };

	for (int i{ 0 }; i < numOfBlock; ++i)
	{
		blocks[i].SetCenter(pos);

		pos.x += block_Width;

		if ((i + 1) % numOfWidthBlock == 0)
		{
			pos.x = block_Width / 2 + paddingX;
			pos.y += block_Height;
		}
	}

	// ball 설정
	if (balls.size() < ballCount)
	{
		balls.emplace_back(Vector2{ static_cast<float>(GameManager::WIDTH / 2.0f), static_cast<float>(GameManager::HEIGHT) }, radius);
	}
	else
	{
		balls.resize(ballCount);
	}
}