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
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");
	
	_jumpHeight = 30.0f;
	_speed = 40.f;

	_facingRight = true;
	_canJump = true;

	_state = IDLE;

	initialize_animator();
	initialize_AllColliders();

} // end constr (parameters)

Enemy::Enemy() : Character()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 1| ");

	_facingRight = true;
	_canJump = true;
	_speed = 0.0f;
	_position = {0.0f, 0.0f};

	_animator = NULL;
} // end constr (no parameters)

Enemy::~Enemy()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	//Destroy animators
	if (_animator != NULL)
		delete _animator;
} // end destr

void Enemy::initialize_animator()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	_animator = new Animator(static_cast<Entity*>(this));

	*_animator << new Animation(gMng::orc_idle_Sp_Fp, 1, 0.0f);
	*_animator << new Animation(gMng::orc_walk_Sp_Fp, 4, 0.250f);

} // end initializeAnimators

void Enemy::initialize_AllColliders()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	initialize_Collider(_idle_collider, (*_animator)[IDLE]->getCanvasSize());
	initialize_Collider(_walk_collider, (*_animator)[WALK]->getCanvasSize());
}

void Enemy::execute(const float deltaTime)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	//_velocity.x = -25.0f;

	updateAction(deltaTime);
	updateState();
	_animator->updateAnimation(deltaTime, _facingRight);

	_current_collider->setPosition(_position);
} // end execute

void Enemy::updateAction(const float deltaTime)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	_velocity.y += 900.0f * deltaTime; //constant g force

	_position += _velocity * deltaTime;
} // end updatePosition
/*
void Enemy::updateAnimation(const float deltaTime)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	switch (_state)
	{
	case 0: //IDLE
		_current_collider = _idle_collider;
		_animator->setCurrentAnime(IDLE);
		break;
	case 1: //WALK
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
		break;
	default:
		break;
	}

	_animator->updateAnimation(deltaTime, _facingRight);
}*/

void Enemy::draw() const
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	Entity::_pGraphMng->draw(*(_animator->getCurrentAnime()->getpSprite()));
	if(gMng::COLLISION_DBG)
		Entity::_pGraphMng->draw(*(_current_collider));
} // end draw
