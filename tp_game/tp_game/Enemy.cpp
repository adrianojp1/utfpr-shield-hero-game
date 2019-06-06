//======================================================================================================================================//
// === Pre-Compiled Header === //
#include "stdafx.h"

//======================================================================================================================================//
// === This Class Header === //
#include "Enemy.h"

//======================================================================================================================================//
// === Enemy methods === //

Enemy::Enemy(const sf::Vector2f initPosition) : Character(initPosition), cd_attack()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	_jumpHeight = 0.0f;
	_hp = 1;
	_collisionDamage = 1;

} // end constr (parameters)

Enemy::Enemy() : Character()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 1| ");

	_attacking = false;
	_canAttack = false;
	_facingRight = true;
	_canJump = true;
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

/*void Enemy::turnArround()
{
	_velocity.x = -_velocity.x;
}

void Enemy::collision_onLeft()
{
	turnArround();
}

void Enemy::collision_onRight()
{
	turnArround();
}*/

void Enemy::decreaseTimers()
{
	_invulnerability.decreaseTime();
	cd_attack.decreaseTime();
}

void Enemy::add_blockUnderneath(Entity *pBlock)
{
	if (pBlock)
		_vblocksUnderneath.push_back(pBlock);
}

void Enemy::clear_blocksUnderneath()
{
	_vblocksUnderneath.clear();
}
