//======================================================================================================================================//
// === Pre-Compiled Header === //
#include "stdafx.h"

//======================================================================================================================================//
// === This Class Header === //
#include "Player.h"

//======================================================================================================================================//
// === Classes headers for redefinition === //
#include "MyWindow.h"

Player::Player(sf::Vector2f initPosition, float speed, float jumpHeight)
{
	_current_Animator = NULL;
	_current_Collider = NULL;

	_jumpHeight = jumpHeight;
	_walkSpeed = speed;
	_position = initPosition;

	_facingRight = true;
	_defending = false;
	_defCounterUp = false;
	_canJump = true;

	_defCounterTimer.setTotalTime(0.3f);

	initializeAnimators();
	initializeColliders();
} // end constr (parameters)

Player::Player()
{
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
} // end constr (no parameters)

Player::~Player()
{
	//Destroy animators
	if (_idle_animator != NULL)
		delete _idle_animator;
	if (_walk_animator != NULL)
		delete _walk_animator;
	if (_def1_animator != NULL)
		delete _def1_animator;
	if (_def2_animator != NULL)
		delete _def2_animator;

	if (_idle_Collider != NULL)
		delete _idle_Collider;
	if (_walk_Collider != NULL)
		delete _walk_Collider;
	if (_def_Collider != NULL)
		delete _def_Collider;

} // end destr

void Player::initializeAnimators()
{
	_idle_animator = new Animator("Media\\shield_hero-idle-1.png", 1, 0.0f, this);
	_walk_animator = new Animator("Media\\shield_hero-walk-1.png", 4, 0.250f, this);
	_def1_animator = new Animator("Media\\shield_hero-def1-1.png", 1, 0.0f, this);
	_def2_animator = new Animator("Media\\shield_hero-def2-1.png", 1, 0.0f, this);
} // end initializeAnimators

void Player::initializeColliders()
{
	_idle_Collider = new sf::RectangleShape(_idle_animator->getSpriteSize());
	_idle_Collider->setOrigin(_idle_Collider->getSize() / 2.0f);
	_idle_Collider->setOutlineThickness(0.2f);
	_idle_Collider->setOutlineColor(sf::Color::White);
	_idle_Collider->setFillColor(sf::Color::Transparent);

	_walk_Collider = new sf::RectangleShape(_walk_animator->getSpriteSize());
	_walk_Collider->setOrigin(_walk_Collider->getSize() / 2.0f);
	_walk_Collider->setOutlineThickness(0.2f);
	_walk_Collider->setOutlineColor(sf::Color::White);
	_walk_Collider->setFillColor(sf::Color::Transparent);

	_def_Collider = new sf::RectangleShape(_def1_animator->getSpriteSize());
	_def_Collider->setOrigin(_def_Collider->getSize() / 2.0f);
	_def_Collider->setOutlineThickness(0.2f);
	_def_Collider->setOutlineColor(sf::Color::White);
	_def_Collider->setFillColor(sf::Color::Transparent);
}

void Player::execute(float deltaTime)
{
	_velocity.x = 0.0f;

	_defCounterTimer.decreaseTime(deltaTime);

	updatePosition(deltaTime);
	updateAnimation(deltaTime);

	_position += _velocity * deltaTime;

	_current_Collider->setPosition(_position);
} // end execute

void Player::updatePosition(float deltaTime)
{
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

void Player::updateAnimation(float deltaTime)
{
	if (_defending)
	{
		_current_Collider = _def_Collider;
		if(_defCounterUp)
			//Counter defense animation
			_current_Animator = _def2_animator;
		else
			//Normal defense animation
			_current_Animator = _def1_animator;
	}
	else
	{
		if (isNotWalking(_velocity.x))
		{
			_current_Collider = _idle_Collider;
			_current_Animator = _idle_animator;
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
			_current_Collider = _walk_Collider;
			_current_Animator = _walk_animator;
		}
	}
	_current_Animator->updateSprite(deltaTime, _facingRight);
} // end updateAnimation

bool Player::isNotWalking(float HorizontalMovement)
{
	if (HorizontalMovement == 0.0f)
	{
		return true;
	}
	return false;
} // end isIdle

bool Player::leftIsKeyPressed()
{
	return (sf::Keyboard::isKeyPressed(sf::Keyboard::A));
} // end leftIsKeyPressed

bool Player::rightIsKeyPressed()
{
	return (sf::Keyboard::isKeyPressed(sf::Keyboard::D));
} // end rightIsKeyPressed

bool Player::jumpKeyPressed()
{
	return (sf::Keyboard::isKeyPressed(sf::Keyboard::W));
} // end jumpKeyPressed

bool Player::defendKeyPressed()
{
	return (sf::Keyboard::isKeyPressed(sf::Keyboard::S));
} // end defendKeyPressed

void Player::draw(MyWindow *window)
{
	window->draw(*(_current_Animator->getpSprite()));
	window->draw(*(_current_Collider));
} // end draw

void Player::onCollision(sf::Vector2f collisionDirection)
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
}

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

void Player::setWalkSpeed(float walkSpeed)
{
	_walkSpeed = walkSpeed;
}

float Player::getWalkSpeed() const
{
	return _walkSpeed;
}

void Player::setJumpHeight(float jumpHeight)
{
	_jumpHeight = jumpHeight;
}

float Player::getJumpHeight() const
{
	return _jumpHeight;
}

void Player::setPosition(sf::Vector2f position)
{
	_position = position;
}

sf::Vector2f Player::getPosition() const
{
	return _position;
}
