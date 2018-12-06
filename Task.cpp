#include "Task.hpp"

Task::Task() :
	m_top(nullptr),
	m_progress(0.0f)
{
}

void Task::addSub(Task* task)
{
	task->m_top = this;
	m_sub_tasks.push_back(task);
	updateProgress();
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

float Task::getProgress() const
{
	return m_progress;
}

void Task::updateProgress()
{
	double progress = 0.0;
	for (Task* t : m_sub_tasks)
	{
		progress += t->m_progress;
	}

	progress /= double(m_sub_tasks.size());

	setProgress(progress);
}
