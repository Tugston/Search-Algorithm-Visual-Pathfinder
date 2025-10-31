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
	DFS::DFS(const std::vector<Utility::NodeStatus>& m_Graph, int startIndex, int targetIndex, const std::function<void(int)> visitFunction, const std::function<void(int)> lookFunction, uint8_t width, uint8_t height, bool iterative):
		BaseSearch(m_Graph, startIndex, targetIndex, visitFunction, lookFunction, width, height, iterative)
	{

	}

	DFS::~DFS()
	{

	}

	void DFS::IterativeSearch()
	{

	}

	void DFS::RecursiveSearch()
	{
		m_PoppedIndexes.push(m_StartIndex);
		while(!m_PoppedIndexes.empty())
		{
			int currentIndex = m_PoppedIndexes.top();
			m_PoppedIndexes.pop();
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

				m_PoppedIndexes.push(currentNeighbor);
			}

			if (m_SearchFinished)
				break;
			
			std::this_thread::sleep_for(std::chrono::milliseconds(200));
		}

		//supposed to be size_t, but ints work with my macro
		for (int i = 0; i < m_Graph.size(); ++i)
		{
			if(m_Graph[i] == Utility::NodeStatus::AVAILABLE)
				LOG_MSG("[DFS]: %i, Available", i)
			else if(m_Graph[i] == Utility::NodeStatus::BLOCK)
				LOG_MSG("[DFS]: %i, Block", i)
			else if(m_Graph[i] == Utility::NodeStatus::LOOKED)
				LOG_MSG("[DFS]: %i, Look", i)
			else if(m_Graph[i] == Utility::NodeStatus::START)
				LOG_MSG("[DFS]: %i, Start", i)
			else if(m_Graph[i] == Utility::NodeStatus::TARGET)
				LOG_MSG("[DFS]: %i, Target", i)
			else if(m_Graph[i] == Utility::NodeStatus::VISITED)
				LOG_MSG("[DFS]: %i, Visited", i)

		
		}

	}

	void DFS::Visit()
	{

	}

	void DFS::Look()
	{

	}
}