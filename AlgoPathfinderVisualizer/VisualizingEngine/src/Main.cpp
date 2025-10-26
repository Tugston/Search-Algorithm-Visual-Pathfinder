/*
*	Copyright (c) 2025 Vincent Pierce
*
*	This file is part of AlgoPathfinderVisualizer.
*	Released under MIT License.
*	See License file at the directory root for more information.
*
*	Description:
*		Entry Point for the application
*/

#include "Application.h"


int main(int argc, char* argv[])
{
	VisualizingEngine::Application* app = &VisualizingEngine::Application::GetApplication();
	app->init("Visualization Engine", { 800, 800 }, { 7, 7 });
	app->Start();
	app->Update();
	return 0;
}