/*
*	Copyright (c) 2025 Vincent Pierce
*
*	This file is part of AlgoPathfinderVisualizer.
*	Released under MIT License.
*	See License file at the directory root for more information.
*
*/
#include "DFS.h"
#include "../../VisualizingEngine/src/Logger/Logger.h"
#include<chrono>
#include<thread>

namespace Algorithms
{
	DFS::DFS(const std::vector<Utility::NodeStatus>& m_Graph, int startIndex, int targetIndex, const std::function<void(int)> visitFunction, const std::function<void(int)> lookFunction, uint8_t width, uint8_t height):
		BaseSearch(m_Graph, startIndex, targetIndex, visitFunction, lookFunction, width, height)
	{

	}

	DFS::~DFS()
	{

	}

	void DFS::IterativeSearch()
	{
		std::stack<int> poppedIndexes;
		poppedIndexes.push(m_StartIndex);
		while(!poppedIndexes.empty())
		{
			int currentIndex = poppedIndexes.top();
			poppedIndexes.pop();
			if (m_Graph.at(currentIndex) == Utility::NodeStatus::VISITED)
				continue;

			m_VisitEvent(currentIndex);
			m_Graph.at(currentIndex) = Utility::NodeStatus::VISITED;

			std::stack<int> neighbors = GetAdjacentIndexes(currentIndex);
			while (!neighbors.empty())
			{
				int currentNeighbor = neighbors.top();
				neighbors.pop();
				
				if (m_Graph.at(currentNeighbor) == Utility::NodeStatus::VISITED || m_Graph.at(currentNeighbor) == Utility::NodeStatus::LOOKED)
				{
					continue;
				}
				else if (m_Graph.at(currentNeighbor) == Utility::NodeStatus::TARGET)
				{
					m_SearchFinished = true;
					break;
				}

				m_Graph.at(currentNeighbor) = Utility::NodeStatus::LOOKED;
				m_LookEvent(currentNeighbor);

				poppedIndexes.push(currentNeighbor);
			}

			if (m_SearchFinished)
				break;
			
			std::this_thread::sleep_for(std::chrono::milliseconds(200));
		}
	}

	void DFS::Visit()
	{

	}

	void DFS::Look()
	{

	}

}