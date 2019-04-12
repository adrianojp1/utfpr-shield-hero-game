//======================================================================================================================================//
// === Pre-Compiled Header === //
#include "stdafx.h"

//======================================================================================================================================//
// === This Class Header === //
#include "Player.h"

Player::Player(sf::Vector2f initPosition, float speed, float jumpHeight)
{
	_jumpHeight = jumpHeight;
	_speed = speed;
	_facingRight = true;

	_sprite.setOrigin(sf::Vector2f{ 7.0f, 7.5f });
	_sprite.setPosition(initPosition);

	_sprite.setPosition(initPosition);
	_sprite.setOrigin(7.0f, 7.5f);

	initializeAnimators();
} // end constr (parameters)

Player::Player()
{
	_facingRight = true;
	_speed = 0.0f;
	_jumpHeight = 0.0f;

	_idle_anmt = NULL;
	_walk_anmt = NULL;
} // end constr (no parameters)


Player::~Player()
{
	if(_idle_anmt != NULL)
		delete _idle_anmt;
	if(_walk_anmt != NULL)
		delete _walk_anmt;

} // end destr

void Player::initializeAnimators()
{
	_idle_anmt = new Animator("shield_hero.png", 1, 0.0f, &_sprite);
	_walk_anmt = new Animator("shield_hero-walk1.png", 4, 0.250f, &_sprite);
} // end initializeAnimators

void Player::execute(float deltaTime)
{
	sf::Vector2f movement{ 0.0f, 0.0f };
	float deltaSpace = _speed * deltaTime;

	//Move the player
	if (leftIsKeyPressed()) //Left
		moveToLeft(&movement.x, deltaSpace);
	if (rightIsKeyPressed()) //Right
		moveToRight(&movement.x, deltaSpace);
	
	_sprite.move(movement);

	if (isIdle(movement.x))
	{
		_idle_anmt->updateSprite(deltaTime, _facingRight);
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

		_walk_anmt->updateSprite(deltaTime, _facingRight);
	}
}

void Player::moveToLeft(float* HorizontalMovement, float offset)
{
	*HorizontalMovement -= offset;
}

void Player::moveToRight(float* HorizontalMovement, float offset)
{
	*HorizontalMovement += offset;
}

bool Player::isIdle(float HorizontalMovement)
{
	if (HorizontalMovement == 0.0f)
	{
		return true;
	}
	return false;
}

bool Player::leftIsKeyPressed()
{
	return (sf::Keyboard::isKeyPressed(sf::Keyboard::A));
}

bool Player::rightIsKeyPressed()
{
	return (sf::Keyboard::isKeyPressed(sf::Keyboard::D));
}

bool Player::jumpKeyPressed()
{
	return (sf::Keyboard::isKeyPressed(sf::Keyboard::W));
}

bool Player::defendKeyPressed()
{
	return (sf::Keyboard::isKeyPressed(sf::Keyboard::S));
}

void Player::draw(sf::RenderWindow& window)
{
	window.draw(this->_sprite);
}
