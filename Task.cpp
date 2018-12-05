#include "Task.hpp"

Task::Task() :
	m_top(nullptr)
{
}

void Task::addSub(Task* task)
{
	task->m_top = this;
	m_sub_tasks.push_back(task);
}

const std::list<Task*>& Task::getSubs() const
{
	return m_sub_tasks;
}

void Task::setProgress(double p)
{
	m_progress = p;
	if (m_top)
		m_top->updateProgress();
}

void Task::updateProgress()
{
	double progress = 0.0;
	for (Task* t : m_sub_tasks)
	{
		progress += t->m_progress;
	}

	m_progress /= double(m_sub_tasks.size());
}
