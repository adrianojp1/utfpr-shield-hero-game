//======================================================================================================================================//
// === Pre-Compiled Header === //
#include "stdafx.h"

//======================================================================================================================================//
// === This Class Header === //
#include "Static_Spike.h"

//======================================================================================================================================//
// === Static initializations === //

//======================================================================================================================================//
// === Static_Spike methods === //

Static_Spike::Static_Spike(const sf::Vector2f initPosition, const int id) :
	Obstacle(initPosition, id)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
	_collisionDamage = 1;
}

Static_Spike::Static_Spike() : Obstacle()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 1 | ");
	
	_collider = NULL;
}

Static_Spike::~Static_Spike()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
	if (_collider)
		delete _collider;
	if (_animator)
		delete _animator;
}

void Static_Spike::updateAction(const float deltaTime)
{
}
