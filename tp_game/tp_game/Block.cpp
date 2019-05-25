//======================================================================================================================================//
// === Pre-Compiled Header === //
#include "stdafx.h"

//======================================================================================================================================//
// === This Class Header === //
#include "Block.h"

//======================================================================================================================================//
// === Classes headers for redefinition === //
#include "MyWindow.h"

Block::Block(const sf::Vector2f initPosition) :
	Entity(initPosition, true)
{
	MyWindow::console_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	//_position = initPosition;

	initialize_Collider(_collider, blockNS::blockSize);

	//For tests porpouse
	_collider->setOutlineThickness(-0.5f);
	_collider->setOutlineColor(sf::Color::Color(150, 150, 150));
	_collider->setFillColor(sf::Color::Color(40, 40, 40));

	_current_collider = _collider;
}

Block::Block() : Entity()
{
	MyWindow::console_log(__FUNCTION__ + (std::string)" | -ov: 1 | ");
	_collider = NULL;
}

Block::~Block()
{
	MyWindow::console_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
	if (_collider)
		delete _collider;
}

void Block::execute(float deltaTime)
{
	MyWindow::console_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	_collider->setPosition(_position);
}

void Block::draw(MyWindow* window) const
{
	MyWindow::console_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	window->draw(*(this->_collider));
}

/*
void Block::setPosition(sf::Vector2f position)
{
	MyWindow::console_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
	_position = position;
}

sf::Vector2f Block::getPosition() const
{
	MyWindow::console_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
	return _position;
}
*/