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
#include <random>

class GameManager
{
private:
	std::list<Block> blocks;
	std::vector<Ball> balls;
	std::list<Ball> items;
	std::unique_ptr<IGameStrategy> strategy;

	MoveableBlock moveAbleBlock;

public:
	static inline constexpr int FPS{ 120 };
	static inline constexpr float DELTATIME{ 1.0f / static_cast<float>(FPS) };
	static inline constexpr int WIDTH{ 700 };
	static inline constexpr int HEIGHT{ 700 };
	static inline constexpr float MOVEABLEBLOCKSPEED{ 600.0f };

	// 0 ~ 9, 9°¡ 100% È®·ü
	static inline constexpr int ITEMDROPCHANCE{ 9 };
	static inline constexpr float ITEMRADIUS{ 5.0f };
	static inline constexpr float ITEMSPEED{ 50.0f };

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
	void CheckCollision() noexcept;

	inline void GenerateItem(const Block& block) noexcept;

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

	for (const Ball& item : items)
	{
		item.Draw(hdc);
	}
}

inline void GameManager::GenerateItem(const Block& block) noexcept
{
	// center, radius, speed!
	//items.emplace_back()
	static std::random_device rd;
	static std::default_random_engine g{ rd() };
	static std::uniform_int_distribution i_dist{ 0, 9 };

	// 0 1 2 3 4 5 6 7 8 9

	if (i_dist(g) < ITEMDROPCHANCE)
	{
		items.emplace_back(block.GetCenter(), ITEMRADIUS, ITEMSPEED, Vector2::UnitY);
	}
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

	for (Ball& item : items)
	{
		item.Update(deltaTime);
	}
}
