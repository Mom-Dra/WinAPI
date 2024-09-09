#include "DefaultGameStrategy.h"

void DefaultGameStrategy::CreateGame(std::list<Block>& blocks, std::vector<Ball>& balls, Block& moveableBlock) const noexcept
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
		balls.emplace_back(moveableBlockCenter - Vector2::UnitY * 20.0f, radiusOfBall, speedOfBall, -Vector2::UnitY);
	}
	else
	{
		balls.resize(numOfBall);
	}

	moveableBlock.SetCenter(moveableBlockCenter);
	moveableBlock.SetWidth(moveableBlockWidth);
	moveableBlock.SetHeight(moveableBlockHeight);
}