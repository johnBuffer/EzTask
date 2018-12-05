#include <SFML/Graphics.hpp>

#include <vector>
#include <string>
#include <list>
#include <iostream>
/*
struct Geometry
{
	Geometry() = default;
	Geometry(double x_, double y_) :
		x(x_),
		y(y_),
		w(0.0),
		h(0.0)
	{}

	double x, y, w, h;
};

struct DrawContext
{
	double x_orig, y_orig;
	uint32_t level;
};

struct Task
{
	Task() = default;
	Task(double x, double y) :
		bbox(x, y)
	{}

	void draw(sf::RenderTarget* target) const
	{
		sf::RectangleShape box(sf::Vector2f(bbox.w, bbox.h));
		box.setOrigin(bbox.w / 2, 0);
		box.setPosition(bbox.x, bbox.y);

		target->draw(box);
	}

	void updateGeometry(DrawContext context)
	{
		
	}

	void updateWidth(uint32_t level)
	{
		const uint32_t h_padding = 25;

		_width = 512 / pow(2, level);
		_sub_width = 0;

		if (!sub_tasks.empty())
		{
			for (Task* t : sub_tasks)
			{
				t->updateWidth(level + 1);
				_sub_width += t->_width + h_padding;
			}
			
			_sub_width -= h_padding;
			_width = std::max(_width, _sub_width);
		}
	}

	void update()
	{
		bbox.x += (target_pos.x - bbox.x) * 0.1;
		bbox.y += (target_pos.y - bbox.y) * 0.1;
	}

	std::string name;
	std::list<Task*> sub_tasks;

	double _width;
	double _sub_width;

	Geometry bbox, target_pos;
};

/*
struct TaskTree
{
	TaskTree()
	{
		tasks.push_back(Task());
		updateGeometry();
	}

	void updateGeometry()
	{
		DrawContext context;
		context.x_orig = 500;
		context.y_orig = 10;
		context.level = 0;

		tasks.front().updateWidth(0);
		tasks.front().updateGeometry(context);
	}

	void update()
	{
		for (Task& t : tasks)
		{
			t.update();
		}
	}

	void draw(sf::RenderTarget* target) const
	{
		for (const Task& t : tasks)
		{
			t.draw(target);
		}
	}

	void add(const sf::Vector2i& coord)
	{
		for (Task& t : tasks)
		{
			double lx = t.bbox.x - t.bbox.w / 2;
			double ux = t.bbox.x + t.bbox.w / 2;

			double ly = t.bbox.y;
			double uy = t.bbox.y + t.bbox.h;

			if (coord.x > lx && coord.x < ux && coord.y > ly && coord.y < uy)
			{
				tasks.emplace_back(t.bbox.x, t.bbox.y);
				t.sub_tasks.push_back(&tasks.back());
				updateGeometry();
				break;
			}
		}
	}

	std::list<Task> tasks;
};*/


int main()
{
	sf::RenderWindow window(sf::VideoMode(1000, 1000), "EzTask");
	window.setFramerateLimit(60);

	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	//TaskTree tree;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.type == sf::Event::MouseButtonPressed)
			{
				//tree.add(sf::Mouse::getPosition(window));
			}
		}

		//tree.update();

		window.clear();

		//tree.draw(&window);
		
		window.display();
	}

	return 0;
}