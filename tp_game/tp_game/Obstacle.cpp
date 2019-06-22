//======================================================================================================================================//
// === Pre-Compiled Header === //
#include "stdafx.h"

//======================================================================================================================================//
// === This Class Header === //
#include "Obstacle.h"

//======================================================================================================================================//
// === Obstacle methods === //

Obstacle::Obstacle(const sf::Vector2f initPosition) :
	Entity(initPosition, true)
{
	_obs_collider = NULL;

	_cd_action.trigger();

	_state = 0;
}

Obstacle::Obstacle()
{
}

Obstacle::~Obstacle()
{
	_obs_collider = NULL;
}

void Obstacle::initialize_AllColliders()
{
}

void Obstacle::execute(const float deltaTime)
{
}

void Obstacle::draw() const
{
}

void Obstacle::updateAction(const float deltaTime)
{
}

void Obstacle::updatePosition(const float deltaTime)
{
}
