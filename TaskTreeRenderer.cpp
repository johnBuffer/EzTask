#include "TaskTreeRenderer.hpp"
#include <iostream>

TaskTreeRenderer::TaskTreeRenderer() :
	m_padding(100, 500)
{
	m_viewport.zoom = 1.0;
	m_viewport.offset = { 0.0, 0.0 };
	m_viewport.dimension = { 1000.0, 1000.0 };
}

void TaskTreeRenderer::update()
{
	const double speed = 0.25;
	for (GTask& task : m_bboxes)
	{
		task.pos.x += (task.target.x - task.pos.x) * speed;
		task.pos.y += (task.target.y - task.pos.y) * speed;

		task.progress += (task.task->getProgress() - task.progress) * speed * 0.5f;
	}
}

void TaskTreeRenderer::generateGTree(Task& root_task)
{
	m_bboxes.clear();

	addToGTree(root_task, nullptr);
	
	updateBboxes();
}

void TaskTreeRenderer::updateBboxes()
{
	computeWidth(m_bboxes.front(), 0);

	Context root_context;
	root_context.bbox.x = 0;
	root_context.bbox.y = -300;
	root_context.level = 0;

	updateBbox(m_bboxes.front(), root_context);
}

void TaskTreeRenderer::addSubTask(Task& task, GTask* gtask)
{
	addToGTree(task, gtask);
	updateBboxes();
}

GTask* TaskTreeRenderer::getTaskAt(const sf::Vector2f& coord)
{
	sf::Vector2<double> r_coord = m_viewport.getRealCoord(coord.x, coord.y);
	for (GTask& t : m_bboxes)
	{
		double lx = t.pos.x - t.pos.w / 2;
		double ux = t.pos.x + t.pos.w / 2;

		double ly = t.pos.y;
		double uy = t.pos.y + t.pos.h;

		if (r_coord.x > lx && r_coord.x < ux && r_coord.y > ly && r_coord.y < uy)
		{
			return &t;
		}
	}

	return nullptr;
}

void TaskTreeRenderer::remove(GTask* gtask)
{
	gtask->removeFromParent();
	recRemove(gtask);
	updateBboxes();
}

void TaskTreeRenderer::addOffset(double x, double y)
{
	m_viewport.addOffset(x, y);
}

void TaskTreeRenderer::zoom(double z)
{
	m_viewport.zoom *= z;
}

void TaskTreeRenderer::draw(sf::RenderTarget* target) const
{
	GTask::box_count = 0;
	/*for (const GTask& task : m_bboxes)
	{
		task.draw(target, m_viewport);
	}*/
	m_bboxes.front().draw(target, m_viewport);
}

void TaskTreeRenderer::updateBbox(GTask& task, Context context)
{
	double x = context.bbox.x;
	double y = context.bbox.y;

	task.target.x = x;
	task.target.y = y;

	double scale = 1.0 / pow(2, context.level);

	std::list<GTask*> subs = task.sub_tasks;
	if (!subs.empty())
	{
		// Compute start of coord to draw subs
		double sub_start = x - task.sub_width / 2;
		for (GTask* t : subs)
		{
			Context sub_context;
			sub_context.level = context.level + 1;
			sub_context.bbox.x = sub_start + t->width / 2;
			sub_context.bbox.y = y + task.pos.h + m_padding.y * scale;

			updateBbox(*t, sub_context);

			sub_start += t->width + m_padding.x * scale;
		}
	}
}

void TaskTreeRenderer::renderTask(sf::RenderTarget* target, GTask* task) const
{

}

void TaskTreeRenderer::recRemove(GTask* gtask)
{
	// Recursive version of remove, deletes all childs and sub childs of gtask
	auto& subs = gtask->sub_tasks;
	for (GTask* gt : subs)
	{
		recRemove(gt);
	}
	// Finally, removes the current task
	m_bboxes.remove_if([=](GTask& t) {return &t == gtask; });
}

void TaskTreeRenderer::addToGTree(Task& task, GTask* top_task)
{
	// Create new GTask
	m_bboxes.emplace_back();
	GTask& current_gtask = m_bboxes.back();

	current_gtask.task = &task;
	current_gtask.top = top_task;
	
	// Link to top_task
	if (top_task)
	{
		top_task->sub_tasks.push_back(&current_gtask);
		current_gtask.pos = top_task->pos;
	}

	// Add subs
	std::list<Task*> subs = task.getSubs();
	if (!subs.empty())
	{
		for (Task* t : subs)
		{
			addToGTree(*t, &current_gtask);
		}
	}
}

void TaskTreeRenderer::computeWidth(GTask& task, uint32_t level)
{
	double scale = 1.0 / pow(2, level);
	task.width = max_size * scale;

	task.pos.w = task.width;
	task.pos.h = task.width / 2;

	task.sub_width = 0;

	if (!task.sub_tasks.empty())
	{
		for (GTask* t : task.sub_tasks)
		{
			computeWidth(*t, level + 1);
			task.sub_width += t->width + m_padding.x * scale;
		}

		task.sub_width -= m_padding.x * scale;
		task.width = std::max(task.width, task.sub_width);
	}
}
