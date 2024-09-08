#pragma once
#include "Object.h"
#include "Block.h"
#include "MoveableBlock.h"
#include "Ball.h"
#include "framework.h"
#include "IGameStrategy.h"
#include <vector>
#include <list>
#include <memory>

class GameManager
{
private:
	std::list<Block> blocks;
	std::vector<Ball> balls;
	std::list<Ball> items;
	std::unique_ptr<IGameStrategy> strategy;

	MoveableBlock moveAbleBlock;

public:
	static inline constexpr int FPS{ 60 };
	static inline constexpr float DELTATIME{ 1.0f / static_cast<float>(FPS) };
	static inline constexpr int WIDTH{ 700 };
	static inline constexpr int HEIGHT{ 700 };
	static inline constexpr float MOVEABLEBLOCKSPEED{ 600.0f };

	enum class KEY
	{
		NONE,
		LEFT,
		RIGHT
	};

public:
	inline explicit GameManager(IGameStrategy* gameStrategy);
	inline void InitGame() noexcept;
	inline constexpr void CreateGame() noexcept;

	inline void SetStrategy(IGameStrategy* newStrategy);
	inline void Update(const float deltaTime);
	inline void Draw(const HDC& hdc) const noexcept;
	inline constexpr void CheckCollision() noexcept;

	inline constexpr void GenerateItem() noexcept;

	inline constexpr void KeyDown(KEY key);
};

inline GameManager::GameManager(IGameStrategy* gameStrategy) : strategy{ gameStrategy }
{
	CreateGame();
}

inline constexpr void GameManager::CreateGame() noexcept
{
	strategy->CreateGame(blocks, balls, moveAbleBlock);
}

inline void GameManager::SetStrategy(IGameStrategy* newStrategy)
{
	std::unique_ptr<IGameStrategy> tmp{ newStrategy };
	strategy = std::move(tmp);
}

inline void GameManager::Draw(const HDC& hdc) const noexcept
{
	for (const Block& block : blocks)
	{
		block.Draw(hdc);
	}

	for (const Ball& ball : balls)
	{
		ball.Draw(hdc);
	}

	moveAbleBlock.Draw(hdc);
}

inline constexpr void GameManager::CheckCollision() noexcept
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
			collision = ball.CheckCollisionWithBlock(*it);

			if (collision)
			{
				blocks.erase(it);

				break;
			}
		}

		if (collision) break;

		collision = ball.CheckCollisionWithWall(WIDTH, HEIGHT);

		if (collision) break;

		ball.CheckCollisionWithMoveableBlock(moveAbleBlock);
	}

	// Item 충돌 판정
	// Item 생성 -> Item 충돌 -> Item이 블럭에 충돌 -> Item 효과 발동
	// Item이 바닥에 충돌 -> Item 삭제

	collision = false;
	for (std::list<Ball>::iterator it{ items.begin() }; it != items.end(); ++it)
	{
		// 여기서 블럭하고 아이템 충돌 Check
		//collision = (*it)

		if (collision)
		{
			GenerateItem();
			it = items.erase(it);
			--it;
		}
	}
}

inline constexpr void GameManager::GenerateItem() noexcept
{

}

inline constexpr void GameManager::KeyDown(KEY key)
{
	switch (key)
	{
	case KEY::NONE:
		moveAbleBlock.SetMoveDir(Vector2::Zero);
		break;
	case KEY::LEFT:
		moveAbleBlock.SetMoveDir(-Vector2::UnitX);
		break;
	case KEY::RIGHT:
		moveAbleBlock.SetMoveDir(Vector2::UnitX);
		break;
	default:
		break;
	}
}

inline void GameManager::InitGame() noexcept
{
	for (Block& block : blocks)
	{
		block.Init();
	}

	for (Ball& ball : balls)
	{
		ball.Init();
	}
}

inline void GameManager::Update(const float deltaTime)
{
	for (Block& block : blocks)
	{
		block.Update(deltaTime);
	}

	for (Ball& ball : balls)
	{
		ball.Update(deltaTime);
	}

	moveAbleBlock.Update(deltaTime);
}
