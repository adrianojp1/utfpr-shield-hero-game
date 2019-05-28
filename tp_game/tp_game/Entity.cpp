#include "stdafx.h"
#include "Entity.h"


Entity::Entity(const sf::Vector2f initPosition, bool active)
{
	Graphical_Manager::console_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	//Pointers
	_current_animator = NULL;
	_current_collider = NULL;

	//Parameters
	_position = initPosition;

	_speed = 0.0f;

	//Bools
	_facingRight = true;
	_active = active;
}

Entity::Entity()
{
	Graphical_Manager::console_log(__FUNCTION__ + (std::string)" | -ov: 1 | ");

	//Pointers
	_current_animator = NULL;
	_current_collider = NULL;

	//Parameters
	_position = { 0.0f, 0.0f };

	_speed = 0.0f;

	//Bools
	_facingRight = true;
	_active = false;
}


Entity::~Entity()
{
	Graphical_Manager::console_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
}

void Entity::initialize_Collider(sf::RectangleShape*& pCollider, const sf::Vector2f size)
{
	Graphical_Manager::console_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	pCollider = new sf::RectangleShape(size);
	pCollider->setOrigin(size / 2.0f);
}

void Entity::move(const float dx, const float dy)
{
	Graphical_Manager::console_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	move(sf::Vector2f(dx, dy));
}

void Entity::move(const sf::Vector2f offset)
{
	Graphical_Manager::console_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	_position += offset;
}

void Entity::onCollision(const sf::Vector2f collisionDirection)
{
	Graphical_Manager::console_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

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
	Graphical_Manager::console_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
	_speed = speed;
}

float Entity::getSpeed() const
{
	Graphical_Manager::console_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
	return _speed;
}

void Entity::setPosition(const sf::Vector2f position)
{
	Graphical_Manager::console_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
	_position = position;
}

sf::Vector2f Entity::getPosition() const
{
	Graphical_Manager::console_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
	return _position;
}

sf::RectangleShape* Entity::getCollider() const
{
	Graphical_Manager::console_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
	return _current_collider;
}

void Entity::activate()
{
	_active = true;
}

void Entity::desactivate()
{
	_active = false;
}

bool Entity::isActive() const
{
	return _active;
}

void Entity::updateAction(const float deltaTime)
{
}

void Entity::updateAnimation(const float deltaTime)
{
}
