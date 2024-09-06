#pragma once
#include <vector>
#include <list>
#include "Block.h"
#include "Ball.h"

class IGameStrategy
{
public:
	virtual ~IGameStrategy() = default;
	inline constexpr virtual void CreateGame(std::list<Block>& blocks, std::vector<Ball>& balls, Block& wall) const noexcept = 0;
};