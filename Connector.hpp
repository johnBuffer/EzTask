#pragma once

#include <SFML/Graphics.hpp>
#include "GTask.hpp"

class Connector
{
public:
	Connector() = default;
	Connector(const GTask* gt1, const GTask* gt2);

	void draw(sf::RenderTarget* target, const Viewport& viewport) const;

private:
	const GTask* m_task_1;
	const GTask* m_task_2;

	const uint32_t quality = 32;
};
