
#include <iostream>
#include <chrono>
#include <thread>

#include <SFML/Graphics.hpp>

#include "Dragger.h"

using namespace std::chrono_literals;

int main()
{
	const sf::Vector2f scaleBase(0.25f, 0.25f);
	float scrolled = 0;

	Dragger dragger = Dragger();
	dragger.setOffset(sf::Vector2f(0.5f, 0.f));

	sf::RenderWindow window(sf::VideoMode(500, 500), L"Mandelbrotova množina / Mandelbrot set");
	sf::RectangleShape shape(sf::Vector2f(500, 500));
	shape.setTextureRect(sf::IntRect(0, 0, 1, 1));

	sf::Shader shader;
	
	if (!shader.loadFromFile("mandelbrot_shader.vert", "mandelbrot_shader.frag"))
	{
		std::cout << "chyba v shaderu";
		return 1;
	}

	while (window.isOpen())
	{
		sf::Vector2f scale = scaleBase * pow(1.1f, scrolled); 
		dragger.scale = sf::Vector2f(1.f / window.getSize().x / scale.x, 1.f / window.getSize().y / scale.y);

		sf::Vector2i mousePos = sf::Mouse::getPosition() - window.getPosition();

		sf::Event e;
		while (window.pollEvent(e))
		{
			if (e.type == sf::Event::Closed) { window.close(); }
			
			switch (e.type)
			{
			case sf::Event::Closed:
				window.close();
				return 0;
			case sf::Event::MouseButtonPressed:
				if (e.mouseButton.button == sf::Mouse::Button::Left)
				{
					dragger.startDragging(mousePos);
				}
				break;
			case sf::Event::MouseButtonReleased:
				if (e.mouseButton.button == sf::Mouse::Button::Left)
				{
					dragger.stopDragging(mousePos);
				}
				break;
			case sf::Event::MouseWheelScrolled:
				scrolled += e.mouseWheelScroll.delta;
				break;
			default:
				break;
			}			
		}		
		
		shader.setUniform("U_offset", dragger.getOffset(mousePos));
		shader.setUniform("U_scale", scale);
		shader.setUniform("U_stepsZoom", (int)(scrolled / 4));

		window.clear();
		window.draw(shape, &shader);
		window.display();

		std::this_thread::sleep_for(10ms);
	}

	return 0;
}