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

	TaskTree tree;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.type == sf::Event::MouseButtonPressed)
			{
				tree.addTaskAt(sf::Mouse::getPosition(window));
			}
		}

		tree.update();

		window.clear();

		tree.draw(&window);
		
		window.display();
	}

	return 0;
}