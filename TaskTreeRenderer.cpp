#include "TaskTreeRenderer.hpp"

void TaskTreeRenderer::generateGTree(const Task& root_task)
{
	m_bboxes.clear();

	addToGTree(root_task, nullptr);
}

void TaskTreeRenderer::updateBboxes(const Task& task)
{
	m_bboxes.clear();
}

void TaskTreeRenderer::updateBbox(const Task& task, Context context)
{
	/*double x = context.bbox.x;
	double y = context.bbox.y;

	double width = context.bbox.w;
	double height = width / 2;

	m_bboxes.emplace_back();
	GTask& current_gtask = m_bboxes.back();
	current_gtask.task = &task;

	current_gtask.target.x = x;
	current_gtask.target.y = y;
	current_gtask.target.w = width;
	current_gtask.target.h = height;

	std::list<Task*> subs = task.getSubs();
	if (!subs.empty())
	{
		// Compute start of coord to draw subs
		double sub_start = x - _sub_width / 2;
		for (const Task* t : subs)
		{
			Context sub_context;
			sub_context.level = context.level + 1;
			sub_context.bbox.x = sub_start + t->_width / 2;
			sub_context.bbox.y = y + height + v_padding;
			t->updateGeometry(sub_context);

			sub_start += t->_width + h_padding;
		}
	}*/
}
void TaskTreeRenderer::addToGTree(const Task& task, GTask* super)
{
	// Create new GTask
	m_bboxes.emplace_back();
	GTask& current_gtask = m_bboxes.back();
	if (super)
	{
		super->sub_tasks.push_back(&current_gtask);
	}

	// Add subs
	std::list<Task*> subs = task.getSubs();
	if (!subs.empty())
	{
		// Compute start of coord to draw subs
		for (const Task* t : subs)
		{

		}
	}
}

void TaskTreeRenderer::computeWidth(GTask& task, uint32_t level)
{

}
