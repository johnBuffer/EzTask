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

	void addTaskTo(GTask* gtask);
	void addTaskAt(const sf::Vector2i& coord);
	Task* getTaskAt(const sf::Vector2i& coord);
	GTask* getGTaskAt(const sf::Vector2i& coord);

	void removeGTask(GTask* gtask);

	void addOffset(double x, double y);

	void zoom(double z);

private:
	std::list<Task> m_tasks;

	TaskTreeRenderer m_renderer;
};