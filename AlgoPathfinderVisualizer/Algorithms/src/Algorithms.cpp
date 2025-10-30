/*
*	Copyright (c) 2025 Vincent Pierce
* 
*	This file is part of AlgoPathfinderVisualizer.
*	Released under MIT License.
*	See License file at the directory root for more information.
*	
*/

#include "Algorithms.h"

namespace Algorithms
{
	Algorithms::Algorithms(const std::vector<Utility::NodeStatus>& graph, const std::function<void(int)>& visitFunction, const std::function<void(int)>& lookFunction, uint8_t width, uint8_t height)
	{
		//0, 0 indexes wont be stored or displayed anywhere because the search prevents them from both being the same
		m_DFSSearch = std::make_unique<DFS>(graph, 0, 0, visitFunction, lookFunction, width, height, false);
	}

	Algorithms::Algorithms(const std::vector<Utility::NodeStatus>& graph, int startPosition, int endPosition, const std::function<void(int)>& visitFunction, const std::function<void(int)>& lookFunction, uint8_t width, uint8_t height)
	{
	}

	Algorithms::~Algorithms()
	{

	}

	void Algorithms::StartSearch()
	{
		if (m_DFSSearch)
			m_DFSSearch->RecursiveSearch();
	}

	void Algorithms::UpdateGraphCell(int position, Utility::NodeStatus newState, const std::optional<int> previousPosition)
	{
		if (position < 0) return;

		std::vector<Utility::NodeStatus>* searchGraph = m_DFSSearch->GetGraph();
		
		if (previousPosition.has_value() && previousPosition.value() != -1)
			searchGraph->at(previousPosition.value()) = Utility::NodeStatus::AVAILABLE; //optional previous position erasing
		
		searchGraph->at(position) = newState;

		if (newState == Utility::NodeStatus::START)
			m_DFSSearch->SetStartIndex(position);
		else if (newState == Utility::NodeStatus::TARGET)
			m_DFSSearch->SetTargetIndex(position);
	}
}
