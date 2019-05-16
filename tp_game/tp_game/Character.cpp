//======================================================================================================================================//
// === Pre-Compiled Header === //
#include "stdafx.h"

//======================================================================================================================================//
// === This Class Header === //
#include "Character.h"

//======================================================================================================================================//
// === Character methods === //

Character::Character(const sf::Vector2f initPosition) :
	Entity(initPosition)
{
	std::cerr << __FUNCTION__ << " | -ov: 0 | " << std::endl;

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
	std::cerr << __FUNCTION__ << " | -ov: 1 | " << std::endl;

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
	std::cerr << __FUNCTION__ << " | -ov: 0 | " << std::endl;
}

void Character::initialize_Collider(sf::RectangleShape*& pCollider, const sf::Vector2f size)
{
	std::cerr << __FUNCTION__ << " | -ov: 0 | " << std::endl;

	pCollider = new sf::RectangleShape(size);
	pCollider->setOrigin(size / 2.0f);
}
/*
void Character::move(const float dx, const float dy)
{
	std::cerr << __FUNCTION__ << " | -ov: 0 | " << std::endl;

	_position += sf::Vector2f(dx, dy);
}

void Character::move(const sf::Vector2f offset)
{
	std::cerr << __FUNCTION__ << " | -ov: 0 | " << std::endl;

	_position += offset;
}*/

void Character::onCollision(const sf::Vector2f collisionDirection)
{
	std::cerr << __FUNCTION__ << " | -ov: 0 | " << std::endl;

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
	_jumpHeight = jumpHeight;
}

float Character::getJumpHeight() const
{
	return _jumpHeight;
}
/*
void Character::setSpeed(const float speed)
{
	_speed = speed;
}

float Character::getSpeed() const
{
	return _speed;
}

void Character::setPosition(const sf::Vector2f position)
{
	_position = position;
}

sf::Vector2f Character::getPosition() const
{
	return _position;
}

sf::RectangleShape* Character::getCollider() const
{
	return _current_collider;
}
*/
bool Character::isWalking(const float HorizontalMovement) const
{
	std::cerr << __FUNCTION__ << " | -ov: 0 | " << std::endl;

	if (HorizontalMovement == 0.0f)
	{
		return false;
	}
	return true;
}
