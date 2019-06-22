//======================================================================================================================================//
// === Pre-Compiled Header === //
#include "stdafx.h"

//======================================================================================================================================//
// === This Class Header === //
#include "Enemy.h"

//======================================================================================================================================//
// === Enemy methods === //

Enemy::Enemy(const sf::Vector2f initPosition) : 
	Character(initPosition), cd_attack()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	_jumpHeight = 0.0f;
	_maxHp = 1;
	resetHp();
	_collisionDamage = 1;
	_attackDamage = 2;
	_canAttack = true;
	_attacking = false;

} // end constr (parameters)

Enemy::Enemy() : Character()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 1| ");

	_attacking = false;
	_canAttack = false;
	_facingRight = false;
	_canJump = false;
	_position = {0.0f, 0.0f};
	_hp = 0;
	_collisionDamage = 0;
} // end constr (no parameters)

Enemy::~Enemy()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

} // end destr

bool Enemy::isVulnerable()
{
	return true;
}

void Enemy::setCollDmg(const int dmg)
{
	_collisionDamage = dmg;
}

int Enemy::getCollDmg() const
{
	return _collisionDamage;
}

void Enemy::setAttackDmg(const int dmg)
{
	_attackDamage = dmg;
}

int Enemy::getAttackDmg() const
{
	return _attackDamage;
}

/*void Enemy::turnArround()
{
	_velocity.x = -_velocity.x;
}

void Enemy::colliding_onLeft()
{
	turnArround();
}

void Enemy::colliding_onRight()
{
	turnArround();
}*/

void Enemy::decreaseTimers()
{
	_invulnerability.decreaseTime();
	cd_attack.decreaseTime();
}

bool Enemy::isAttacking() const
{
	return _attacking;
}
