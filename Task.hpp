#pragma once
#include <list>

class Task
{
public:
	Task() = default;

	void addSub(Task* task);

	const std::list<Task*>& getSubs() const;

	void setDone();

private:
	std::list<Task*> m_sub_tasks;

	float m_progress;
};