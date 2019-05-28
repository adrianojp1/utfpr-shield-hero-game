//======================================================================================================================================//
// === Pre-Compiled Header === //
#include "stdafx.h"

//======================================================================================================================================//
// === This Class Header === //
#include "Block.h"

//======================================================================================================================================//
// === Static initializations === //
const sf::Vector2f Block::size = { 16.0f, 16.0f };

//======================================================================================================================================//
// === Block methods === //

Block::Block(const sf::Vector2f initPosition) :
	Entity(initPosition, true)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	//_position = initPosition;

	initialize_Collider(_collider, size);

	//For tests porpouse
	_collider->setOutlineThickness(-0.5f);
	_collider->setOutlineColor(sf::Color::Color(150, 150, 150));
	_collider->setFillColor(sf::Color::Color(40, 40, 40));

	_current_collider = _collider;
}

Block::Block() : Entity()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 1 | ");
	_collider = NULL;
}

Block::~Block()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
	if (_collider)
		delete _collider;
}

void Block::execute(float deltaTime)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	_collider->setPosition(_position);
}

void Block::draw() const
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	Entity::_pGraphMng->draw(*(this->_collider));
}
