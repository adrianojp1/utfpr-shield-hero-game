//======================================================================================================================================//
// === Pre-Compiled Header === //
#include "stdafx.h"

//======================================================================================================================================//
// === This Class Header === //
#include "Enemy.h"

//======================================================================================================================================//
// === Enemy methods === //

Enemy::Enemy(const sf::Vector2f initPosition) : Character(initPosition)
{
	MyWindow::console_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	/*
	//Pointers
	_current_animator = NULL;
	_current_collider = NULL;

	//Parameters
	_position = initPosition;
	*/
	//Constants
	_jumpHeight = 30.0f;
	_speed = 40.f;

	//Bools
	_facingRight = true;
	_canJump = true;

	//Methods
	initialize_AllAnimators();
	initialize_AllColliders();

} // end constr (parameters)

Enemy::Enemy() : Character()
{
	MyWindow::console_log(__FUNCTION__ + (std::string) " | -ov: 1| ");

	_facingRight = true;
	_canJump = true;
	_speed = 0.0f;
	_position = {0.0f, 0.0f};

	_idle_animator = NULL;
	_walk_animator = NULL;

	_idle_collider = NULL;
	_walk_collider = NULL;

} // end constr (no parameters)

Enemy::~Enemy()
{
	MyWindow::console_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	//Destroy animators
	if (_idle_animator != NULL)
		delete _idle_animator;
	if (_walk_animator != NULL)
		delete _walk_animator;

	if (_idle_collider != NULL)
		delete _idle_collider;
	if (_walk_collider != NULL)
		delete _walk_collider;

} // end destr

void Enemy::initialize_AllAnimators()
{
	MyWindow::console_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	_idle_animator = new Animator(orcNS::idle_sprite_filePath, 1, 0.0f, this);
	_walk_animator = new Animator(orcNS::walk_sprite_filePath, 4, 0.250f, this);

} // end initializeAnimators

void Enemy::initialize_AllColliders()
{
	MyWindow::console_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	initialize_Collider(_idle_collider, _idle_animator->getSpriteSize());
	initialize_Collider(_walk_collider, _walk_animator->getSpriteSize());
}

void Enemy::initialize_Collider(sf::RectangleShape *&pCollider, const sf::Vector2f size)
{
	MyWindow::console_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	pCollider = new sf::RectangleShape(size);
	pCollider->setOrigin(size / 2.0f);

	//For tests porpouse
	pCollider->setOutlineThickness(0.2f);
	pCollider->setOutlineColor(sf::Color::Green);
	pCollider->setFillColor(sf::Color::Transparent);
}

void Enemy::execute(const float deltaTime)
{
	MyWindow::console_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	_velocity.x = 0.0f;

	updateAction(deltaTime);
	updateAnimation(deltaTime);

	_position += _velocity * deltaTime;

	_current_collider->setPosition(_position);
} // end execute

void Enemy::updateAction(const float deltaTime)
{

	_velocity.y += 300.0f * deltaTime; //constant g force
} // end updatePosition

void Enemy::updateAnimation(const float deltaTime)
{
	MyWindow::console_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	if (!isWalking(_velocity.x))
	{
		_current_collider = _idle_collider;
		_current_animator = _idle_animator;
	}
	else
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
		_current_animator = _walk_animator;
	}
	_current_animator->updateSprite(deltaTime, _facingRight);
}

void Enemy::draw(MyWindow *window) const
{
	MyWindow::console_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	window->draw(*(_current_animator->getpSprite()));
	window->draw(*(_current_collider));
} // end draw
