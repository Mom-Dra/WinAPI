#pragma once
#include <vector>
#include <memory>
#include "Object.h"
#include "Block.h"
#include "Ball.h"

class GameStrategy
{
public:
	virtual ~GameStrategy() = default;
	inline constexpr virtual void CreateGame() const = 0;
};

class DefaultGameStrategy : public GameStrategy
{
public:
	inline constexpr void CreateGame() const override
	{

	}
};

class GameManager
{
private:
	std::vector<Block> blocks;
	std::vector<Ball> balls;
	std::unique_ptr<GameStrategy> strategy;

public:
	inline constexpr explicit GameManager();
	inline constexpr void InitGame();
	inline constexpr void SetStrategy(std::unique_ptr<GameStrategy> newStrategy);
	inline constexpr void Update(const float deltaTime);
};

inline constexpr GameManager::GameManager()
{
	InitGame();
}

inline constexpr void GameManager::InitGame()
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

inline constexpr void GameManager::SetStrategy(std::unique_ptr<GameStrategy> newStrategy)
{
	strategy = std::move(newStrategy);
}

inline constexpr void GameManager::Update(const float deltaTime)
{

}
