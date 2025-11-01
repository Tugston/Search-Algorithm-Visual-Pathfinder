/*
*	Copyright (c) 2025 Vincent Pierce
*
*	This file is part of AlgoPathfinderVisualizer.
*	Released under MIT License.
*	See License file at the directory root for more information.
*
*/
#include "BaseSearch.h"
#include "../../VisualizingEngine/src/Logger/Logger.h"

namespace Algorithms
{
	BaseSearch::BaseSearch(const std::vector<Utility::NodeStatus>& graph, int startIndex, int targetIndex, const std::function<void(int)> visitFunction, const std::function<void(int)> lookFunction, uint8_t width, uint8_t height):
		m_Graph(graph), m_StartIndex(startIndex), m_TargetIndex(targetIndex), m_VisitEvent(visitFunction), m_LookEvent(lookFunction), m_Width(width), m_Height(height)
	{
		if (startIndex != targetIndex)
		{
			m_Graph.at(startIndex) = Utility::NodeStatus::START;
			m_Graph.at(targetIndex) = Utility::NodeStatus::TARGET;
		}
	}

	BaseSearch::~BaseSearch()
	{
		m_Graph.clear();
	}

	std::stack<int> BaseSearch::GetAdjacentIndexes(int currentIndex)
	{
		std::stack<int> tempStack;
		

		LOG_MSG("[Base Search]: Top: %i, %i", currentIndex - m_Width, 0)
		LOG_MSG("[Base Search]: Right: %i, %i", (currentIndex + 1) % m_Width, 0)
		LOG_MSG("[Base Search]: Bottom: %i, %i", currentIndex + m_Width, m_Width * m_Height)
		LOG_MSG("[Base Search]: Left: %i, %i\n", (currentIndex - 1) % m_Width, 0)
	

		if (currentIndex - m_Width > 0 && m_Graph.at(currentIndex - m_Width) != Utility::NodeStatus::BLOCK) //top
			tempStack.push(currentIndex - m_Width);
		if ((currentIndex + 1) % m_Width != 0 && m_Graph.at(currentIndex + 1) != Utility::NodeStatus::BLOCK) //right
			tempStack.push(currentIndex + 1);
		if (currentIndex + m_Width < m_Width * m_Height && m_Graph.at(currentIndex + m_Width) != Utility::NodeStatus::BLOCK) //bottom
			tempStack.push(currentIndex + m_Width);
		if ((currentIndex - 1) % m_Width != m_Width - 1 && (currentIndex - 1) % m_Width != -1 && m_Graph.at(currentIndex - 1) != Utility::NodeStatus::BLOCK) //left
			tempStack.push(currentIndex - 1);
		
		return tempStack;
	}
}