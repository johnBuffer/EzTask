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
		double height = width / 2;

		sf::RectangleShape box(sf::Vector2f(width, height));
		box.setPosition(x, y);
		target->draw(box);

		if (!sub_tasks.empty())
		{
			const uint32_t h_padding = 10;
			const uint32_t v_padding = 20;
			
			uint32_t i = 0;
			uint32_t n = sub_tasks.size();
			
			double sub_width = width / 2;
			double spacing = sub_width + h_padding;
			double total_width = n * spacing - h_padding;

			const double sub_start = x + sub_width - total_width / 2;

			for (const Task& t : sub_tasks)
			{
				DrawContext sub_context;
				sub_context.level = context.level + 1;
				sub_context.x_orig = sub_start + spacing * i;
				sub_context.y_orig = y + height + v_padding;

				++i;
				t.draw(target, sub_context);
			}
		}
	}

	std::string name;
	std::vector<Task> sub_tasks;
};

int main()
{
	sf::RenderWindow window(sf::VideoMode(1000, 1000), "EzTask");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	DrawContext context;
	context.x_orig = 250;
	context.y_orig = 10;
	context.level = 0;

	Task root, t1, t2, t3, t4, t5;
	
	t4.sub_tasks.push_back(t5);
	
	t2.sub_tasks.push_back(t3);
	t2.sub_tasks.push_back(t4);

	root.sub_tasks.push_back(t1);
	root.sub_tasks.push_back(t2);



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