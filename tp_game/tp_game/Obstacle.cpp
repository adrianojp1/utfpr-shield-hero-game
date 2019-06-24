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
	_triggered = false;
	_collisionDamage = 0;
}

Obstacle::Obstacle()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 1 | ");
	_collider = NULL;
	_collisionDamage = 0;
	_triggered = false;
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
		checkColls();
		decreaseTimers();

		updateAction(deltaTime);
		updatePosition(deltaTime);

		resetColls();
	}
}

void Obstacle::decreaseTimers()
{
	_cd_action.decreaseTime();
}

void Obstacle::setCollDmg(const int collDmg)
{
	_collisionDamage = collDmg;
}

const int Obstacle::getCollDmg() const
{
	return _collisionDamage;
}

