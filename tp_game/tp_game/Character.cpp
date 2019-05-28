//======================================================================================================================================//
// === Pre-Compiled Header === //
#include "stdafx.h"

//======================================================================================================================================//
// === This Class Header === //
#include "Character.h"

//======================================================================================================================================//
// === Character methods === //

Character::Character(const sf::Vector2f initPosition) :
	Entity(initPosition, true)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	//Pointers
	_current_animator = NULL;
	_current_collider = NULL;

	//Parameters
	_position = initPosition;

	//Constants
	_jumpHeight = 0.0f;
	_speed = 0.0f;

	//Bools
	_facingRight = true;
	_canJump = false;
}

Character::Character()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 1 | ");

	//Pointers
	_current_animator = NULL;
	_current_collider = NULL;

	//Parameters
	_position = { 0.0f, 0.0f };

	//Constants
	_jumpHeight = 0.0f;
	_speed = 0.0f;

	//Bools
	_facingRight = true;
	_canJump = false;
}

Character::~Character()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
}

void Character::onCollision(const sf::Vector2f collisionDirection)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	//X axe
	if (collisionDirection.x < 0.0f)
	{ //Collision on left
		_velocity.x = 0.0f;
	}
	else if (collisionDirection.x > 0.0f)
	{ //Collisiton on right
		_velocity.x = 0.0f;
	}

	//Y axe
	if (collisionDirection.y > 0.0f)
	{ //Collisition on bottom
		_velocity.y = 0.0f;
		_canJump = true;
	}
	else if (collisionDirection.y < 0.0f)
	{ //Collision on top
		_velocity.y = 0.0f;
	}
}

void Character::setJumpHeight(const float jumpHeight)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
	_jumpHeight = jumpHeight;
}

float Character::getJumpHeight() const
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
	return _jumpHeight;
}

bool Character::isWalking(const float HorizontalMovement) const
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	if (HorizontalMovement == 0.0f)
	{
		return false;
	}
	return true;
}
