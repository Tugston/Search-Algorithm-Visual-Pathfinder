/*
*	Copyright (c) 2025 Vincent Pierce
*
*	This file is part of AlgoPathfinderVisualizer.
*	Released under MIT License.
*	See License file at the directory root for more information.
*
*	Description:
*		Depth first search generic search implementation, both approaches are designed for a 1d array representing a 2d grid
*/

#include "BaseSearch.h"

namespace Algorithms
{
	class DFS : public BaseSearch
	{
	public:
		DFS(const std::vector<Utility::NodeStatus>& m_Graph, int startIndex, int targetIndex, const std::function<void(int)> visitFunction, const std::function<void(int)> lookFunction, uint8_t width, uint8_t height, bool iterative);
		~DFS();

		virtual void IterativeSearch() override;
		virtual void RecursiveSearch() override;

	protected:
		virtual void Visit() override;
		virtual void Look() override;
	};
}