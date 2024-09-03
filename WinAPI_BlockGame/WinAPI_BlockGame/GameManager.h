#pragma once
#include <vector>
#include <memory>
#include "Object.h"

class GameManager
{
private:
	std::vector<std::unique_ptr<Object>> objects;

public:
	inline constexpr explicit GameManager();
	inline constexpr void InitGame();
	inline constexpr void Update(const float deltaTime);
};

inline constexpr GameManager::GameManager()
{
	InitGame();
}

inline constexpr void GameManager::InitGame()
{

}

inline constexpr void GameManager::Update(const float deltaTime)
{
	for (auto& object : objects)
	{
		object->Update(deltaTime);
	}
}
