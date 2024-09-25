#include "AStar.h"
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <array>

std::vector<std::pair<int, int>> AStar::FindPath()
{
	// F(x) = G(x) + H(x)

	// ���� �򰡸� �ؾ��� ���
	std::priority_queue<Node> openSet;

	// �򰡸� ��ģ ���
	std::unordered_set<int> closedSet;
	std::unordered_map<int, std::unordered_map<int, int>> gCost;
	std::unordered_map<int, std::unordered_map<int, std::pair<int, int>>> cameFrom;

	// ó������ ���� ���� �����Ѵ�!
	openSet.emplace(startX, startY, 0.0, Heuristic(startX, startY, goalX, goalY));
	gCost[startX][startY] = 0;

	std::array<std::pair<int, int>, 4> directions{ { {0, 1}, {1, 0}, {0, -1}, {-1, 0} } };
	std::pair<int, int> minusPair{ std::make_pair(-1, -1) };

	while (!openSet.empty())
	{
		Node current{ openSet.top() };
		openSet.pop();

		// ��ǥ�� �����ϸ� ��� ����
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

		// ���� ��带 closed set�� �߰�
		closedSet.emplace(current.x * grid[0].size() + current.y);

		// ������ ��� �˻�
		for (const auto& dir : directions)
		{
			int neighborX{ current.x + dir.first };
			int neighborY{ current.x + dir.second };

			// �� ���� üũ �� ��ֹ� �˻�
			if (neighborX >= 0 && neighborY >= 0 && neighborX < grid.size() && neighborY < grid[0].size() && grid[neighborX][neighborY] == 0)
			{
				int neighborKey{ neighborX * grid[0].size() + neighborY };

				// �̹� ClosedSet�� �ִ� ���� ����
				
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

// Manhatan Distance
int AStar::Heuristic(int x1, int y1, int x2, int y2)
{
	return std::abs(x1 - x2) + std::abs(y1 - y2);
}
