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

void TaskTree::addTaskTo(GTask* gtask)
{
	m_tasks.emplace_back();
	gtask->task->addSub(&m_tasks.back());

	m_renderer.addSubTask(m_tasks.back(), gtask);
}

void TaskTree::addTaskAt(const sf::Vector2i& coord)
{
	GTask* gtask = getGTaskAt(coord);

	if (gtask)
	{
		m_tasks.emplace_back();
		gtask->task->addSub(&m_tasks.back());

		m_renderer.addSubTask(m_tasks.back(), gtask);
	}
}

Task* TaskTree::getTaskAt(const sf::Vector2i& coord)
{
	GTask* gtask = getGTaskAt(coord);

	if (gtask)
		return gtask->task;

	return nullptr;
}

GTask * TaskTree::getGTaskAt(const sf::Vector2i & coord)
{
	sf::Vector2f pos(coord.x, coord.y);
	GTask* gtask = m_renderer.getTaskAt(pos);

	return gtask;
}

void TaskTree::removeGTask(GTask* gtask)
{
	Task* tsk = gtask->task;
	m_tasks.remove_if([=](Task& t) {return &t == tsk; });
	m_renderer.remove(gtask);
}

void TaskTree::addOffset(double x, double y)
{
	m_renderer.addOffset(x, y);
}

void TaskTree::zoom(double z)
{
	m_renderer.zoom(z);
}
