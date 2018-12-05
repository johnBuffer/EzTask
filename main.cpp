#include <SFML/Graphics.hpp>

#include <vector>
#include <string>
#include <list>
#include <iostream>
#include "TaskTree.hpp"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1000, 1000), "EzTask");
	window.setFramerateLimit(60);

	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	bool clicking = false;
	sf::Vector2i click_position;

	TaskTree tree;

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
				clicking = true;
				click_position = sf::Mouse::getPosition(window);
			}
			else if (event.type == sf::Event::MouseButtonReleased)
			{
				clicking = false;
				if (mouse_pos == click_position)
					tree.addTaskAt(mouse_pos);
			}
			else if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::A)
				{
					tree.zoom(1.25);
				}
				else if (event.key.code == sf::Keyboard::E)
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