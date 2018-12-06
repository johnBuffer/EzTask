#pragma once

#include <SFML/Graphics.hpp>
#include "Task.hpp"
#include "utils.hpp"
#include "Viewport.hpp"

struct GTask
{
	GTask();

	Task* task;
	Bbox pos, target;
	double width;
	double sub_width;
	std::list<GTask*> sub_tasks;
	float progress;

	void draw(sf::RenderTarget* target, const Viewport& viewport) const;

	// Static stuff
	static sf::Font s_font;
	static void initialize();
};