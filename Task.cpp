#include "Task.hpp"

const std::list<Task*>& Task::getSubs() const
{
	return m_sub_tasks;
}
