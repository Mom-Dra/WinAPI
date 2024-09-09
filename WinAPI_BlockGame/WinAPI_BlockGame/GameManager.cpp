#include "GameManager.h"

void GameManager::CheckCollision() noexcept
{
	// 공이 블럭과 충돌하면 튀겨야 한다!!

	// Code!!

	// 8개의 공간으로 나누어야 한다!!!
	// 8개의 사분면으로 나누자!
	bool collision{ false };

	for (Ball& ball : balls)
	{
		for (std::list<Block>::iterator it{ blocks.begin() }; it != blocks.end(); ++it)
		{
			collision = ball.ReflectTheBallWithBlock(*it);

			if (collision)
			{
				GenerateItem(*it);

				blocks.erase(it);

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

	//collision = false;
	//for (std::list<Ball>::iterator it{ items.begin() }; it != items.end(); ++it)
	//{
	//	// 여기서 블럭하고 아이템 충돌 Check
	//	collision = (*it)

	//	if (collision)
	//	{
	//		it = items.erase(it);
	//		--it;
	//	}
	//}
}