//======================================================================================================================================//
// === Pre-Compiled Header === //
#include "stdafx.h"

//======================================================================================================================================//
// === This Class Header === //
#include "Block.h"

//======================================================================================================================================//
// === Static initializations === //
const sf::Vector2f Block::size = sf::Vector2f{ 16.0f, 16.0f } * gMng::textures_scale;

//======================================================================================================================================//
// === Block methods === //

Block::Block(const sf::Vector2f initPosition) :
	Entity(initPosition, true)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	initialize_Collider(_collider, size / gMng::textures_scale);
	
	//For tests porpouse
	_collider->setFillColor(sf::Color(40, 40, 40));
	
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
