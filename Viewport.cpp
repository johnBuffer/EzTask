#include "Viewport.hpp"

void Viewport::addOffset(double x, double y)
{
	offset.x += x / zoom;
	offset.y += y / zoom;
}

sf::Vector2f Viewport::getViewportCoord(double x, double y) const
{
	double o_x = (x - offset.x) * zoom;
	double o_y = (y - offset.y) * zoom;

	double vp_x = o_x + dimension.x * 0.5;
	double vp_y = o_y + dimension.y * 0.5;

	return sf::Vector2f(vp_x, vp_y);
}

sf::Vector2f Viewport::getRealCoord(double x, double y) const
{
	double x_1 = x - dimension.x * 0.5;
	double y_1 = y - dimension.y * 0.5;

	double r_x = x_1 / zoom + offset.x;
	double r_y = y_1 / zoom + offset.y;

	return sf::Vector2f(r_x, r_y);
}
