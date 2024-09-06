#pragma once
#include "Object.h"
#include "Block.h"
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
	std::unique_ptr<IGameStrategy> strategy;

	Block block;

public:
	static inline constexpr int FPS{ 60 };
	static inline constexpr float DELTATIME{ 1.0f / static_cast<float>(FPS) };
	static inline constexpr int WIDTH{ 700 };
	static inline constexpr int HEIGHT{ 700 };

public:
	inline explicit GameManager(IGameStrategy* gameStrategy);
	inline void InitGame() noexcept;
	inline constexpr void CreateGame() noexcept;

	inline void SetStrategy(IGameStrategy* newStrategy);
	inline void Update(const float deltaTime);
	inline void Draw(const HDC& hdc) const noexcept;
	inline constexpr void CheckCollision() noexcept;
};

inline GameManager::GameManager(IGameStrategy* gameStrategy) : strategy{ gameStrategy }
{
	CreateGame();
}

inline constexpr void GameManager::CreateGame() noexcept
{
	strategy->CreateGame(blocks, balls, block);
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

		ball.CheckCollisionWithWall(WIDTH, HEIGHT);
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
}