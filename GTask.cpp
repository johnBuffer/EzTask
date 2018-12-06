#include "GTask.hpp"
#include "Connector.hpp"

void GTask::draw(sf::RenderTarget* target, const Viewport& viewport) const
{
	double box_width = pos.w * viewport.zoom;
	double box_height = pos.h * viewport.zoom;

	sf::Vector2f screen_pos = viewport.getViewportCoord(pos.x, pos.y);
	double x = screen_pos.x - box_width * 0.5;
	double y = screen_pos.y;

	sf::RectangleShape box(sf::Vector2f(box_width, box_height));
	box.setOrigin(box_width * 0.5, 0);
	box.setPosition(screen_pos);

	target->draw(box);

	sf::RectangleShape header(sf::Vector2f(box_width, box_height * 0.25));
	header.setPosition(x, y);

	double p = progress;
	header.setFillColor(sf::Color(255*(1-p), 255*p, 0));

	target->draw(header);

	for (const GTask* gt : sub_tasks)
	{
		Connector c(gt, this);
		c.draw(target, viewport);
	}
}
