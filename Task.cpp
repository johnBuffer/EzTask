#include "Task.hpp"

void Task::addSub(Task* task)
{
	m_sub_tasks.push_back(task);
}

const std::list<Task*>& Task::getSubs() const
{
	return m_sub_tasks;
}

void Task::setDone()
{
	m_progress = 1.0f;
}
