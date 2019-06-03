//======================================================================================================================================//
// === Pre-Compiled Header === //
#include "stdafx.h"

//======================================================================================================================================//
// === This Class Header === //
#include "Character.h"

//======================================================================================================================================//
// === Static initializations === //
const int Character::IDLE(0);
const int Character::WALK(1);
const int Character::DEATH(2);
const int Character::COMBAT(3);

//======================================================================================================================================//
// === Character methods === //

Character::Character(const sf::Vector2f initPosition) :
	Entity(initPosition, true)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	//Pointers
	_current_collider = NULL;

	_animator = NULL;

	_idle_collider = NULL;
	_walk_collider = NULL;
	_death_collider = NULL;
	_combat_collider = NULL;

	//Parameters
	_position = initPosition;

	//Constants
	_jumpHeight = 0.0f;
	_speed = 0.0f;
	_hp = 0;

	_state = IDLE;

	//Bools
	_facingRight = true;
	_canJump = false;
	_vulnerable = true;
	_invulnerability.trigger();
}

Character::Character()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 1 | ");

	//Pointers
	_current_collider = NULL;

	_idle_collider = NULL;
	_walk_collider = NULL;
	_death_collider = NULL;
	_combat_collider = NULL;

	//Parameters
	_position = { 0.0f, 0.0f };

	//Constants
	_jumpHeight = 0.0f;
	_speed = 0.0f;
	_hp = 0;

	//Bools
	_facingRight = true;
	_canJump = false;
}

Character::~Character()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	if (_idle_collider != NULL)
		delete _idle_collider;
	if (_walk_collider != NULL)
		delete _walk_collider;
	if (_combat_collider != NULL)
		delete _combat_collider;
}

void Character::initialize_AllColliders()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	initialize_Collider(_idle_collider, (*_animator)[IDLE]->getCanvasSize());
	initialize_Collider(_walk_collider, (*_animator)[WALK]->getCanvasSize());
	initialize_Collider(_death_collider, (*_animator)[DEATH]->getCanvasSize());
	initialize_Collider(_combat_collider, (*_animator)[COMBAT]->getCanvasSize());
}

void Character::execute(const float deltaTime)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	if (this->isActive())
	{
		decreaseTimers();

		if (!this->isDying())
		{
			updateAction(deltaTime);
			applyGforce(deltaTime);
			updatePosition(deltaTime);
		}
		else
		{
			updateDeath();
		}

		switchAnime_n_Collider();

		if (!isVulnerable())
		{
			apply_invulnerable_effect();
		}
		else
		{
			apply_default_effect();
		}

		_animator->updateAnimation(deltaTime, _facingRight);
		_current_collider->setPosition(_position);
	}
}

void Character::draw() const
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
	
	Entity::_pGraphMng->draw(*(_animator->getCurrentAnime()->getpSprite()));
	if (gMng::COLLISION_DBG)
		Entity::_pGraphMng->draw(*(_current_collider));
}

void Character::onCollision(const sf::Vector2f collisionDirection)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	//X axe
	if (collisionDirection.x < 0.0f)
	{
		collision_onLeft();
	}
	else if (collisionDirection.x > 0.0f)
	{
		collision_onRight();
	}

	//Y axe
	if (collisionDirection.y > 0.0f)
	{
		collision_onBottom();
	}
	else if (collisionDirection.y < 0.0f)
	{
		collision_onTop();
	}
}

void Character::collision_onLeft()
{
	_velocity.x = 0.0f;
}

void Character::collision_onRight()
{
	_velocity.x = 0.0f;
}

void Character::collision_onBottom()
{
	_velocity.y = 0.0f;
	_canJump = true;
}

void Character::collision_onTop()
{
	_velocity.y = 0.0f;
}

void Character::updatePosition(const float deltaTime)
{
	_position += _velocity * deltaTime;
}

void Character::applyGforce(const float deltaTime)
{
	_velocity.y += gMng::gravity * deltaTime; //constant g force
}

void Character::jump()
{
	/*
	square root ( 2.0f * gravity * _jumpHeight )
	gravity = 9.81 m / s^2
	10 pixels = 1m
	gravity = 98.1*/
	_velocity.y = -sqrtf(2.0f * gMng::gravity * _jumpHeight);
}

void Character::moveToLeft(const float speedMultiplier)
{
	_velocity.x -= _speed * speedMultiplier;
}

void Character::moveToRight(const float speedMultiplier)
{
	_velocity.x += _speed * speedMultiplier;
}

void Character::updateDeath()
{
	if ((*_animator)[DEATH]->isFinished())
	{
		/*bool Animation::isFinished() const
			return (getFrameCounter() == getnFrames() - 1); ARRUMAR
		*/
		ressurect(); //mudar, só o player
	}
}

bool Character::isVulnerable()
{
	if (_invulnerability.isZeroed())
	{
		_vulnerable = true;
		return _vulnerable;
	}
	else
	{
		_vulnerable = false;
		return _vulnerable;
	}
}

void Character::apply_invulnerable_effect()
{
	_animator->getCurrentAnime()->getpSprite()->setFillColor(sf::Color(70, 200, 100, 255));
}

void Character::apply_default_effect()
{
	_animator->getCurrentAnime()->getpSprite()->setFillColor(sf::Color(255, 255, 255, 255));
}

bool Character::isDying()
{
	if (this->isActive() && _hp <= 0)
		return true;
	return false;
}

void Character::takeDmg(const int dmg)
{
	if (this->isVulnerable())
	{
		_hp -= dmg;
		_invulnerability.reset_and_trigger();

		if (_hp <= 0)
			this->die();
	}
}

void Character::die()
{
	_state = DEATH;
	_invulnerability.setCurrentTime(0.0f);
}

void Character::ressurect()
{
	if (_state == DEATH)
	{
		_state = IDLE;
		resetHp();
		(*_animator)[DEATH]->reset();
	}
}

void Character::resetHp()
{
	_hp = 1;
}

void Character::decreaseTimers()
{
	_invulnerability.decreaseTime();
}

void Character::setJumpHeight(const float jumpHeight)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
	_jumpHeight = jumpHeight;
}

float Character::getJumpHeight() const
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
	return _jumpHeight;
}

void Character::setHp(const int hp)
{
	_hp = hp;
}

int Character::getHp() const
{
	return _hp;
}

void Character::switchAnime_n_Collider()
{
	switch (_state)
	{
	case 0: //IDLE
		switchTo_idle();
		break;
	case 1: //WALK 
		switchTo_walk();
		break;
	case 2: //DEATH
		switchTo_death();
		break;
	case 3: //COMBAT
		switchTo_combat();
		break;
	default:
		break;
	}
}

void Character::switchTo_idle()
{
	_current_collider = _idle_collider;
	_animator->setCurrentAnime(IDLE);
}

void Character::switchTo_walk()
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
	_animator->setCurrentAnime(WALK);
}

void Character::switchTo_death()
{
	_current_collider = _death_collider;
	_animator->setCurrentAnime(DEATH);
}

void Character::switchTo_combat()
{
	_current_collider = _combat_collider;
	_animator->setCurrentAnime(COMBAT);
}