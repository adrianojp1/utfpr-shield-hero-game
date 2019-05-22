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
	MyWindow::console_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	_position = position;

	_collider = new sf::RectangleShape(size);
	_collider->setOrigin(size / 2.0f);
	_collider->setFillColor(sf::Color::Transparent);
	_collider->setOutlineColor(color);
	_collider->setOutlineThickness(0.5f);
}

Platform::~Platform()
{
	MyWindow::console_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
}

void Platform::execute(float deltaTime)
{
	MyWindow::console_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	_collider->setPosition(_position);
}

void Platform::draw(MyWindow* window)
{
	MyWindow::console_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	window->draw(*(this->_collider));
}

void Platform::setPosition(sf::Vector2f position)
{
	MyWindow::console_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
	_position = position;
}

sf::Vector2f Platform::getPosition() const
{
	MyWindow::console_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
	return _position;
}
