#include "TaskTreeRenderer.hpp"
#include <iostream>

TaskTreeRenderer::TaskTreeRenderer() :
	m_padding(25, 25)
{
}

void TaskTreeRenderer::update()
{
	const double speed = 0.1;
	for (GTask& task : m_bboxes)
	{
		task.pos.x += (task.target.x - task.pos.x) * speed;
		task.pos.y += (task.target.y - task.pos.y) * speed;
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
	root_context.bbox.x = 500;
	root_context.bbox.y = m_padding.y;
	root_context.level = 0;

	updateBbox(m_bboxes.front(), root_context);
}

void TaskTreeRenderer::addSubTask(Task& task, GTask* gtask)
{
	addToGTree(task, gtask);
	
	updateBboxes();
}

GTask* TaskTreeRenderer::getTaskAt(const sf::Vector2f & coord)
{
	for (GTask& t : m_bboxes)
	{
		double lx = t.pos.x - t.pos.w / 2;
		double ux = t.pos.x + t.pos.w / 2;

		double ly = t.pos.y;
		double uy = t.pos.y + t.pos.h;

		if (coord.x > lx && coord.x < ux && coord.y > ly && coord.y < uy)
		{
			return &t;
		}
	}

	return nullptr;
}

void TaskTreeRenderer::draw(sf::RenderTarget * target) const
{
	for (const GTask& task : m_bboxes)
	{
		sf::RectangleShape box(sf::Vector2f(task.pos.w, task.pos.h));
		box.setOrigin(task.pos.w / 2, 0);
		box.setPosition(task.pos.x, task.pos.y);

		target->draw(box);
	}
}

void TaskTreeRenderer::updateBbox(GTask& task, Context context)
{
	double x = context.bbox.x;
	double y = context.bbox.y;

	task.target.x = x;
	task.target.y = y;

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
			sub_context.bbox.y = y + task.pos.h + m_padding.y;

			updateBbox(*t, sub_context);

			sub_start += t->width + m_padding.x;
		}
	}
}
void TaskTreeRenderer::addToGTree(Task& task, GTask* top_task)
{
	// Create new GTask
	m_bboxes.emplace_back();
	GTask& current_gtask = m_bboxes.back();

	current_gtask.task = &task;
	
	// Link to top_task
	if (top_task)
	{
		top_task->sub_tasks.push_back(&current_gtask);
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
	task.width = max_size / pow(2, level);

	task.pos.w = task.width;
	task.pos.h = task.width / 2;

	task.sub_width = 0;

	if (!task.sub_tasks.empty())
	{
		for (GTask* t : task.sub_tasks)
		{
			computeWidth(*t, level + 1);
			task.sub_width += t->width + m_padding.x;
		}

		task.sub_width -= m_padding.x;
		task.width = std::max(task.width, task.sub_width);
	}
}
