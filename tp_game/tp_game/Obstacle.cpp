//======================================================================================================================================//
// === Pre-Compiled Header === //
#include "stdafx.h"

//======================================================================================================================================//
// === This Class Header === //
#include "Obstacle.h"

//======================================================================================================================================//
// === Obstacle methods === //

Obstacle::Obstacle(const sf::Vector2f initPosition, const int id) :
	Tile(initPosition, id)
{
	_cd_action.trigger();

}

Obstacle::Obstacle()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 1 | ");
	_collider = NULL;
}

Obstacle::~Obstacle()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
	if (_collider)
		delete _collider;
	if (_animator)
		delete _animator;
}


void Obstacle::execute(const float deltaTime)
{
	if (this->isActive())
	{
		updateAction(deltaTime);
		//updatePosition(deltaTime);
	}

}

