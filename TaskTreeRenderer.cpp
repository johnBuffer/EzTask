#include "TaskTreeRenderer.hpp"

void TaskTreeRenderer::updateBboxes(const Task& task)
{
	m_bboxes.clear();
}

void TaskTreeRenderer::updateBbox(const Task& task, Context context)
{
	double x = context.bbox.x;
	double y = context.bbox.y;

	double width = context.bbox.w;
	double height = width / 2;

	m_bboxes.emplace_back();
	BboxAnim& current_bbox = m_bboxes.back();
	current_bbox.target.x = x;
	current_bbox.target.y = y;
	current_bbox.target.w = width;
	current_bbox.target.h = height;

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
	}
}
