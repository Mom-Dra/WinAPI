#pragma once
#include "AStar.h"

class GameManager
{
public:
	static GameManager& GetInstance();

	static constexpr int WIDTH{ 100 };
	static constexpr int HEIGHT{ 100 };

	static constexpr int ROWS{ 10 };
	static constexpr int COLS{ 10 };

	void Draw(const AStar& aStar) const noexcept;

private:
	explicit GameManager() noexcept;
};

