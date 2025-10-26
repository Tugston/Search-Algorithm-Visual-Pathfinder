/*
*	Copyright (c) 2025 Vincent Pierce
* 
*	This file is part of AlgoPathfinderVisualizer.
*	Released under MIT License.
*	See License file at the directory root for more information.
*	
*/
#include "Grid.h"
#include <iostream>
#include <exception>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "../Logger/Logger.h"

namespace VisualizingEngine::GridSystem
{
	Grid::Grid(const sf::Vector2u& windowSize, const Vector2& dimensions):
		m_WindowSize(windowSize), m_Dimensions(dimensions), m_TargetCell(nullptr), m_StartCell(nullptr)
	{
		LOG_MSG("Grid: Starting Initialization...")
		try
		{
			//cell sizes must be calculated before initializing cells!
			if (CalculateCellSizes(windowSize))
				LOG_MSG("Grid: Cell Sizes Calculated!")
			else
				throw std::invalid_argument("Grid: Shared Window Is Too Small For Application To Be Effective!");
			
			if (InitializeCells())
				LOG_MSG("Grid: Cells Successfully Initialized!")
			else
				throw std::domain_error("Grid: Cell Area Must Be Greater Than 0!");

		}
		catch (const std::exception& exception)
		{
			LOG_MSG("Grid: Initialization Failed!")
			std::cerr << exception.what();
		}
	}

	GridSystem::Grid::~Grid()
	{
		m_Cells.clear();
		m_Cells.shrink_to_fit();
	}

	void GridSystem::Grid::InteractWithCell(const sf::Vector2i& mousePosition, InteractMethod method)
	{
		Cell* interactCell = GetInteractedCell(mousePosition);
		if (!interactCell) [[unlikely]]
		{
			LOG_MSG("Grid: Interacted Cell Not Valid!")
			return;
		}

		auto UpdateInteractedCell = [=](CellState state)
			{
				interactCell->SetState(state);
				Vector2 gridPosition = interactCell->GetGridPosition();
				LOG_MSG("Grid: <Cell %i> Grid Location - %i, %i updated", interactCell->GetID(), gridPosition.x_, gridPosition.y_)
			};

		switch (method)
		{
		//dont override the target and start cells when placing and removing walls
		case InteractMethod::CREATE_WALL:
			if (interactCell->GetState() == CellState::TARGET || interactCell->GetState() == CellState::START)
				break;
			UpdateInteractedCell(CellState::BLOCK);
			break;
		case InteractMethod::ERASE_WALL:
			if (interactCell->GetState() == CellState::TARGET || interactCell->GetState() == CellState::START)
				break;
			UpdateInteractedCell(CellState::AVAILABLE);
			break;
		case InteractMethod::START_POINT:
			//start point should only be allowed to be on available cells
			if (interactCell->GetState() == CellState::BLOCK || interactCell->GetState() == CellState::TARGET || interactCell->GetState() == CellState::START)
				break;

			if (m_StartCell)
				m_StartCell->SetState(CellState::AVAILABLE);

			m_StartCell = interactCell;
			UpdateInteractedCell(CellState::START);
			break;
		case InteractMethod::TARGET_POINT:
			//end point only available on empty cells
			if (interactCell->GetState() == CellState::BLOCK || interactCell->GetState() == CellState::START || interactCell->GetState() == CellState::TARGET)
				break;

			if (m_TargetCell)
				m_TargetCell->SetState(CellState::AVAILABLE);

			m_TargetCell = interactCell;
			UpdateInteractedCell(CellState::TARGET);
			break;
		default:
			LOG_MSG("GRID: Interact Method Invalid!")
			break;
		}
	}

	void Grid::Draw(sf::RenderWindow* window)
	{
		for (const auto& cell : m_Cells)
			cell.get()->Draw(window);
	}

	bool Grid::InitializeCells()
	{
		int cellArea = m_Dimensions.x_ * m_Dimensions.y_;
		if (cellArea <= 0)
			return false;

		m_Cells.reserve(cellArea);

		Vector2 currentGridPosition{0, 0};
		sf::Vector2f currentScreenPosition{0, 0};

		//1d vector cell placement algorithm
		//skip the static class... I guess? idk, its weird when not doing =1 or <=
		for (unsigned short i = 1; i <= cellArea; i++)
		{
			m_Cells.push_back(std::make_unique<Cell>(i + 1, currentGridPosition, currentScreenPosition));
			
			if (i % m_Dimensions.x_ == 0)
			{
				currentGridPosition.y_ += 1;
				currentGridPosition.x_ = 0;

				currentScreenPosition.y += Cell::GetSize().y;
				currentScreenPosition.x = 0.f;
			}
			else
			{
				currentGridPosition.x_++;
				currentScreenPosition.x += Cell::GetSize().x;
			}
		}

		return true;
	}

	//this honestly doesnt need to be a function
	//I had to refactor some stuff that removed some weak_ptr stuff from this function
	//so figured I would just leave it and add the windowsize check
	bool Grid::CalculateCellSizes(const sf::Vector2u& windowSize) const
	{
		if (windowSize.x < m_MinWindowSize || windowSize.y < m_MinWindowSize)
			return false;

		Cell::SetSize(CellDimensions(windowSize.x / m_Dimensions.x_, windowSize.y / m_Dimensions.y_));
		return true;
	}

	Cell* GridSystem::Grid::GetInteractedCell(const sf::Vector2i& mousePosition)
	{
		Vector2 clickedCellPosition = MousePositionToGridPosition(mousePosition);
		LOG_MSG("Clicked Cell Grid Position: %i, %i", clickedCellPosition.x_, clickedCellPosition.y_);

		//since using a 1d vector, can get 1d index from 2d position
		int index = (clickedCellPosition.x_ * m_Dimensions.y_) + clickedCellPosition.y_;
		return m_Cells.at(index).get();
	}

	Vector2 GridSystem::Grid::MousePositionToGridPosition(const sf::Vector2i& mousePosition)
	{
		uint8_t x = mousePosition.x / Cell::GetSize().x;
		uint8_t y = mousePosition.y / Cell::GetSize().y;
		return Vector2{y, x};
	}
}
