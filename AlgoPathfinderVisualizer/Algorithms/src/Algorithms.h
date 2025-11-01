/*
*	Copyright (c) 2025 Vincent Pierce
*
*	This file is part of AlgoPathfinderVisualizer.
*	Released under MIT License.
*	See License file at the directory root for more information.
*
*	Description:
*		public api interface for controlling the search algorithms
*/
#ifndef SEARCH_ALGORITHMS_H
#define SEARCH_ALGORITHMS_H

#include <utility>
#include <optional>
#include <memory>

#include "Searches/DFS.h"
#include "Searches/BFS.h"


namespace Algorithms
{

	class Algorithms
	{
	public:
		Algorithms(const std::vector<Utility::NodeStatus>& graph, const std::function<void(int)>& visitFunction, const std::function<void(int)>& lookFunction, uint8_t width, uint8_t height);
		Algorithms(const std::vector<Utility::NodeStatus>& graph, int startPosition, int endPosition, const std::function<void(int)>& visitFunction, const std::function<void(int)>& lookFunction, uint8_t width, uint8_t height);
		~Algorithms();

		void StartSearch();

		void UpdateGraphCell(int position, Utility::NodeStatus newState, const std::optional<int> previousPosition = std::nullopt);

	private:
		std::unique_ptr<BaseSearch> m_DFSSearch;
		std::unique_ptr<BaseSearch> m_BFSSearch;
	};
}

#endif