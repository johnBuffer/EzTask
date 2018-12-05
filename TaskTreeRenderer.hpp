#pragma once

#include <SFML/Graphics.hpp>
#include <list>

#include "Task.hpp"

struct Bbox
{
	Bbox() = default;
	Bbox(double x_, double y_, double w_, double h_) :
		x(x_),
		y(y_),
		w(w_),
		h(h_)
	{}

	double x, y, w, h;
};

struct GTask
{
	Task* task;
	Bbox pos, target;
	double width;
	double sub_width;
	std::list<GTask*> sub_tasks;
};

struct Context
{
	uint32_t level;
	Bbox bbox;
};

struct Viewport
{
	sf::Vector2f offset;
	double zoom;
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

	void draw(sf::RenderTarget* target) const;

private:
	std::list<GTask> m_bboxes;

	sf::Vector2f m_padding;
	const double max_size = 512.0;

	void addToGTree(Task& task, GTask* super);
	void computeWidth(GTask& task, uint32_t level);

	void updateBbox(GTask& task, Context context);
};
