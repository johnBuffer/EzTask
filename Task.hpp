#pragma once
#include <list>

class Task
{
public:
	Task() = default;

	const std::list<Task*>& getSubs() const;

private:
	std::list<Task*> m_sub_tasks;
};