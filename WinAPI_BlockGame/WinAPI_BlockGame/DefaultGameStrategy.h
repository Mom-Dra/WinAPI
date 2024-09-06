#pragma once
#include <vector>
#include "GameManager.h"
#include "IGameStrategy.h"
#include "Block.h"
#include "Ball.h"

class DefaultGameStrategy : public IGameStrategy
{
private:
	// �� �������� ���� Ŭ������ ���� ����� ���!
	const int numOfWidthBlock{ 10 };
	const int numOfHeightBlock{ 4 };
	const float block_Width{ static_cast<float>(GameManager::WIDTH) / static_cast<float>(numOfWidthBlock + 2) };
	const float block_Height{ 25.0f };
	const float paddingX{ block_Width };
	const float paddingY{ block_Height * 2 };
	
	const int numOfBall{ 1 };
	const float radiusOfBall{ 5.0f };
	const float speedOfBall{ 200.0f };

public:
	inline constexpr explicit DefaultGameStrategy() = default;
	inline void CreateGame(std::list<Block>& blocks, std::vector<Ball>& balls, Block& wall) const noexcept override;
};

inline void DefaultGameStrategy::CreateGame(std::list<Block>& blocks, std::vector<Ball>& balls, Block& wall) const noexcept
{
	// �� ���� �����ֱ�
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

	// �� ������ ����
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

	// ball ����
	if (balls.size() < numOfBall)
	{
		balls.emplace_back(Vector2{ static_cast<float>(GameManager::WIDTH / 2.3f), static_cast<float>(GameManager::HEIGHT - 50) }, radiusOfBall, speedOfBall);
	}
	else
	{
		balls.resize(numOfBall);
	}
}