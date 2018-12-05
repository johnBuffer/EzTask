#pragma once
#include <list>

class Task
{
public:
	Task();

	void addSub(Task* task);

	const std::list<Task*>& getSubs() const;

	void setProgress(double p);

private:
	Task* m_top;
	std::list<Task*> m_sub_tasks;

	void updateProgress();

	float m_progress;
};