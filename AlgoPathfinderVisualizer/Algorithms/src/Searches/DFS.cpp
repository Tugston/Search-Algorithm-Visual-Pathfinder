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
		std::stack<int> neighbors = GetAdjacentIndexes(m_StartIndex);
		int index = 0;
		while(!neighbors.empty())
		{
			int visited = neighbors.top();
			neighbors.pop();
			index++;
			m_LookEvent(visited);
			m_Graph.at(visited) = Utility::NodeStatus::VISITED;
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