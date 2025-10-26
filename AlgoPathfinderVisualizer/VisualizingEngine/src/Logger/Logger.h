/*
*	Copyright (c) 2025 Vincent Pierce
* 
*	This file is part of AlgoPathfinderVisualizer.
*	Released under MIT License.
*	See License file at the directory root for more information.
*	
*	Description:
*		Very basic logging macro 
*/

#ifdef _DEBUG
#include<cstdio>
#define LOG_MSG(x, ...) std::printf("[DEBUG] " x "\n", ##__VA_ARGS__);
#else
#define LOG_MSG(x, ...) ((void)0);
#endif
	
	
