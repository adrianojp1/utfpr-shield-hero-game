//======================================================================================================================================//
// === Pre-Compiled Header === //
#include "stdafx.h"

//======================================================================================================================================//
// === This Class Header === //
#include "Entity.h"

//======================================================================================================================================//
// === Static initializations === //
Graphical_Manager* Entity::_pGraphMng = NULL;

//======================================================================================================================================//
// === Entity methods === //

Entity::Entity(const sf::Vector2f initPosition, bool active)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

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
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 1 | ");

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
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
}

void Entity::initialize_Collider(sf::RectangleShape*& pCollider, const sf::Vector2f size)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	pCollider = new sf::RectangleShape(size);
	pCollider->setOrigin(size / 2.0f);

	if (gMng::COLLISION_DBG)
	{
		pCollider->setOutlineThickness(0.2f);
		pCollider->setOutlineColor(sf::Color::White);
		pCollider->setFillColor(sf::Color::Transparent);
	}
}

void Entity::move(const float dx, const float dy)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	move(sf::Vector2f(dx, dy));
}

void Entity::move(const sf::Vector2f offset)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	_position += offset;
}

void Entity::onCollision(const sf::Vector2f collisionDirection)
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
	}
	else if (collisionDirection.y < 0.0f)
	{ //Collision on top
		_velocity.y = 0.0f;
	}
}

void Entity::setSpeed(const float speed)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
	_speed = speed;
}

float Entity::getSpeed() const
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
	return _speed;
}

void Entity::setPosition(const sf::Vector2f position)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
	_position = position;
}

sf::Vector2f Entity::getPosition() const
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
	return _position;
}

sf::RectangleShape* Entity::getCollider() const
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
	return _current_collider;
}

void Entity::activate()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	_active = true;
}

void Entity::desactivate()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	_active = false;
}

bool Entity::isActive() const
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	return _active;
}

void Entity::setGraphManager(gMng* gMng)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	_pGraphMng = gMng;
}

gMng* Entity::getGraphManager()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	return _pGraphMng;
}

void Entity::updateAction(const float deltaTime)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

}

void Entity::updateAnimation(const float deltaTime)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

}