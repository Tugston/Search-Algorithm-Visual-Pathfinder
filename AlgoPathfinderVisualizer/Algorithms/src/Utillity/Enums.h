/*
*	Copyright (c) 2025 Vincent Pierce
*	All rights reserved
* 
*	Description:
*		provides all needed enums for this algorithm project and derived projects
*/
#ifndef ALGO_UTIL_ENUMS
#define ALGO_UTIL_ENUMS

#include <cstdint>

namespace Algorithms::Utility
{
	//obvious name, but controls the status of each node in node based searches
	//Available - Algo hasn't been there at all
	//Looked - Algo has checked, but decided not to visit
	//Visited - Algo fully visited the node
	//Block - Algo is blocked from going to this node
	enum class NodeStatus : uint8_t
	{
		AVAILABLE = 0,
		LOOKED,
		VISITED,
		BLOCK,
		START,
		TARGET
	};
}

#endif
