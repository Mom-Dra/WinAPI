#pragma once
#include <vector>

class AStar
{
	struct Node
	{
		int x, y;
		double g, h;

		double F() const noexcept
		{
			return g + h;
		}

		bool operator<(const Node& other) const noexcept
		{
			return F() > other.F();
		}
	};

public:
	explicit AStar(const std::vector<std::vector<int>>& grid, int startX, int startY, int goalX, int goalY)
		: grid{ grid }, startX{ startX }, startY{ startY }, goalX{ goalX }, goalY{ goalY } {}

	std::vector<std::pair<int, int>> FindPath();

private:
	std::vector<std::vector<int>> grid;
	int startX, startY, goalX, goalY;
};

