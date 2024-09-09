#include "GameManager.h"

void GameManager::CheckCollision() noexcept
{
	// ���� ���� �浹�ϸ� Ƣ�ܾ� �Ѵ�!!

	// Code!!

	// 8���� �������� ������� �Ѵ�!!!
	// 8���� ��и����� ������!
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



	// Item �浹 ����
	// Item ���� -> Item �浹 -> Item�� ���� �浹 -> Item ȿ�� �ߵ�
	// Item�� �ٴڿ� �浹 -> Item ����

	//collision = false;
	//for (std::list<Ball>::iterator it{ items.begin() }; it != items.end(); ++it)
	//{
	//	// ���⼭ ���ϰ� ������ �浹 Check
	//	collision = (*it)

	//	if (collision)
	//	{
	//		it = items.erase(it);
	//		--it;
	//	}
	//}
}