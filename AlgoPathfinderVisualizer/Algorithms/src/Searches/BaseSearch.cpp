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
	BaseSearch::BaseSearch(const std::vector<Utility::NodeStatus>& graph, int startIndex, int targetIndex, const std::function<void(int)> visitFunction, const std::function<void(int)> lookFunction, uint8_t width, uint8_t height, bool iterative):
		m_Graph(graph), m_StartIndex(startIndex), m_TargetIndex(targetIndex), m_VisitEvent(visitFunction), m_LookEvent(lookFunction), m_Width(width), m_Height(height), m_IterativeSearch(iterative)
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
		

		LOG_MSG("[Base Search]: offset 1: %i, %i", currentIndex + m_Width, m_Width * m_Height)
		LOG_MSG("[Base Search]: offset 2: %i, %i", currentIndex - m_Width, 0)
		
		if (currentIndex + m_Width < m_Width * m_Height && m_Graph.at(currentIndex + m_Width) != Utility::NodeStatus::BLOCK)
			tempStack.push(currentIndex + m_Width);
		if (currentIndex - m_Width > 0 && m_Graph.at(currentIndex - m_Width) != Utility::NodeStatus::BLOCK)
			tempStack.push(currentIndex - m_Width);
		
		return tempStack;
	}
}