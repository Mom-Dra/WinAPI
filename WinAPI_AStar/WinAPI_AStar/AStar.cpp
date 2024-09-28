#include "AStar.h"
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <array>
#include <stack>

namespace std
{
	template<>
	struct hash<MomDra::AStar::Node>
	{
		std::size_t operator()(const MomDra::AStar::Node& node) const noexcept
		{
			std::hash<int> hash_func;

			return hash_func(node.x) ^ (hash_func(node.y) << 1);
		}
	};

	template<>
	struct hash<std::pair<int, int>>
	{
		std::size_t operator()(const std::pair<int, int>& pair) const noexcept
		{
			std::hash<int> hash_func;

			return hash_func(pair.first) ^ (hash_func(pair.second) << 1);
		}
	};
}

//std::vector<std::pair<int, int>> AStar::FindPath() const noexcept
//{
//	// F(x) = G(x) + H(x)
//	// 아직 평가를 해야할 노드
//	std::priority_queue<Node> openSet;
//
//	// 평가를 마친 노드
//	std::unordered_set<int> closedSet;
//
//	std::unordered_map<int, std::unordered_map<int, int>> gCost;
//	std::unordered_map<int, std::unordered_map<int, std::pair<int, int>>> cameFrom;
//
//	// 처음에는 시작 노드로 시작한다!
//	openSet.emplace(startX, startY, 0.0, Heuristic(startX, startY, goalX, goalY));
//	gCost[startX][startY] = 0;
//
//	std::array<std::pair<int, int>, 4> directions{ { {0, 1}, {1, 0}, {0, -1}, {-1, 0} } };
//	std::pair<int, int> minusPair{ std::make_pair(-1, -1) };
//
//	while (!openSet.empty())
//	{
//		Node current{ openSet.top() };
//		openSet.pop();
//
//		// 목표에 도착하면 경로 구성
//		if (current.x == goalX && current.y == goalY)
//		{
//			std::vector<std::pair<int, int>> path;
//
//			int x{ current.x };
//			int y{ current.y };
//
//			while (cameFrom[x][y] != minusPair)
//			{
//				path.emplace_back(x, y);
//				const auto& [prevX, prevY] {cameFrom[x][y]};
//
//				x = prevX;
//				y = prevY;
//			}
//
//			path.emplace_back(startX, startY);
//			std::reverse(path.begin(), path.end());
//
//			return path;
//		}
//
//		// 현재 노드를 closed set에 추가
//		closedSet.emplace(current.x * grid[0].size() + current.y);
//
//		// 인접한 노드 검사
//		for (const auto& [dx, dy] : directions)
//		{
//			int neighborX{ current.x + dx };
//			int neighborY{ current.y + dy };
//
//			// 맵 범위 체크 및 장애물 검사
//			if (neighborX >= 0 && neighborY >= 0 && neighborX < grid.size() && neighborY < grid[0].size() && grid[neighborX][neighborY] == 0)
//			{
//				int neighborKey{ neighborX * static_cast<int>(grid[0].size()) + neighborY };
//
//				// 이미 ClosedSet에 있는 노드는 무시
//				
//				if (closedSet.find(neighborKey) != closedSet.end())
//					continue;
//
//				int tentativeScore{ gCost[current.x][current.y] + 1 };
//
//				if (gCost.find(neighborX) == gCost.end() || gCost[neighborX].find(neighborY) == gCost[neighborX].end() || tentativeScore < gCost[neighborX][neighborY])
//				{
//					cameFrom[neighborX][neighborY] = { current.x, current.y };
//					gCost[neighborX][neighborY] = tentativeScore;
//
//					int h{ Heuristic(neighborX, neighborY, goalX, goalY) };
//					openSet.emplace(neighborX, neighborY, tentativeScore, h);
//				}
//			}
//		}
//	}
//
//	return std::vector<std::pair<int, int>>{};
//}

namespace MomDra
{
	std::vector<std::pair<int, int>> AStar::FindPath2() const noexcept
	{
		// F(x) = G(x) + H(x)
		// 아직 평가를 해야할 노드
		std::priority_queue<Node> openSet;

		// 평가를 마친 노드
		std::unordered_set<std::pair<int, int>> closeSet;
		std::unordered_map<std::pair<int, int>, int> gCost;
		std::unordered_map<std::pair<int, int>, std::pair<int, int>> cameFrom;
		std::array<std::pair<int, int>, 8> directions{ { { 0, 1 }, { 1, 0 }, { 0, -1 }, { -1, 0 }, { 1, 1 }, { 1 , -1 }, { -1, 1 }, { -1, -1 } } };

		openSet.emplace(startX, startY, 0.0, Heuristic(startX, startY, goalX, goalY));
		// 처음에는 시작 노드로 시작한다!

		std::pair<int, int> tmp;

		while (!openSet.empty())
		{
			Node current{ openSet.top() };
			openSet.pop();

			closeSet.emplace(current.x, current.y);

			if (current.x == goalX && current.y == goalY)
			{
				std::vector<std::pair<int, int>> path;
				std::stack<std::pair<int, int>> st;

				tmp = { current.x, current.y };

				while (cameFrom.find(tmp) != cameFrom.end())
				{
					st.emplace(tmp);
					tmp = cameFrom[tmp];
				}

				st.emplace(startX, startY);

				path.reserve(st.size());

				while (!st.empty())
				{
					path.emplace_back(st.top());
					st.pop();
				}

				return path;
			}

			for (const auto& [dx, dy] : directions)
			{
				int nx{ current.x + dx };
				int ny{ current.y + dy };

				if (nx >= 0 && ny >= 0 && nx < grid.size() && ny < grid[0].size())
				{
					tmp = { nx, ny };

					if (closeSet.find(tmp) == closeSet.end())
					{
						int newGCost{ current.g + 10 };

						if (gCost.find(tmp) == gCost.end() || gCost[tmp] < newGCost)
						{
							gCost[tmp] = newGCost;
							cameFrom[tmp] = std::make_pair(current.x, current.y);

							int h{ Heuristic(nx, ny, goalX, goalY) };
							openSet.emplace(nx, ny, newGCost, h);
						}
					}
				}
			}
		}

		return std::vector<std::pair<int, int>>{};
	}

	// Manhatan Distance
	int AStar::Heuristic(int x1, int y1, int x2, int y2) const noexcept
	{
		int dx{ std::abs(x1 - x2) };
		int dy{ std::abs(y1 - y2) };

		int min{ std::min(dx, dy) };
		int max{ std::max(dx, dy) };

		return 14 * min + 10 * (max - min);
	}

	std::vector<std::pair<int, int>> AStar::RetracePath()
	{
		std::vector<std::pair<int, int>> track;



		return track;
	}

}

