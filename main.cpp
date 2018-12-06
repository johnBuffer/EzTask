#include <SFML/Graphics.hpp>

#include <vector>
#include <string>
#include <list>
#include <iostream>
#include "TaskTree.hpp"

int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 4;

	sf::RenderWindow window(sf::VideoMode(1000, 1000), "EzTask", sf::Style::Default, settings);
	//window.setFramerateLimit(60);

	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	bool clicking = false;
	sf::Vector2i click_position;

	TaskTree tree;
	GTask::initialize();

	while (window.isOpen())
	{
		sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					clicking = true;
					click_position = sf::Mouse::getPosition(window);
				}
			}
			else if (event.type == sf::Event::MouseButtonReleased)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					clicking = false;
					if (mouse_pos == click_position)
						tree.addTaskAt(mouse_pos);
				}
				else
				{
					Task* t = tree.getTaskAt(mouse_pos);
					if (t)
						t->setProgress(1.0f - t->getProgress());
				}
			}
			else if (event.type == sf::Event::MouseWheelScrolled)
			{
				if (event.mouseWheelScroll.delta > 0)
				{
					tree.zoom(1.25);
				}
				else
				{
					tree.zoom(0.8);
				}
			}
		}

		if (clicking)
		{
			double dx = click_position.x - mouse_pos.x;
			double dy = click_position.y - mouse_pos.y;

			tree.addOffset(dx, dy);

			click_position = mouse_pos;
		}

		tree.update();

		window.clear();

		tree.draw(&window);
		
		window.display();
	}

	return 0;
}