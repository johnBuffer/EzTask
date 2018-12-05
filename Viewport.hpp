#pragma once
#include <SFML/Graphics.hpp>

struct Viewport
{
	sf::Vector2f offset;
	sf::Vector2f dimension;
	double zoom;

	void addOffset(double x, double y);

	sf::Vector2f getViewportCoord(double x, double y) const;
	sf::Vector2f getRealCoord(double x, double y) const;
};