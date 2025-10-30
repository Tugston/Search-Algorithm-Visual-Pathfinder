/*
*	Copyright (c) 2025 Vincent Pierce
*
*	This file is part of AlgoPathfinderVisualizer.
*	Released under MIT License.
*	See License file at the directory root for more information.
* 
*/

#include "Cell.h"
#include <SFML/Graphics.hpp>
#include "../Logger/Logger.h"

namespace VisualizingEngine::GridSystem
{
	//static definitions
	CellDimensions VisualizingEngine::GridSystem::Cell::m_Size{ 0.f,0.f };
	Color VisualizingEngine::GridSystem::Cell::m_NormalColor{ 0,0,0 };
	Color VisualizingEngine::GridSystem::Cell::m_LookColor{ 0,0,0 };
	Color VisualizingEngine::GridSystem::Cell::m_VisitedColor{ 0,0,0 };
	Color VisualizingEngine::GridSystem::Cell::m_BlockColor{ 0,0,0 };
	Color VisualizingEngine::GridSystem::Cell::m_BorderColor{ 0,0,0 };
	Color VisualizingEngine::GridSystem::Cell::m_StartColor{ 0,0,0 };
	Color VisualizingEngine::GridSystem::Cell::m_TargetColor{ 0,0,0 };
	Color VisualizingEngine::GridSystem::Cell::m_HoverColor{ 0,0,0 };

	//utilizing the function calls rahter than initial list for the state
	//because SetState handles color change as well
	Cell::Cell() :
		m_ID(-1), m_GridPosition(), m_WindowPosition(), m_Shape(std::make_unique<sf::RectangleShape>())
	{
		//static values need to be set inside constructors
		SetDefaultColors();

		SetState(CellState::AVAILABLE);
		AddOutline();
	}

	Cell::Cell(int id, Vector2 gridPosition, const sf::Vector2f& windowPosition) :
		m_ID(id), m_GridPosition(gridPosition), m_WindowPosition(windowPosition)
	{
		SetDefaultColors();

		m_Shape = std::make_unique<sf::RectangleShape>();

		m_Shape.get()->setSize(m_Size);
		m_Shape.get()->setPosition(m_WindowPosition);

		SetState(CellState::AVAILABLE);
		AddOutline();
	}

	Cell::Cell(int id, Vector2 gridPosition, const sf::Vector2f& windowPosition, CellState state) :
		m_ID(id), m_GridPosition(gridPosition), m_WindowPosition(windowPosition)
	{
		SetDefaultColors();
		SetState(state);
		AddOutline();
	}

	Cell::~Cell()
	{
		LOG_MSG("Cell: %i Destroyed", m_ID)
	}

	void Cell::SetState(CellState newState)
	{
		//application should never destroy cells
		if (!m_Shape.get()) [[unlikely]]
			return;

		m_State = newState;

		auto changeColor = [=](sf::Color color)
			{
				m_Shape->setFillColor(color);
			};

		switch (m_State)
		{
		case CellState::AVAILABLE:
			m_Shape->setFillColor(sf::Color(m_NormalColor.r_, m_NormalColor.g_, m_NormalColor.b_));
			break;
		case CellState::LOOKED:
			m_Shape->setFillColor(sf::Color(m_LookColor.r_, m_LookColor.g_, m_LookColor.b_));
			break;
		case CellState::BLOCK:
			m_Shape->setFillColor(sf::Color(m_BlockColor.r_, m_BlockColor.g_, m_LookColor.b_));
			break;
		case CellState::VISITED:
			m_Shape->setFillColor(sf::Color(m_VisitedColor.r_, m_VisitedColor.g_, m_VisitedColor.b_));
			break;
		case CellState::START:
			m_Shape->setFillColor(sf::Color(m_StartColor.r_, m_StartColor.g_, m_StartColor.b_));
			break;
		case CellState::TARGET:
			m_Shape->setFillColor(sf::Color(m_TargetColor.r_, m_TargetColor.g_, m_TargetColor.b_));
			break;
		default:
			m_Shape->setFillColor(sf::Color(0, 255, 0)); //obvious error color
			break;
		}
	}

	void GridSystem::Cell::SetDefaultColors()
	{
		m_BorderColor = { 0, 0, 0 };
		m_NormalColor = { 255, 255, 255 };
		m_LookColor = { 155, 155, 155 };
		m_BlockColor = { 25, 25, 25 };
		m_VisitedColor = { 175, 0, 0 };
		m_TargetColor = { 0, 175, 0 };
		m_StartColor = { 137, 207, 240 };
	}

	void Cell::AddOutline()
	{
		m_Shape->setOutlineColor(sf::Color(m_BorderColor.r_, m_BorderColor.g_, m_BorderColor.b_));
		m_Shape->setOutlineThickness(1.f);
	}

	//oversophisticated set color function to avoid a long api for the class
	void GridSystem::Cell::SetAlgoColor(const CellState& state, const Color& newColor)
	{
		switch (state)
		{
		case CellState::AVAILABLE:
			m_NormalColor = newColor;
			break;
		case CellState::LOOKED:
			m_LookColor = newColor;
			break;
		case CellState::VISITED:
			m_VisitedColor = newColor;
			break;
		case CellState::BLOCK:
			m_BlockColor = newColor;
			break;
		default:
			m_NormalColor = newColor;
			break;
		}
	}

	void Cell::Draw(sf::RenderWindow* window) const
	{
		if (m_Shape.get()) [[likely]]
			window->draw(*m_Shape.get());
	}
}
