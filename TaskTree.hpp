#pragma once

#include <SFML/Graphics.hpp>
#include "Task.hpp"
#include "TaskTreeRenderer.hpp"

class TaskTree
{
public:
	TaskTree();

	void draw(sf::RenderTarget* target) const;

	void update();

	void addTaskAt(const sf::Vector2i& coord);

	void addOffset(double x, double y);

	void zoom(double z);

private:
	std::list<Task> m_tasks;

	TaskTreeRenderer m_renderer;
};