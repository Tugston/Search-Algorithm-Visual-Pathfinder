/*
*	Copyright (c) 2025 Vincent Pierce
*
*	This file is part of AlgoPathfinderVisualizer.
*	Released under MIT License.
*	See License file at the directory root for more information.
*
*	Description:
*		Base class for all the searches (helps the algorithm api)
*/
#ifndef ALGORITHM_BASE_SEARCH_PARENT
#define ALGORITHM_BASE_SEARCH_PARENT

#include <stack>
#include <vector>
#include <functional>
#include "Utillity/Enums.h"

namespace Algorithms
{
	class BaseSearch
	{
	public:
		BaseSearch(const std::vector<Utility::NodeStatus>& m_Graph, int startIndex, int targetIndex, const std::function<void(int)> visitFunction, const std::function<void(int)> lookFunction, uint8_t width, uint8_t height, bool iterative);
		~BaseSearch();

		virtual void IterativeSearch() = 0;
		virtual void RecursiveSearch() = 0;

		std::vector<Utility::NodeStatus>* GetGraph() { return &m_Graph; }

		void SetStartIndex(int index) { m_StartIndex = index; }
		void SetTargetIndex(int index) { m_TargetIndex = index; }

	protected:
		virtual void Visit() = 0;
		virtual void Look() = 0;

		//all returned indexes are valid 
		std::stack<int> GetAdjacentIndexes(int currentIndex);

		std::stack<int> m_PoppedIndexes;
		std::vector<Utility::NodeStatus> m_Graph;
		std::function<void(int)> m_VisitEvent;
		std::function<void(int)> m_LookEvent;
		int m_StartIndex;
		int m_TargetIndex;
		uint8_t m_Width;
		uint8_t m_Height;
		bool m_IterativeSearch;

	};
}

#endif