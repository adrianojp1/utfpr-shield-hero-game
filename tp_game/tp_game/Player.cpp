//======================================================================================================================================//
// === Pre-Compiled Header === //
#include "stdafx.h"

//======================================================================================================================================//
// === This Class Header === //
#include "Player.h"

//======================================================================================================================================//
// === Player methods === //

Player::Player(const sf::Vector2f initPosition)
{
	std::cerr << __FUNCTION__ << " | -ov: 0 | " << std::endl;

	//Pointers
	_current_animator = NULL;
	_current_collider = NULL;

	//Parameters
	_position = initPosition;

	//Constants
	_jumpHeight = 30.0f;
	_walkSpeed = 60.f;

	//Bools
	_facingRight = true;
	_defending = false;
	_defCounterUp = false;
	_canJump = true;
	
	//Methods
	initialize_AllAnimators();
	initialize_AllColliders();

	_defCounterTimer.setTotalTime(0.3f); //Counter defense time

} // end constr (parameters)

Player::Player()
{
	std::cerr << __FUNCTION__ << " | -ov: 1 | " << std::endl;

	_facingRight = true;
	_defending = false;
	_defCounterUp = false;
	_canJump = true;
	_walkSpeed = 0.0f;
	_jumpHeight = 0.0f;
	_position = {0.0f, 0.0f};

	_idle_animator = NULL;
	_walk_animator = NULL;
	_def1_animator = NULL;
	_def2_animator = NULL;
	
	_idle_collider = NULL;
	_walk_collider = NULL;
	_def_collider = NULL;

	_defCounterTimer.setTotalTime(0.3f); //Counter defense time

} // end constr (no parameters)

Player::~Player()
{
	std::cerr << __FUNCTION__ << " | -ov: 0 | " << std::endl;

	//Destroy animators
	if (_idle_animator != NULL)
		delete _idle_animator;
	if (_walk_animator != NULL)
		delete _walk_animator;
	if (_def1_animator != NULL)
		delete _def1_animator;
	if (_def2_animator != NULL)
		delete _def2_animator;

	if (_idle_collider != NULL)
		delete _idle_collider;
	if (_walk_collider != NULL)
		delete _walk_collider;
	if (_def_collider != NULL)
		delete _def_collider;

} // end destr

void Player::initialize_AllAnimators()
{
	std::cerr << __FUNCTION__ << " | -ov: 0 | " << std::endl;

	_idle_animator = new Animator("Media\\shield-hero\\shield_hero-idle.png", 1, 0.0f, this);
	_walk_animator = new Animator("Media\\shield-hero\\shield_hero-walk.png", 4, 0.250f, this);
	_def1_animator = new Animator("Media\\shield-hero\\shield_hero-def1.png", 1, 0.0f, this);
	_def2_animator = new Animator("Media\\shield-hero\\shield_hero-def2.png", 1, 0.0f, this);
} // end initializeAnimators

void Player::initialize_AllColliders()
{
	std::cerr << __FUNCTION__ << " | -ov: 0 | " << std::endl;

	initialize_Collider(_idle_collider, _idle_animator->getSpriteSize());
	initialize_Collider(_walk_collider, _walk_animator->getSpriteSize());
	initialize_Collider(_def_collider, _def1_animator->getSpriteSize());
}

void Player::initialize_Collider(sf::RectangleShape*& pCollider, const sf::Vector2f size)
{
	std::cerr << __FUNCTION__ << " | -ov: 0 | " << std::endl;

	pCollider = new sf::RectangleShape(size);
	pCollider->setOrigin(size / 2.0f);

	//For tests porpouse
	pCollider->setOutlineThickness(0.2f);
	pCollider->setOutlineColor(sf::Color::White);
	pCollider->setFillColor(sf::Color::Transparent);
}

void Player::execute(const float deltaTime)
{
	std::cerr << __FUNCTION__ << " | -ov: 0 | " << std::endl;

	_velocity.x = 0.0f;

	_defCounterTimer.decreaseTime(deltaTime);

	updateAction(deltaTime);
	updateAnimation(deltaTime);

	_position += _velocity * deltaTime;

	_current_collider->setPosition(_position);
} // end execute

void Player::updateAction(const float deltaTime)
{
	std::cerr << __FUNCTION__ << " | -ov: 0 | " << std::endl;

	if (defendKeyPressed())
	{
		_defending = true;
		if (_defCounterTimer.isTicking())
			_defCounterUp = true;
		else if (_defCounterTimer.isZeroed())
			_defCounterUp = false;
		else
			_defCounterTimer.trigger();
	}
	// Player is not defending
	else
	{
		_defending = false;
		_defCounterTimer.resetTimer();

		//Move the player
		if (leftIsKeyPressed()) //Left
			_velocity.x -= _walkSpeed;

		if (rightIsKeyPressed()) //Right
			_velocity.x += _walkSpeed;

		if (jumpKeyPressed() && _canJump) //Jump
		{
			_canJump = false;

			//square root ( 2.0f * gravity * _jumpHeight )
			//gravity = 9.81 m / s^2
			//10 pixels = 1m
			//gravity = 98.1
			_velocity.y = -sqrtf(2.0f * 300.0f * _jumpHeight);
		}
	}

	_velocity.y += 300.0f * deltaTime; //constant g force

} // end updatePosition

void Player::updateAnimation(const float deltaTime)
{
	std::cerr << __FUNCTION__ << " | -ov: 0 | " << std::endl;

	if (_defending)
	{
		_current_collider = _def_collider;
		if(_defCounterUp)
			//Counter defense animation
			_current_animator = _def2_animator;
		else
			//Normal defense animation
			_current_animator = _def1_animator;
	}
	else
	{
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
	}
	_current_animator->updateSprite(deltaTime, _facingRight);
} // end updateAnimation

bool Player::leftIsKeyPressed() const
{
	return (sf::Keyboard::isKeyPressed(sf::Keyboard::A));
} // end leftIsKeyPressed

bool Player::rightIsKeyPressed() const
{
	return (sf::Keyboard::isKeyPressed(sf::Keyboard::D));
} // end rightIsKeyPressed

bool Player::jumpKeyPressed() const
{
	return (sf::Keyboard::isKeyPressed(sf::Keyboard::W));
} // end jumpKeyPressed

bool Player::defendKeyPressed() const
{
	return (sf::Keyboard::isKeyPressed(sf::Keyboard::S));
} // end defendKeyPressed

void Player::draw(MyWindow *window) const
{
	std::cerr << __FUNCTION__ << " | -ov: 0 | " << std::endl;

	window->draw(*(_current_animator->getpSprite()));
	window->draw(*(_current_collider));
} // end draw
/*
void Player::onCollision(const sf::Vector2f collisionDirection)
{
	//X axe
	if (collisionDirection.x < 0.0f)
	{ //Collision on left
		_velocity.x = 0.0f;
	}
	else if(collisionDirection.x > 0.0f)
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
}*/

bool Player::isDefending() const
{
	return _defending;
}

bool Player::isCounterUp() const
{
	return _defCounterUp;
}

bool Player::isDefending_with_Counter() const
{
	if (this->isDefending() && this->isCounterUp())
		return true;
	else
	return false;
}