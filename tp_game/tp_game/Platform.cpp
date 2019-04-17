//======================================================================================================================================//
// === Pre-Compiled Header === //
#include "stdafx.h"

//======================================================================================================================================//
// === This Class Header === //
#include "Platform.h"

//======================================================================================================================================//
// === Classes headers for redefinition === //
#include "MyWindow.h"

Platform::Platform(sf::Color color, sf::Vector2f size, sf::Vector2f position)
{
	_position = position;

	_collider = new sf::RectangleShape(size);
	_collider->setOrigin(size / 2.0f);
	_collider->setFillColor(sf::Color::Transparent);
	_collider->setOutlineColor(color);
	_collider->setOutlineThickness(0.5f);
}

Platform::~Platform()
{
}

void Platform::execute(float deltaTime)
{
	_collider->setPosition(_position);
}

void Platform::draw(MyWindow* window)
{
	window->draw(*(this->_collider));
}

void Platform::setPosition(sf::Vector2f position)
{
	_position = position;
}

sf::Vector2f Platform::getPosition() const
{
	return _position;
}
