#pragma once
#include <vector>
#include <array>

namespace MomDra
{
	class AStar
	{
	public:
		struct Node
		{
			int x, y;
			int g, h;

			explicit Node() noexcept : Node{ 0, 0, 0, 0 }
			{

			}

			explicit Node(int x, int y) noexcept : Node{ x, y, 0, 0 }
			{

			}

			explicit Node(int x, int y, int g, int h) noexcept : x{ x }, y{ y }, g{ g }, h{ h }
			{

			}

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
		explicit AStar(const std::vector<std::vector<Node>>& grid, int startX, int startY, int goalX, int goalY)
			: grid{ grid }, startX{ startX }, startY{ startY }, goalX{ goalX }, goalY{ goalY } {}

		//std::vector<std::pair<int, int>> FindPath() const noexcept;
		std::vector<std::pair<int, int>> FindPath2() const noexcept;
		int Heuristic(int x1, int y1, int x2, int y2) const noexcept;

	private:
		std::vector<std::vector<Node>> grid;
		int startX, startY, goalX, goalY;

		std::vector<std::pair<int, int>> RetracePath();
	};
}

