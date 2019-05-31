//======================================================================================================================================//
// === Pre-Compiled Header === //
#include "stdafx.h"

//======================================================================================================================================//
// === This Class Header === //
#include "Character.h"

//======================================================================================================================================//
// === Static initializations === //
const int Character::IDLE(0);
const int Character::WALK(1);
const int Character::DEATH(2);
const int Character::COMBAT(3);

//======================================================================================================================================//
// === Character methods === //

Character::Character(const sf::Vector2f initPosition) :
	Entity(initPosition, true)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	//Pointers
	_current_animator = NULL;
	_current_collider = NULL;

	_animator = NULL;

	_idle_collider = NULL;
	_walk_collider = NULL;
	_death_collider = NULL;
	_combat_collider = NULL;

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
	
	_animator = NULL;

	_idle_collider = NULL;
	_walk_collider = NULL;
	_death_collider = NULL;
	_combat_collider = NULL;

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

	if (_idle_collider != NULL)
		delete _idle_collider;
	if (_walk_collider != NULL)
		delete _walk_collider;
	if (_combat_collider != NULL)
		delete _combat_collider;
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

void Character::updateState()
{
	switch (_state)
	{
	case 0: //IDLE
		setIdle();
		break;
	case 1: //WALK 
		setWalk();
		break;
	case 2: //DEATH
		setDeath();
		break;
	case 3: //COMBAT
		setCombat();
		break;
	default:
		break;
	}
}

void Character::setIdle()
{
	_current_collider = _idle_collider;
	_animator->setCurrentAnime(IDLE);
}

void Character::setWalk()
{
	if (_velocity.x > 0.0f)
	{
		_facingRight = true;
	}
	else
	{
		_facingRight = false;
	}

	_current_collider = _walk_collider;
	_animator->setCurrentAnime(WALK);
}

void Character::setDeath()
{
	_current_collider = _death_collider;
	_animator->setCurrentAnime(DEATH);
}

void Character::setCombat()
{
	_current_collider = _combat_collider;
	_animator->setCurrentAnime(COMBAT);
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
