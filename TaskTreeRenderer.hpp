#pragma once

#include <SFML/Graphics.hpp>
#include <list>

#include "Task.hpp"
#include "Viewport.hpp"
#include "utils.hpp"
#include "GTask.hpp"

struct Context
{
	uint32_t level;
	Bbox bbox;
};


class TaskTreeRenderer
{
public:
	TaskTreeRenderer();

	void update();
	void generateGTree(Task& root_task);
	void updateBboxes();

	void addSubTask(Task& task, GTask* gtask);
	GTask* getTaskAt(const sf::Vector2f& coord);
	void remove(GTask* gtask);

	void addOffset(double x, double y);
	void zoom(double z);
	void draw(sf::RenderTarget* target) const;

private:
	std::list<GTask> m_bboxes;
	Viewport m_viewport;

	sf::Vector2f m_padding;
	const double max_size = 512.0;

	void addToGTree(Task& task, GTask* super);
	void computeWidth(GTask& task, uint32_t level);
	void updateBbox(GTask& task, Context context);
	void renderTask(sf::RenderTarget* target, GTask* task) const;
	void recRemove(GTask* gtask);
};
