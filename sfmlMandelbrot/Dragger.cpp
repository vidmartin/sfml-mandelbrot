
#include <iostream>

#include "Dragger.h"

Dragger::Dragger()
{
}

void Dragger::setOffset(sf::Vector2f offset)
{
	_offset = offset;
}

void Dragger::startDragging(sf::Vector2i mousePos)
{
	_origin = mousePos;
	_isDragging = true;
}

sf::Vector2f Dragger::getOffset(sf::Vector2i mousePos)
{
	if (_isDragging)
	{
		auto temp = (sf::Vector2f)(mousePos - _origin);
		return _offset + sf::Vector2f(temp.x * scale.x, temp.y * scale.y);
	}

	return _offset;
}

void Dragger::stopDragging(sf::Vector2i mousePos)
{
	_offset = getOffset(mousePos);
	_isDragging = false;
}
