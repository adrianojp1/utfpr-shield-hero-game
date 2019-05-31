//======================================================================================================================================//
// === Pre-Compiled Header === //
#include "stdafx.h"

//======================================================================================================================================//
// === This Class Header === //
#include "Player.h"

//======================================================================================================================================//
// === Player methods === //

Player::Player(const sf::Vector2f initPosition) :
	Character(initPosition)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	_jumpHeight = 300.0f;
	_speed = 200.f;

	_facingRight = true;
	_defCounterUp = false;
	_canJump = true;
	
	_state = IDLE;

	initialize_animator();
	initialize_AllColliders();

	_defCounterTimer.setTotalTime(0.3f);

} // end constr (parameters)

Player::Player() : 
	Character()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 1| ");

	_facingRight = true;
	_defCounterUp = false;
	_canJump = true;
	_speed = 0.0f;
	_jumpHeight = 0.0f;
	_position = {0.0f, 0.0f};

	_defCounterTimer.setTotalTime(0.3f); //Counter defense time

} // end constr (no parameters)

Player::~Player()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	//Destroy animators
	if (_animator != NULL)
		delete _animator;
} // end destr

void Player::initialize_animator()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	_animator = new Animator(static_cast<Entity*>(this));

	*_animator << new Animation(gMng::player_idle_Sp_Fp, 1, 0.0f);
	*_animator << new Animation(gMng::player_walk_Sp_Fp, 4, 0.250f);
	*_animator << new Animation(gMng::player_die_Sp_Fp, 3, 0.250f);
	*_animator << new Animation(gMng::player_def1_Sp_Fp, 1, 0.0f);
	*_animator << new Animation(gMng::player_def2_Sp_Fp, 1, 0.0f);
} // end initializeAnimators

void Player::initialize_AllColliders()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	initialize_Collider(_idle_collider, (*_animator)[IDLE]->getCanvasSize());
	initialize_Collider(_walk_collider, (*_animator)[WALK]->getCanvasSize());
	initialize_Collider(_combat_collider,  (*_animator)[COMBAT]->getCanvasSize());
}

void Player::execute(const float deltaTime)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	_velocity.x = 0.0f;

	_defCounterTimer.decreaseTime();

	updateAction(deltaTime);
	updateState();
	_animator->updateAnimation(deltaTime, _facingRight);
	_current_collider->setPosition(_position);
} // end execute

void Player::updateAction(const float deltaTime)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	if (defendKeyPressed())
	{
		_state = COMBAT;
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
		_state = IDLE;
		_defCounterTimer.resetTimer();

		if (leftIsKeyPressed() || rightIsKeyPressed())
		{
			_state = WALK;

			//Move the player
			if (leftIsKeyPressed()) //Left
				_velocity.x -= _speed;

			if (rightIsKeyPressed()) //Right
				_velocity.x += _speed;
		}

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

	_velocity.y += 900.0f * deltaTime; //constant g force

	_position += _velocity * deltaTime;
} // end updatePosition
/*
void Player::updateAnimation(const float deltaTime)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

} // end updateAnimation
*/
void Player::setCombat()
{
	_current_collider = _combat_collider;
	if (_defCounterUp)
		//Counter defense animation
		_animator->setCurrentAnime(COMBAT + 1); //Def2
	else
		//Normal defense animation
		_animator->setCurrentAnime(COMBAT); //Def1
}

bool Player::leftIsKeyPressed() const
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
	return (sf::Keyboard::isKeyPressed(sf::Keyboard::A));
} // end leftIsKeyPressed

bool Player::rightIsKeyPressed() const
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
	return (sf::Keyboard::isKeyPressed(sf::Keyboard::D));
} // end rightIsKeyPressed

bool Player::jumpKeyPressed() const
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
	return (sf::Keyboard::isKeyPressed(sf::Keyboard::W));
} // end jumpKeyPressed

bool Player::anyMoveKeyPressed() const
{
	return (leftIsKeyPressed() || rightIsKeyPressed() || jumpKeyPressed());
}

bool Player::defendKeyPressed() const
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
	return (sf::Keyboard::isKeyPressed(sf::Keyboard::S));
} // end defendKeyPressed

void Player::draw() const
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	Entity::_pGraphMng->draw(*(_animator->getCurrentAnime()->getpSprite()));
	if(gMng::COLLISION_DBG)
		Entity::_pGraphMng->draw(*(_current_collider));
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
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
	if(_state == COMBAT)
		return true;
	return false;
}

bool Player::isCounterUp() const
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
	return _defCounterUp;
}

bool Player::isDefending_with_Counter() const
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
	if (this->isDefending() && this->isCounterUp())
		return true;
	else
	return false;
}