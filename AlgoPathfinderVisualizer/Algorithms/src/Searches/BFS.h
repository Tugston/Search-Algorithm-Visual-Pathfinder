/*
*	Copyright (c) 2025 Vincent Pierce
*
*	This file is part of AlgoPathfinderVisualizer.
*	Released under MIT License.
*	See License file at the directory root for more information.
*
*	Description:
*		Bredth first search implementation, the underlying data is a 1d array represented as a 2d grid
*/
#ifndef ALGORITHM_BREADTH_FIRST_SEARCH
#define ALGORITHM_BREADTH_FIRST_SEARCH

#include "BaseSearch.h"

namespace Algorithms
{
	class BFS: public BaseSearch
	{
	public:
		BFS(const std::vector<Utility::NodeStatus>& m_Graph, int startIndex, int targetIndex, const std::function<void(int)> visitFunction, const std::function<void(int)> lookFunction, uint8_t width, uint8_t height);
		~BFS();

		virtual void IterativeSearch() override;

	protected:
		virtual void Visit() override;
		virtual void Look() override;
	};
}

#endif
