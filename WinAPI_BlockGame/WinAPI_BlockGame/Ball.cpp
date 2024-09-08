#include "Ball.h"
#include <numbers>
#include <cmath>

bool Ball::CheckCollisionWithBlock(const Block& block) noexcept
{
	// ���� ����� �簢���� ���� ������!
	Vector2 center{ GetCenter() };

	float left{ block.GetLeft() };
	float right{ block.GetRight() };
	float top{ block.GetTop() };
	float bottom{ block.GetBottom() };

	float closestX{ std::clamp(center.x, left, right) };
	float closestY{ std::clamp(center.y, top, bottom) };

	Vector2 closestPoint{ closestX, closestY };
	Vector2 distance{ center - closestPoint };

	// �� �浹 ó��
	if (distance.Magnitude() <= radius)
	{
		// ���⼭ 8���� ��и����� ������!
		if (center.y <= top)
		{
			//if (isCorner)
			//{
			//	SetMoveDir(-moveDir);
			//}
			//else
			//{
			//	// �ݻ� ����!
			//	// R = P + 2 x (-P dot n) x n
			//	SetMoveDir(moveDir + (-Vector2::UnitY) * (2 * moveDir.Dot(Vector2::UnitY)));
			//}

			SetMoveDir(moveDir + (-Vector2::UnitY) * (2 * moveDir.Dot(Vector2::UnitY)));
		}
		else if (center.y >= bottom)
		{
			//if (isCorner)
			//{
			//	SetMoveDir(-moveDir);
			//}
			//else
			//{
			//	// �ݻ� ����
			//	SetMoveDir(moveDir + Vector2::UnitY * (2 * moveDir.Dot(-Vector2::UnitY)));
			//}

			SetMoveDir(moveDir + Vector2::UnitY * (2 * moveDir.Dot(-Vector2::UnitY)));
		}
		else
		{
			// ���̿� �� ���, �ݻ� ����
			// R = P + 2 x (-P dot n) x n

			if (center.x >= right)
			{
				SetMoveDir(moveDir + Vector2::UnitX * (2 * moveDir.Dot(-Vector2::UnitX)));
			}
			else if (center.x <= left)
			{
				SetMoveDir(moveDir + (-Vector2::UnitX) * (2 * moveDir.Dot(Vector2::UnitX)));
			}
		}

		return true;
	}

	return false;
}

bool Ball::CheckCollisionWithMoveableBlock(const MoveableBlock& block) noexcept
{
	Vector2 center{ GetCenter() };

	float left{ block.GetLeft() };
	float right{ block.GetRight() };
	float top{ block.GetTop() };
	float bottom{ block.GetBottom() };

	float closestX{ std::clamp(center.x, left, right) };
	float closestY{ std::clamp(center.y, top, bottom) };

	float ratio{ (closestX - left) / (right - left) };

	Vector2 closestPoint{ closestX, closestY };
	Vector2 distance{ center - closestPoint };

	
	// �� �浹 ó��
	if (distance.Magnitude() < radius)
	{
		static constexpr float degreeToRadian{ std::numbers::pi_v<float> / 180.0f };
		Vector2 rightVector{ std::cosf(-15 * degreeToRadian), std::sinf(-15 * degreeToRadian) };
		Vector2 leftVector{ std::cosf((-180 + 15) * degreeToRadian), std::sinf((-180 + 15) * degreeToRadian) };

		SetMoveDir(Vector2::Lerp(leftVector, rightVector, ratio).Normalize());

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
		SetMoveDir(moveDir + Vector2::UnitX * (2 * moveDir.Dot(-Vector2::UnitX)));
		return true;
	}
	else if (center.x + radius >= width)
	{
		SetMoveDir(moveDir + (-Vector2::UnitX) * (2 * moveDir.Dot(Vector2::UnitX)));

		return true;
	}
	else if (center.y - radius <= 0.0f)
	{
		SetMoveDir(moveDir + (Vector2::UnitY) * (2 * moveDir.Dot(-Vector2::UnitY)));

		return true;
	}
	else if (center.y + radius >= height)
	{
		SetMoveDir(moveDir + (-Vector2::UnitY) * (2 * moveDir.Dot(Vector2::UnitY)));

		return true;
	}

	return false;
}
