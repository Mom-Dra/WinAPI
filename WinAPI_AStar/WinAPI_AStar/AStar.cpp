#include "AStar.h"
#include <unordered_map>
#include <unordered_set>
#include <queue>

std::vector<std::pair<int, int>> AStar::FindPath()
{
	// 아직 평가를 해야할 노드
	std::priority_queue<Node> openSet;

	// 평가를 마친 노드
	std::unordered_set<int> closedSet;
	std::unordered_map<int, std::unordered_map<int, double>> gCost;
	std::unordered_map<int, std::unordered_map<int, std::pair<int, int>>> cameFrom;

	// 처음에는 시작 노드로 시작한다!
	openSet.push({ startX, startY, 0.0, 9999 });

	while (!openSet.empty())
	{
		Node current{ openSet.top() };
		openSet.pop();

		// 목표에 도착하면 경로 재구성
		if (current.x == goalX && current.y == goalY)
		{

		}

		// 현재 노드를 closed set에 추가
		//closedSet.insert(current.x)
	}

	return std::vector<std::pair<int, int>>();
}
