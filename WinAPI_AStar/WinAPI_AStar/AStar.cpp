#include "AStar.h"
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <array>

struct Node
{
	int x, y;
	int g, h;

	explicit Node()
	{

	}

	bool operator==(const Node& other) const noexcept
	{
		return x == other.x && y == other.y;
	}
};

namespace std
{
	template<>
	struct hash<Node>
	{
		std::size_t operator()(const Node& node) const
		{
			std::hash<int> hash_func;

			return hash_func(node.x) ^ (hash_func(node.y) << 1);
		}
	};
}

std::vector<std::pair<int, int>> AStar::FindPath() const noexcept
{
	// F(x) = G(x) + H(x)
	// 아직 평가를 해야할 노드
	std::priority_queue<Node> openSet;

	// 평가를 마친 노드
	std::unordered_set<int> closedSet;

	std::unordered_map<int, std::unordered_map<int, int>> gCost;
	std::unordered_map<int, std::unordered_map<int, std::pair<int, int>>> cameFrom;

	// 처음에는 시작 노드로 시작한다!
	openSet.emplace(startX, startY, 0.0, Heuristic(startX, startY, goalX, goalY));
	gCost[startX][startY] = 0;

	std::array<std::pair<int, int>, 4> directions{ { {0, 1}, {1, 0}, {0, -1}, {-1, 0} } };
	std::pair<int, int> minusPair{ std::make_pair(-1, -1) };

	while (!openSet.empty())
	{
		Node current{ openSet.top() };
		openSet.pop();

		// 목표에 도착하면 경로 구성
		if (current.x == goalX && current.y == goalY)
		{
			std::vector<std::pair<int, int>> path;

			int x{ current.x };
			int y{ current.y };

			while (cameFrom[x][y] != minusPair)
			{
				path.emplace_back(x, y);
				const auto& [prevX, prevY] {cameFrom[x][y]};

				x = prevX;
				y = prevY;
			}

			path.emplace_back(startX, startY);
			std::reverse(path.begin(), path.end());

			return path;
		}

		// 현재 노드를 closed set에 추가
		closedSet.emplace(current.x * grid[0].size() + current.y);

		// 인접한 노드 검사
		for (const auto& [dx, dy] : directions)
		{
			int neighborX{ current.x + dx };
			int neighborY{ current.y + dy };

			// 맵 범위 체크 및 장애물 검사
			if (neighborX >= 0 && neighborY >= 0 && neighborX < grid.size() && neighborY < grid[0].size() && grid[neighborX][neighborY] == 0)
			{
				int neighborKey{ neighborX * grid[0].size() + neighborY };

				// 이미 ClosedSet에 있는 노드는 무시
				
				if (closedSet.find(neighborKey) != closedSet.end())
					continue;

				int tentativeScore{ gCost[current.x][current.y] + 1 };

				if (gCost.find(neighborX) == gCost.end() || gCost[neighborX].find(neighborY) == gCost[neighborX].end() || tentativeScore < gCost[neighborX][neighborY])
				{
					cameFrom[neighborX][neighborY] = { current.x, current.y };
					gCost[neighborX][neighborY] = tentativeScore;

					int h{ Heuristic(neighborX, neighborY, goalX, goalY) };
					openSet.emplace(neighborX, neighborY, tentativeScore, h);
				}
			}
		}
	}

	return std::vector<std::pair<int, int>>{};
}

std::vector<std::pair<int, int>> AStar::FindPath2() const noexcept
{
	std::priority_queue<Node> openSet;
	std::array<std::pair<int, int>, 4> directions{ { {0, 1}, {1, 0}, {0, -1}, {-1, 0} } };

	while (!openSet.empty())
	{
		Node current{ openSet.top() };
		openSet.pop();

		if (current.x == goalX && current.y == goalY)
			break;

		for (const auto& [dx, dy] : directions)
		{
			int nx{ current.x + dx };
			int ny{ current.y + dy };

			if (nx >= 0 && ny >= 0 && nx < grid.size() && ny < grid.size())
			{
				int nKey{ nx * grid[0].size() + ny };


			}
		}
	}

	return std::vector<std::pair<int, int>>();
}

// Manhatan Distance
int AStar::Heuristic(int x1, int y1, int x2, int y2) const noexcept
{
	return std::abs(x1 - x2) + std::abs(y1 - y2);
}
