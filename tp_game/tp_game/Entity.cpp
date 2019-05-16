#include "stdafx.h"
#include "Entity.h"


Entity::Entity(const sf::Vector2f initPosition)
{
	std::cerr << __FUNCTION__ << " | -ov: 0 | " << std::endl;

	//Pointers
	_current_animator = NULL;
	_current_collider = NULL;

	//Parameters
	_position = initPosition;

	_speed = 0.0f;

	//Bools
	_facingRight = true;
}

Entity::Entity()
{
	std::cerr << __FUNCTION__ << " | -ov: 0 | " << std::endl;

	//Pointers
	_current_animator = NULL;
	_current_collider = NULL;

	//Parameters
	_position = { 0.0f, 0.0f };

	_speed = 0.0f;

	//Bools
	_facingRight = true;
}


Entity::~Entity()
{
	std::cerr << __FUNCTION__ << " | -ov: 0 | " << std::endl;
}

void Entity::initialize_Collider(sf::RectangleShape*& pCollider, const sf::Vector2f size)
{
	std::cerr << __FUNCTION__ << " | -ov: 0 | " << std::endl;

	pCollider = new sf::RectangleShape(size);
	pCollider->setOrigin(size / 2.0f);
}

void Entity::move(const float dx, const float dy)
{
	std::cerr << __FUNCTION__ << " | -ov: 0 | " << std::endl;

	move(sf::Vector2f(dx, dy));
}

void Entity::move(const sf::Vector2f offset)
{
	std::cerr << __FUNCTION__ << " | -ov: 0 | " << std::endl;

	_position += offset;
}

void Entity::onCollision(const sf::Vector2f collisionDirection)
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
	}
	else if (collisionDirection.y < 0.0f)
	{ //Collision on top
		_velocity.y = 0.0f;
	}
}

void Entity::setSpeed(const float speed)
{
	_speed = speed;
}

float Entity::getSpeed() const
{
	return _speed;
}

void Entity::setPosition(const sf::Vector2f position)
{
	_position = position;
}

sf::Vector2f Entity::getPosition() const
{
	return _position;
}

sf::RectangleShape* Entity::getCollider() const
{
	return _current_collider;
}
