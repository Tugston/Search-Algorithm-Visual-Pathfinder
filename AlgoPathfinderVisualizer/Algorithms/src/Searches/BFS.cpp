/*
*	Copyright (c) 2025 Vincent Pierce
*
*	This file is part of AlgoPathfinderVisualizer.
*	Released under MIT License.
*	See License file at the directory root for more information.
*
*/
#include "BFS.h"
#include <queue>

namespace Algorithms
{
	BFS::BFS(const std::vector<Utility::NodeStatus>& m_Graph, int startIndex, int targetIndex, const std::function<void(int)> visitFunction, const std::function<void(int)> lookFunction, uint8_t width, uint8_t height):
		BaseSearch(m_Graph, startIndex, targetIndex, visitFunction, lookFunction, width, height)
	{
	}

	BFS::~BFS()
	{
	}

	void BFS::IterativeSearch()
	{
		std::queue<int> nextIndexes;
		nextIndexes.push(m_StartIndex);
		while (!nextIndexes.empty())
		{
			int currentIndex = nextIndexes.front();
			nextIndexes.pop();
			if (m_Graph.at(currentIndex) == Utility::NodeStatus::VISITED)
			{
				continue;
			}
			else if (m_Graph.at(currentIndex) == Utility::NodeStatus::TARGET)
			{
				m_SearchFinished = true;
				break;
			}

			m_Graph.at(currentIndex) = Utility::NodeStatus::VISITED;
			m_VisitEvent(currentIndex);

			std::stack<int> adjacents = GetAdjacentIndexes(currentIndex);
			while (!adjacents.empty())
			{
				int currentAdjacent = adjacents.top();
				adjacents.pop();
				if (m_Graph.at(currentAdjacent) == Utility::NodeStatus::VISITED || m_Graph.at(currentAdjacent) == Utility::NodeStatus::LOOKED)
					continue;
				m_LookEvent(currentAdjacent);
				m_Graph.at(currentAdjacent) = Utility::NodeStatus::LOOKED;
				nextIndexes.emplace(currentAdjacent);
			}
		}
	}

	void BFS::Visit()
	{
	}

	void BFS::Look()
	{
	}


}
