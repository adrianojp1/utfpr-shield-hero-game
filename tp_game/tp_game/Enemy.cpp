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

	_hp = 1;

	initialize_animator();
	initialize_AllColliders();


	_invulnerability.trigger();

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

	if (_animator != NULL)
		delete _animator;
} // end destr

void Enemy::initialize_animator()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	_animator = new Animator(static_cast<Entity*>(this));

	*_animator << new Animation(gMng::orc_idle_Sp_Fp, 1, 0.0f);
	*_animator << new Animation(gMng::orc_walk_Sp_Fp, 4, 0.250f);
	*_animator << new Animation(gMng::orc_die_Sp_Fp, 3, 0.250f);
	*_animator << new Animation(gMng::orc_atk_Sp_Fp, 3, 0.200f);
} // end initializeAnimators

bool Enemy::isVulnerable()
{
	return true;
}

void Enemy::updateAction(const float deltaTime)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	_velocity.y += 900.0f * deltaTime; //constant g force

	_position += _velocity * deltaTime;
} // end updatePosition