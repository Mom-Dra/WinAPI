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
	const float speedOfBall{ 200.0f };

	const Vector2 moveableBlockCenter{ static_cast<float>(GameManager::WIDTH / 2.0f), static_cast<float>(GameManager::HEIGHT - 100) };
	const float moveableBlockWidth{ block_Width * 2 };
	const float moveableBlockHeight{ block_Height };

public:
	inline constexpr explicit DefaultGameStrategy() = default;
	inline void CreateGame(std::list<Block>& blocks, std::vector<Ball>& balls, Block& moveableBlock) const noexcept override;
};

inline void DefaultGameStrategy::CreateGame(std::list<Block>& blocks, std::vector<Ball>& balls, Block& moveableBlock) const noexcept
{
	// 블럭 갯수 맞춰주기
	int numOfBlock{ numOfWidthBlock * numOfHeightBlock };

	if (blocks.size() < numOfBlock)
	{
		int extraBlock{ numOfBlock - static_cast<int>(blocks.size()) };

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
	auto it = blocks.begin();

	for (int i{ 0 }; i < numOfBlock; ++i, ++it)
	{
		it->SetCenter(pos);

		pos.x += block_Width;

		if ((i + 1) % numOfWidthBlock == 0)
		{
			pos.x = block_Width / 2 + paddingX;
			pos.y += block_Height;
		}
	}

	// ball 설정
	if (balls.size() < numOfBall)
	{
		balls.emplace_back(moveableBlockCenter - Vector2::UnitY * 20.0f, radiusOfBall, speedOfBall);
	}
	else
	{
		balls.resize(numOfBall);
	}

	moveableBlock.SetCenter(moveableBlockCenter);
	moveableBlock.SetWidth(moveableBlockWidth);
	moveableBlock.SetHeight(moveableBlockHeight);
}