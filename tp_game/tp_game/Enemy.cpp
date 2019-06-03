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
	_damage = 1;

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
	_hp = 0;
	_damage = 0;
} // end constr (no parameters)

Enemy::~Enemy()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	if (_animator)
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
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	return true;
}

void Enemy::setDmg(const int dmg)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	_damage = dmg;
}

int Enemy::getDmg() const
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	return _damage;
}

void Enemy::updateAction(const float deltaTime)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

} // end updatePosition