#include "Connector.hpp"

double sigm(double x)
{
	return 1 / (1 + exp(-x));
}

Connector::Connector(const GTask* gt1, const GTask* gt2) :
	m_task_1(gt1),
	m_task_2(gt2)
{
}

void Connector::draw(sf::RenderTarget* target, const Viewport& viewport) const
{
	sf::VertexArray va(sf::LinesStrip, quality);

	sf::Vector2f screen_pos_1 = viewport.getViewportCoord(m_task_1->pos.x, m_task_1->pos.y);
	sf::Vector2f screen_pos_2 = viewport.getViewportCoord(m_task_2->pos.x, m_task_2->pos.y + m_task_2->pos.h);

	double dx = screen_pos_1.x - screen_pos_2.x;
	double dy = screen_pos_1.y - screen_pos_2.y;

	for (uint32_t i(0); i < quality; ++i)
	{
		double y = 14*i/double(quality-1) - 7;

		double x = dx * sigm(y);

		va[i].position.x = screen_pos_1.x - x;
		va[i].position.y = screen_pos_1.y - (y + 7)/14.0*dy;
	}

	target->draw(va);
}
