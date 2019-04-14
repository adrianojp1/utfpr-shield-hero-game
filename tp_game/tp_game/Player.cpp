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
	_jumpHeight = jumpHeight;
	_speed = speed;
	_facingRight = true;
	_position = initPosition;

	_sprite.setOrigin(sf::Vector2f{ 7.0f, 7.5f });
	_sprite.setPosition(initPosition);

	initializeAnimators();
} // end constr (parameters)

Player::Player()
{
	_facingRight = true;
	_speed = 0.0f;
	_jumpHeight = 0.0f;
	_position = { 0.0f, 0.0f };

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

	updatePosition(&movement, deltaTime);
	updateAnimation(movement, deltaTime);

	_position += movement;
	_sprite.setPosition(_position);
} // end execute

void Player::updatePosition(sf::Vector2f* pMovement, float deltaTime)
{
	float offset = _speed * deltaTime; //the displacement between the loop iterations

	//Move the player
	if (leftIsKeyPressed()) //Left
		moveToLeft(&(pMovement->x), offset);
	if (rightIsKeyPressed()) //Right
		moveToRight(&(pMovement->x), offset);
} // end updatePosition

void Player::updateAnimation(sf::Vector2f movement, float deltaTime)
{
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
} // end updateAnimtion

void Player::moveToLeft(float* HorizontalMovement, float offset)
{
	*HorizontalMovement -= offset;
} // end moveToleft

void Player::moveToRight(float* HorizontalMovement, float offset)
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

void Player::draw(MyWindow* window)
{
	window->draw(this->_sprite);
} // end draw
