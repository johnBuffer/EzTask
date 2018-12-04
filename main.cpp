#include <SFML/Graphics.hpp>

#include <vector>
#include <string>

struct DrawContext
{
	double x_orig, y_orig;
	uint32_t level;
};

struct Task
{
	void draw(sf::RenderTarget* target, DrawContext context) const
	{
		double x = context.x_orig;
		double y = context.y_orig;

		double scale = 512 / pow(2, context.level);
		double width = scale;
		double height = width / 3;

		sf::RectangleShape box(sf::Vector2f(width, height));
		box.setOrigin(width / 2, 0);
		box.setPosition(x, y);
		target->draw(box);

		sf::RectangleShape box_width(sf::Vector2f(_width, 2));
		box_width.setOrigin(_width / 2, 0);
		box_width.setPosition(x, y+height);
		box_width.setFillColor(sf::Color::Red);
		target->draw(box_width);

		if (!sub_tasks.empty())
		{
			const uint32_t h_padding = 30;
			const uint32_t v_padding = 10;
			
			uint32_t i = 0;
			uint32_t n = sub_tasks.size();
			
			double sub_width = width / 2;

			// Compute total width
			double total_width = 0;
			for (const Task& t : sub_tasks)
			{
				total_width += t._width + h_padding;
			}
			total_width -= h_padding;

			// Compute start of coord to draw subs
			double sub_start = x - total_width / 2;
			for (const Task& t : sub_tasks)
			{
				DrawContext sub_context;
				sub_context.level = context.level + 1;
				sub_context.x_orig = sub_start + t._width / 2;
				sub_context.y_orig = y + height + v_padding;

				sub_start += t._width + h_padding;

				t.draw(target, sub_context);
			}
		}
	}

	void updateWidth(uint32_t level)
	{
		const uint32_t h_padding = 30;

		_width = 512 / pow(2, level);

		if (!sub_tasks.empty())
		{
			double tmp_width = 0;
			for (Task& t : sub_tasks)
			{
				t.updateWidth(level + 1);
				tmp_width += t._width + h_padding;
			}
			
			_width = std::max(tmp_width - h_padding, _width);
		}

	}

	std::string name;
	std::vector<Task> sub_tasks;

	double _width;
};

int main()
{
	sf::RenderWindow window(sf::VideoMode(1000, 1000), "EzTask");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	DrawContext context;
	context.x_orig = 500;
	context.y_orig = 10;
	context.level = 0;

	Task root, t1, t2, t3, t4, t5;
	
	t4.sub_tasks.push_back(t5);
	
	t2.sub_tasks.push_back(t3);
	t2.sub_tasks.push_back(t4);

	root.sub_tasks.push_back(t1);
	root.sub_tasks.push_back(t2);
	root.updateWidth(0);


	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		
		root.draw(&window, context);

		window.display();
	}

	return 0;
}