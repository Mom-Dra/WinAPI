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

	// Item �浹 ����
	// Item ���� -> Item �浹 -> Item�� ���� �浹 -> Item ȿ�� �ߵ�
	// Item�� �ٴڿ� �浹 -> Item ����

	collision = false;
	for (std::list<Ball>::iterator it{ items.begin() }; it != items.end(); )
	{
		// ���⼭ ���ϰ� ������ �浹 Check
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