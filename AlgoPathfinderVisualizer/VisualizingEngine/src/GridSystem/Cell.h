/*
*	Copyright (c) 2025 Vincent Pierce
*
*	This file is part of AlgoPathfinderVisualizer.
*	Released under MIT License.
*	See License file at the directory root for more information.
*
*	Description:
*		Contains the individual cell squares for the grid system
*/

#ifndef CELL_H
#define CELL_H

#include <memory>
#include <cstdint>
#include <SFML/System/Vector2.hpp>


#include "Utillity/Enums.h"

namespace sf
{
	class RectangleShape;
	class RenderWindow;
}

namespace VisualizingEngine::GridSystem
{
	using CellShape = std::unique_ptr<sf::RectangleShape>;
	using CellState = Algorithms::Utility::NodeStatus;
	using CellDimensions = sf::Vector2f; //just want to abstract away sf::Vector2 since I am working with my own completely different Vector2 as well

	struct Vector2
	{
		uint8_t x_;
		uint8_t y_;

		Vector2() : x_(0), y_(0) {}
		Vector2(uint8_t x, uint8_t y): x_(x), y_(y) {}

		Vector2& operator=(const Vector2& other)
		{
			if (this == &other)
				return *this;

			x_ = other.x_;
			y_ = other.y_;

			return *this;
		}

		Vector2 operator+(const Vector2& otherPosition) const
		{
			return Vector2(x_ + otherPosition.x_, y_ + otherPosition.y_);
		}
		
		Vector2 operator-(const Vector2& otherPosition) const
		{
			return Vector2(x_ - otherPosition.x_, y_ - otherPosition.y_);
		}
	};

	//simple color struct to not have to heap allocate a forward declared sf::Color
	struct Color
	{
		uint8_t r_;
		uint8_t g_;
		uint8_t b_;
		
		Color() : r_(0), g_(0), b_(0) {}
		Color(uint8_t r, uint8_t g, uint8_t b) : r_(r), g_(g), b_(b) {}
	};


	class Cell
	{
	public:
		Cell();
		Cell(int id, Vector2 gridPosition, const sf::Vector2f& windowPosition);
		Cell(int id, Vector2 gridPosition, const sf::Vector2f& windowPosition, CellState state);
		~Cell();

		//api / getters / setters
		void SetGridPosition(const Vector2& newPosition) { m_GridPosition = newPosition; }
		void SetWindowPosition(const CellDimensions& newPosition) { m_WindowPosition = newPosition; }
		void SetState(CellState newState);

		Vector2 GetGridPosition() const { return m_GridPosition; }
		const CellDimensions& GetWindowPosition() const { return m_WindowPosition; }
		CellState GetState() const { return m_State; }
		int GetID() const { return m_ID; }
		
		//statics
		static CellDimensions GetSize() { return m_Size; }

		static inline void SetSize(const CellDimensions& newSize) { m_Size = newSize; }
		
		//border color is not included in the algo colors using the CellState
		//tuples are converted to sf::Colors under the hood
		static void SetBorderColor(const Color& newColor) { m_BorderColor = newColor; }
		static void SetAlgoColor(const CellState& state, const Color& newColor);
		
		//statics

		void Draw(sf::RenderWindow* window) const;

	private:
		static void SetDefaultColors();
		void AddOutline();

	private:
		int m_ID;
		Vector2 m_GridPosition;
		CellDimensions m_WindowPosition;
		CellShape m_Shape;
		CellState m_State = CellState::AVAILABLE;

		//all cells need the same structure and scheme
		static CellDimensions m_Size;
		static Color m_BorderColor;
		static Color m_NormalColor;
		static Color m_LookColor;
		static Color m_BlockColor;
		static Color m_VisitedColor;
		static Color m_StartColor;
		static Color m_TargetColor;
		static Color m_HoverColor;
	};
}

#endif