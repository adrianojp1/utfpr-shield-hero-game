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
	sf::Vector2f movement{0.0f, 0.0f};

	_defCounterTimer.decreaseTime(deltaTime);

	updatePosition(&movement, deltaTime);
	updateAnimation(movement, deltaTime);

	_position += movement;

	_current_Collider->setPosition(_position);
} // end execute

void Player::updatePosition(sf::Vector2f *pMovement, float deltaTime)
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

		float offset = _walkSpeed * deltaTime; //the displacement between the loop iterations

		//Move the player
		if (leftIsKeyPressed()) //Left
			moveToLeft(&(pMovement->x), offset);
		if (rightIsKeyPressed()) //Right
			moveToRight(&(pMovement->x), offset);
	}
} // end updatePosition

void Player::updateAnimation(sf::Vector2f movement, float deltaTime)
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
		if (isIdle(movement.x))
		{
			_current_Collider = _idle_Collider;
			_current_Animator = _idle_animator;
		}
		else
		{
			if (movement.x > 0.0f)
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

void Player::moveToLeft(float *HorizontalMovement, float offset)
{
	*HorizontalMovement -= offset;
} // end moveToleft

void Player::moveToRight(float *HorizontalMovement, float offset)
{
	*HorizontalMovement += offset;
} // end moveToRight

bool Player::isIdle(float HorizontalMovement)
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
