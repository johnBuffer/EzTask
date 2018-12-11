#include "GTask.hpp"
#include "Connector.hpp"

sf::Font GTask::s_font;
uint32_t GTask::box_count;

GTask::GTask() :
	progress(0.0f),
	selected(false)
{
	
}

GTask::~GTask()
{
}

void GTask::removeFromParent()
{
	if (top)
	{
		top->sub_tasks.remove_if([=](GTask* t) {return t == this; });
	}
}

void GTask::draw(sf::RenderTarget* target, const Viewport& viewport) const
{
	double box_width = pos.w * viewport.zoom;
	double box_height = pos.h * viewport.zoom;

	if (box_height < 0.5)
		return;

	sf::Vector2f screen_pos = viewport.getViewportCoord(pos.x, pos.y);
	double x = screen_pos.x - box_width * 0.5;
	double y = screen_pos.y;
	
	++GTask::box_count;

	// Draw whit background
	sf::RectangleShape box(sf::Vector2f(box_width, box_height));
	box.setOrigin(box_width * 0.5, 0);
	box.setPosition(screen_pos);
	if (selected)
		box.setFillColor(sf::Color(200, 200, 200));
	else
		box.setFillColor(sf::Color::White);
	target->draw(box);

	// Draw header
	double header_height = box_height * 0.25;
	sf::RectangleShape header(sf::Vector2f(box_width, header_height));
	header.setPosition(x, y);
	double p = progress;
	header.setFillColor(sf::Color(255*(1-p), 255*p, 0));
	target->draw(header);

	// Draw progress bar


	// Draw connectors
	for (const GTask* gt : sub_tasks)
	{
		Connector c(gt, this);
		c.draw(target, viewport);
	}

	// Draw task's title
	sf::Text text;
	double text_scale = box_height * 0.00375;
	text.setFont(s_font);
	text.setCharacterSize(48);
	text.setFillColor(sf::Color::Black);
	text.setScale(text_scale, text_scale);
	text.setPosition(x, y);
	text.setString("Task's name");
	target->draw(text);

	// Draw sub tasks names
	text.setScale(text_scale*0.5f, text_scale*0.5f);
	double x_progress_indicator = x + box_width * 0.02;
	double x_text = x + box_width * 0.075;
	double y_text = y + header_height;
	for (const GTask* gt : sub_tasks)
	{
		double radius = box_height * 0.03;
		sf::CircleShape progress_indicator(radius);
		progress_indicator.setOrigin(0, -radius*0.75);
		progress_indicator.setFillColor(sf::Color(255 * (1 - gt->progress), 255 * gt->progress, 0));
		progress_indicator.setPosition(x_progress_indicator, y_text);
		target->draw(progress_indicator);

		text.setPosition(x_text, y_text);
		target->draw(text);
		y_text += 0.1 * box_height;

		if (y_text - y > 0.9 * box_height)
			break;
	}

	for (const GTask* gt : sub_tasks)
	{
		gt->draw(target, viewport);
	}
}

void GTask::initialize()
{
	s_font.loadFromFile("C:/fonts/font.ttf");
}
