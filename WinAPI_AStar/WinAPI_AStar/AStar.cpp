#include "AStar.h"
#include <unordered_map>
#include <unordered_set>
#include <queue>

std::vector<std::pair<int, int>> AStar::FindPath()
{
	// ���� �򰡸� �ؾ��� ���
	std::priority_queue<Node> openSet;

	// �򰡸� ��ģ ���
	std::unordered_set<int> closedSet;
	std::unordered_map<int, std::unordered_map<int, double>> gCost;
	std::unordered_map<int, std::unordered_map<int, std::pair<int, int>>> cameFrom;

	// ó������ ���� ���� �����Ѵ�!
	openSet.push({ startX, startY, 0.0, 9999 });

	while (!openSet.empty())
	{
		Node current{ openSet.top() };
		openSet.pop();

		// ��ǥ�� �����ϸ� ��� �籸��
		if (current.x == goalX && current.y == goalY)
		{

		}

		// ���� ��带 closed set�� �߰�
		//closedSet.insert(current.x)
	}

	return std::vector<std::pair<int, int>>();
}
