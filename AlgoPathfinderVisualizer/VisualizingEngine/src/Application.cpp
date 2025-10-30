/*
*	Copyright (c) 2025 Vincent Pierce
* 
*	This file is part of AlgoPathfinderVisualizer.
*	Released under MIT License.
*	See License file at the directory root for more information.
*	
*/

#include "Application.h"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "Logger/Logger.h"

namespace VisualizingEngine
{
	Application::Application()
	{
		LOG_MSG("Application: Created!")
	}

	Application::~Application()
	{
		LOG_MSG("Application: Destroyed!\n")
	}

	void Application::init(const std::string& appTitle, const sf::Vector2u& windowDimensions, const GridSystem::Vector2& gridDimensions)
	{
		m_Window = std::make_shared<sf::RenderWindow>(sf::VideoMode(windowDimensions), appTitle);

		m_Grid = std::make_unique<GridSystem::Grid>(m_Window->getSize(), gridDimensions);

		const VisualizingEngine::GridSystem::Cell* startCell = m_Grid->GetStartCell();
		const VisualizingEngine::GridSystem::Cell* targetCell = m_Grid->GetTargetCell();

		//this is for the saved data template board setups
		if (startCell && targetCell)
			m_AlgoAPI = std::make_unique<Algorithms::Algorithms>(m_Grid->GetGraphMapData(), startCell->GetID(), targetCell->GetID(),
				[this](int idx) { m_Grid->VisitCell(idx); },
				[this](int idx) { m_Grid->LookCell(idx); },
				m_Grid->GetDimensions().y_, m_Grid->GetDimensions().x_);
		else
			m_AlgoAPI = std::make_unique<Algorithms::Algorithms>(m_Grid->GetGraphMapData(), 
				[this](int idx) { m_Grid->VisitCell(idx); },
				[this](int idx) { m_Grid->VisitCell(idx); },
				m_Grid->GetDimensions().y_, m_Grid->GetDimensions().x_);
	}

	void Application::Start()
	{
		m_Window->setVerticalSyncEnabled(true);
		m_Window->setFramerateLimit(60);

		Update();
	}

	void Application::Update()
	{
		while (m_Window.get()->isOpen())
		{
			while (const std::optional event = m_Window->pollEvent())
			{
				
				sf::Vector2i mousePosition = sf::Mouse::getPosition(*m_Window.get());
				
				if (event->is<sf::Event::Closed>())
				{
					m_Window->close();
				}
				else if (const auto* pressedKey = event->getIf<sf::Event::KeyPressed>())
				{
					//my own window restrictions
					if (mousePosition.x >= 0 && mousePosition.y >= 0 && mousePosition.x <= m_Window->getSize().x && mousePosition.y <= m_Window->getSize().y)
					{
						//previous positions are for updating the start and target graph locations in the algorithms
						if (pressedKey->scancode == sf::Keyboard::Scancode::Num1)
						{
							std::optional<int> previousPosition = -1;
							const int interactedIndex = m_Grid->InteractWithCell(mousePosition, GridSystem::Grid::InteractMethod::START_POINT, &previousPosition);
							m_AlgoAPI->UpdateGraphCell(interactedIndex, Algorithms::Utility::NodeStatus::START, previousPosition);
						}
						else if (pressedKey->scancode == sf::Keyboard::Scancode::Num2)
						{
							std::optional<int> previousPosition = -1;
							const int interactedIndex = m_Grid->InteractWithCell(mousePosition, GridSystem::Grid::InteractMethod::TARGET_POINT, &previousPosition);
							m_AlgoAPI->UpdateGraphCell(interactedIndex, Algorithms::Utility::NodeStatus::TARGET, previousPosition);
						}
						else if (pressedKey->scancode == sf::Keyboard::Scancode::Enter)
						{
							m_AlgoAPI->StartSearch();
						}
					}
				}
				else if (const auto* mb = event->getIf<sf::Event::MouseButtonPressed>())
				{
					//my own window constrictions since sfml doesnt provide solid ones for what I need
					if (mousePosition.x >= 0 && mousePosition.y >= 0 && mousePosition.x <= m_Window->getSize().x && mousePosition.y <= m_Window->getSize().y)
					{
						if (mb->button == sf::Mouse::Button::Left)
						{ 
							const int interactedIndex = m_Grid->InteractWithCell(mousePosition, GridSystem::Grid::InteractMethod::CREATE_WALL);
							m_AlgoAPI->UpdateGraphCell(interactedIndex, Algorithms::Utility::NodeStatus::BLOCK);
						}
						else if (mb->button == sf::Mouse::Button::Right)
						{
							int interactedIndex = m_Grid->InteractWithCell(mousePosition, GridSystem::Grid::InteractMethod::ERASE_WALL);
							m_AlgoAPI->UpdateGraphCell(interactedIndex, Algorithms::Utility::NodeStatus::AVAILABLE);
						}
					}
				}
			}
			
			Draw();
		}
	}

	void Application::Draw() const
	{
		sf::RenderWindow* window = m_Window.get();

		//grid and window should always be valid throughout entire lifetime of application
		if (!m_Grid.get() || !window) [[unlikely]]
			return;

		//clear first
		window->clear();

		m_Grid->Draw(m_Window.get());

		//display everything last
		window->display();
	}
}
