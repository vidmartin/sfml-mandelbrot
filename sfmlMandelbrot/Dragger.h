#pragma once

#include <SFML/Graphics.hpp>

class Dragger
{
public:
	Dragger();

	void startDragging(sf::Vector2i mousePos);
	void setOffset(sf::Vector2f offset);
	sf::Vector2f getOffset(sf::Vector2i mousePos);
	void stopDragging(sf::Vector2i mousePos);
	
	bool isDragging() { return _isDragging; }

	sf::Vector2f scale;

private:
	sf::Vector2i _origin;
	sf::Vector2f _offset;
	bool _isDragging = false;
};

