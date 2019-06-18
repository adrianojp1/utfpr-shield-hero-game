//======================================================================================================================================//
// === Pre-Compiled Header === //
#include "stdafx.h"

//======================================================================================================================================//
// === This Class Header === //
#include "Entity.h"

//======================================================================================================================================//
// === Entity methods === //

Entity::Entity(const sf::Vector2f initPosition, bool active) : 
	Abstract_Entity(initPosition, active)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	//Pointers
	_animator = NULL;
	_current_collider = NULL;

	_speed = 0.0f;

	//Bools
	_facingRight = true;
}

Entity::Entity() : Abstract_Entity()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 1 | ");

	//Pointers
	_animator = NULL;
	_current_collider = NULL;

	_speed = 0.0f;

	//Bools
	_facingRight = true;
}


Entity::~Entity()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
}

void Entity::initialize_Collider(sf::RectangleShape*& pCollider, sf::Vector2f spriteSize)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
	
	spriteSize = spriteSize * gMng::textures_scale;

	pCollider = new sf::RectangleShape(spriteSize);
	pCollider->setOrigin(spriteSize / 2.0f);

	if (gMng::COLLISION_DBG)
	{
		pCollider->setOutlineThickness(1.0f);
		pCollider->setOutlineColor(sf::Color::White);
		pCollider->setFillColor(sf::Color::Transparent);
	}
}

void Entity::draw() const
{

	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	Entity::_pGraphMng->draw(*(_animator->getCurrentAnime()->getpSprite()));
	if (gMng::COLLISION_DBG)
		Entity::_pGraphMng->draw(*(_current_collider));
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

sf::RectangleShape* Entity::getCollider() const
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
	return _current_collider;
}

bool Entity::isFacingRight() const
{
	return _facingRight;
}
