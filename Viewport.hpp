#pragma once
#include <SFML/Graphics.hpp>

struct Viewport
{
	sf::Vector2<double> offset;
	sf::Vector2<double> dimension;
	double zoom;

	void addOffset(double x, double y);

	sf::Vector2f getViewportCoord(double x, double y) const;
	sf::Vector2<double> getRealCoord(double x, double y) const;
};