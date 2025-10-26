/*
*	Copyright (c) 2025 Vincent Pierce
* 
*	This file is part of AlgoPathfinderVisualizer.
*	Released under MIT License.
*	See License file at the directory root for more information.
*	
*	Description:
*		Main application class for the visualization engine
*/

#ifndef APPLICATION_H
#define APPLICATION_H

#include "GridSystem/Grid.h"
#include <string>

namespace VisualizingEngine
{
	class Application
	{
	public:
		~Application();

		//sfml window requires a string ref, otherwise would use a string_view like glfw
		void init(const std::string& appTitle, const sf::Vector2u& windowDimensions, const GridSystem::Vector2& gridDimensions);

		static Application& GetApplication()
		{
			static Application instance;
			return instance;
		}

		void Start();
		void Update();

	protected:
		void Draw() const;

		std::unique_ptr<GridSystem::Grid> m_Grid;
		std::shared_ptr<sf::RenderWindow> m_Window;

	private:
		Application();
		Application(const Application&) = delete;
		Application& operator=(const Application&) = delete;
	};
}

#endif