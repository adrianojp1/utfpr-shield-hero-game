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
}

Character::Character()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 1 | ");

	//Pointers
	_current_collider = NULL;
	
	_animator = NULL;

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

	_velocity.x = 0.0f;

	updateAction(deltaTime);
	updateState();
	_animator->updateAnimation(deltaTime, _facingRight);

	if (!isVulnerable())
	{
		_animator->getCurrentAnime()->getpSprite()->setFillColor(sf::Color(77, 255, 77, 255));
	}
	else
	{
		_animator->getCurrentAnime()->getpSprite()->setFillColor(sf::Color(255, 255, 255, 255));
	}

	_current_collider->setPosition(_position);
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
		_canJump = true;
	}
	else if (collisionDirection.y < 0.0f)
	{ //Collision on top
		_velocity.y = 0.0f;
	}
}

bool Character::isVulnerable()
{
	if (_invulnerability.isZeroed())
	{
		return true;
	}
	else
	{
		return false;
	}
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

void Character::updateState()
{
	switch (_state)
	{
	case 0: //IDLE
		setTo_idle();
		break;
	case 1: //WALK 
		setTo_walk();
		break;
	case 2: //DEATH
		setTo_death();
		break;
	case 3: //COMBAT
		setTo_combat();
		break;
	default:
		break;
	}
}

void Character::setTo_idle()
{
	_current_collider = _idle_collider;
	_animator->setCurrentAnime(IDLE);
}

void Character::setTo_walk()
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

void Character::setTo_death()
{
	_current_collider = _death_collider;
	_animator->setCurrentAnime(DEATH);
}

void Character::setTo_combat()
{
	_current_collider = _combat_collider;
	_animator->setCurrentAnime(COMBAT);
}