#include "GameManager.h"
#include "MyRandom.h"

void GameManager::CheckCollision() noexcept
{
	bool collision{ false };

	for (Ball& ball : balls)
	{
		for (std::list<Block>::iterator it{ blocks.begin() }; it != blocks.end(); ++it)
		{
			collision = ball.ReflectTheBallWithBlock(*it);

			if (collision)
			{
				GenerateItem(*it);

				it = blocks.erase(it);

				if (it != blocks.begin())
					--it;

				break;
			}
		}

		if (collision) break;

		collision = ball.CheckCollisionWithWall(WIDTH, HEIGHT);

		if (collision) break;

		ball.ReflectTheBallWithMoveableBlock(moveAbleBlock);
	}

	// Item 충돌 판정
	// Item 생성 -> Item 충돌 -> Item이 블럭에 충돌 -> Item 효과 발동
	// Item이 바닥에 충돌 -> Item 삭제

	collision = false;
	for (std::list<Ball>::iterator it{ items.begin() }; it != items.end(); )
	{
		// 여기서 블럭하고 아이템 충돌 Check
		collision = (*it).CheckCollisionWithMoveableBlock(moveAbleBlock);

		if (collision)
		{
			it = items.erase(it);

			ApplyItem();

		}
		else
		{
			++it;
		}
	}



	if (blocks.size() == 0)
	{
		SetIsGameOver(true);
	}
}