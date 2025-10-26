/*
*	Copyright (c) 2025 Vincent Pierce
* 
*	This file is part of AlgoPathfinderVisualizer.
*	Released under MIT License.
*	See License file at the directory root for more information.
*	
*	Description:
*		Controls the grid for visualizing various search algorithms 
*/
#ifndef GRID_H
#define GRID_H

#include "Cell.h"
#include <vector>

namespace VisualizingEngine::GridSystem
{
	class Grid
	{
	public:
		Grid(const sf::Vector2u& windowSize, const Vector2& dimensions);
		~Grid();

		enum class InteractMethod : uint8_t
		{
			CREATE_WALL = 0,
			ERASE_WALL,
			START_POINT,
			TARGET_POINT
		};

		//set all of these to be one function is what I am current working on
		void InteractWithCell(const sf::Vector2i& mousePosition, InteractMethod method);

		void Draw(sf::RenderWindow* window);

	protected:
		bool InitializeCells();
		bool CalculateCellSizes(const sf::Vector2u& windowSize) const;

		Cell* GetInteractedCell(const sf::Vector2i& mousePosition);
		Vector2 MousePositionToGridPosition(const sf::Vector2i& mousePosition);

	private:
		Vector2 m_Dimensions;
		std::vector<std::unique_ptr<Cell>> m_Cells;
		Cell* m_TargetCell;
		Cell* m_StartCell;
		sf::Vector2u m_WindowSize;

		//controls how small the window can be to allow the program to work
		//not passing it as member, because it doesnt really matter too much
		float m_MinWindowSize = 50.f;
	};
}

#endif