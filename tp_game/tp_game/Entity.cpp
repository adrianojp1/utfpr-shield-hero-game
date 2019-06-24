//======================================================================================================================================//
// === Pre-Compiled Header === //
#include "stdafx.h"

//======================================================================================================================================//
// === This Class Header === //
#include "Entity.h"

//======================================================================================================================================//
// === Entity methods === //

Entity::Entity(const sf::Vector2f initPosition, const bool active, const int id) : Abstract_Entity(initPosition, active, id)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	//Pointers
	_animator = NULL;
	_current_collider = NULL;

	_speed = 0.0f;

	//Bools
	_facingRight = true;

	resetColls();
}

Entity::Entity() : Abstract_Entity()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 1 | ");

	//Pointers
	_animator = NULL;
	_current_collider = NULL;

	_speed = 0.0f;

	//Bools
	_facingRight = true;
}

Entity::~Entity()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");
}

void Entity::initialize_Collider(sf::RectangleShape *&pCollider, sf::Vector2f spriteSize)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

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

void Entity::draw()
{

	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	if (this->isActive())
	{
		Entity::_pGraphMng->draw(*(_animator->getCurrentAnime()->getpSprite()));
		if (gMng::COLLISION_DBG)
			Entity::_pGraphMng->draw(*(_current_collider));
	}
}

void Entity::move(const float dx, const float dy)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	move(sf::Vector2f(dx, dy));
}

void Entity::move(const sf::Vector2f offset)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	_position += offset;
}

void Entity::checkColls()
{
	if (_coll_onLeft)
	{
		colliding_onLeft();
	}
	else if (_coll_onRight)
	{
		colliding_onRight();
	}
	if (_coll_onBot)
	{
		colliding_onBottom();
	}
	else if (_coll_onTop)
	{
		colliding_onTop();
	}
}

void Entity::resetColls()
{
	_coll_onBot = false;
	_coll_onLeft = false;
	_coll_onRight = false;
	_coll_onTop = false;
}

void Entity::colliding_onLeft()
{
	_velocity.x = 0.0f;
}

void Entity::colliding_onRight()
{
	_velocity.x = 0.0f;
}

void Entity::colliding_onBottom()
{
	_velocity.y = 0.0f;
}

void Entity::colliding_onTop()
{
	_velocity.y = 0.0f;
}

void Entity::updatePosition(const float deltaTime)
{
	_position += _velocity * deltaTime;
}

void Entity::updateAnime_n_Collider()
{
	updateAnime();
	updateCollider();
}

void Entity::updateAnime()
{
	_animator->updateAnimation(_facingRight);
}

void Entity::updateCollider()
{
	_current_collider->setPosition(_position);
}

void Entity::decreaseTimers()
{
}

void Entity::onCollision(const sf::Vector2f collisionDirection)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	//X axe
	if (collisionDirection.x < 0.0f)
	{ //Collision on left
		_coll_onLeft = true;
	}
	else if (collisionDirection.x > 0.0f)
	{ //Collisiton on right
		_coll_onRight = true;
	}

	//Y axe
	if (collisionDirection.y > 0.0f)
	{ //Collisition on bottom
		_coll_onBot = true;
	}
	else if (collisionDirection.y < 0.0f)
	{ //Collision on top
		_coll_onTop = true;
	}
}

void Entity::setSpeed(const float speed)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");
	_speed = speed;
}

float Entity::getSpeed() const
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");
	return _speed;
}

sf::RectangleShape *Entity::getCollider() const
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");
	return _current_collider;
}

bool Entity::isFacingRight() const
{
	return _facingRight;
}
