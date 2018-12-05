#include "TaskTree.hpp"

TaskTree::TaskTree()
{
	m_tasks.emplace_back();
	m_renderer.generateGTree(m_tasks.front());
}

void TaskTree::draw(sf::RenderTarget* target) const
{
	m_renderer.draw(target);
}

void TaskTree::update()
{
	m_renderer.update();
}

void TaskTree::addTaskAt(const sf::Vector2i& coord)
{
	sf::Vector2f pos(coord.x, coord.y);
	GTask* gtask = m_renderer.getTaskAt(pos);

	if (gtask)
	{
		m_tasks.emplace_back();
		gtask->task->addSub(&m_tasks.back());

		m_renderer.addSubTask(m_tasks.back(), gtask);
	}
}

void TaskTree::addOffset(double x, double y)
{
	m_renderer.addOffset(x, y);
}

void TaskTree::zoom(double z)
{
	m_renderer.zoom(z);
}
