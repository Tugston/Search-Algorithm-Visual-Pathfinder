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

		m_Grid = std::make_unique<GridSystem::Grid>(m_Window.get()->getSize(), gridDimensions);
	}

	void Application::Start()
	{
		m_Window.get()->setVerticalSyncEnabled(true);
		m_Window.get()->setFramerateLimit(60);

		Update();
	}

	void Application::Update()
	{
		while (m_Window.get()->isOpen())
		{
			while (const std::optional event = m_Window.get()->pollEvent())
			{
				if (event->is<sf::Event::Closed>())
					m_Window.get()->close();

				sf::Vector2i mousePosition = sf::Mouse::getPosition(*m_Window.get());
				
				//my own window constrictions since sfml doesnt provide solid ones for what I need
				if (mousePosition.x >= 0 && mousePosition.y >= 0 && mousePosition.x <= m_Window.get()->getSize().x && mousePosition.y <= m_Window.get()->getSize().y)
				{
					if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
						m_Grid->InteractWithCell(mousePosition, GridSystem::Grid::InteractMethod::CREATE_WALL);
					else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
						m_Grid->InteractWithCell(mousePosition, GridSystem::Grid::InteractMethod::ERASE_WALL);
					else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
						m_Grid->InteractWithCell(mousePosition, GridSystem::Grid::InteractMethod::START_POINT);
					else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
						m_Grid->InteractWithCell(mousePosition, GridSystem::Grid::InteractMethod::TARGET_POINT);
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

		m_Grid.get()->Draw(m_Window.get());

		//display everything last
		window->display();
	}
}
