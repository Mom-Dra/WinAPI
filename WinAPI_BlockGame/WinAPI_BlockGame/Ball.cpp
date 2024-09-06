#include "Ball.h"

bool Ball::CheckCollisionWithBlock(const Block& block) noexcept
{
	// ���� ����� �簢���� ���� ������!
	Vector2 center{ GetCenter() };

	float closestX{ std::clamp(center.x, block.GetLeft(), block.GetRight()) };
	float closestY{ std::clamp(center.x, block.GetTop(), block.GetBottom()) };

	Vector2 closestPoint{ closestX, closestY };
	Vector2 distance{ center - closestPoint };

	float left{ block.GetLeft() };
	float right{ block.GetRight() };
	float top{ block.GetTop() };
	float bottom{ block.GetBottom() };

	bool isCorner{ center.x  < left || center.x > right };

	// �� �浹 ó��
	if (distance.Magnitude() < radius)
	{
		// ���⼭ 8���� ��и����� ������!
		if (center.y <= top)
		{
			if (isCorner)
			{
				moveDir = -moveDir;
			}
			else
			{
				// �ݻ� ����!
				// R = P + 2 x (-P dot n) x n
				moveDir = moveDir + (-Vector2::UnitY) * (2 * moveDir.Dot(Vector2::UnitY));
			}
		}
		else if (center.y >= bottom)
		{
			if (isCorner)
			{
				moveDir - moveDir;
			}
			else
			{
				// �ݻ� ����
				moveDir = moveDir + Vector2::UnitY * (2 * -moveDir.Dot(Vector2::UnitY));
			}
		}
		else
		{
			// ���̿� �� ���, �ݻ� ����
			// R = P + 2 x (-P dot n) x n

			if (center.x >= right)
			{
				moveDir = moveDir + Vector2::UnitX * (2 * moveDir.Dot(Vector2::UnitX));
			}
			else if (center.x <= left)
			{
				moveDir = moveDir + (-Vector2::UnitX) * (2 * moveDir.Dot(-Vector2::UnitX));
			}
		}

		return true;
	}

	return false;
}

bool Ball::CheckCollisionWithWall(const int width, const int height) noexcept
{
	Vector2 center{ GetCenter() };

	// �� �浹 üũ
	// R = P + 2 x (-P dot n) x n
	if (center.x - radius <= 0.0f)
	{
		moveDir = moveDir + Vector2::UnitX * (2 * moveDir.Dot(Vector2::UnitX));
		return true;
	}
	else if (center.x + radius >= width)
	{
		moveDir = moveDir + (-Vector2::UnitX) * (2 * moveDir.Dot(Vector2::UnitX));

		return true;
	}
	else if (center.y - radius <= 0.0f)
	{
		moveDir = moveDir + (Vector2::UnitY) * (2 * moveDir.Dot(-Vector2::UnitY));

		return true;
	}
	else if (center.y + radius >= height)
	{
		moveDir = moveDir + (-Vector2::UnitY) * (2 * moveDir.Dot(Vector2::UnitY));

		return true;
	}

	return false;
}
