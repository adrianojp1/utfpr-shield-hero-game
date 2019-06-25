//======================================================================================================================================//
// === Pre-Compiled Header === //
#include "stdafx.h"

//======================================================================================================================================//
// === This Class Header === //
#include "Enemy.h"

//======================================================================================================================================//
// === Enemy methods === //

Enemy::Enemy(const sf::Vector2f initPosition) : 
	Character(initPosition), _cd_attack()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	_jumpHeight = 0.0f;
	_maxHp = 1;
	resetHp();
	_collisionDamage = 1;
	_attackDamage = 2;
	_canCauseDmg = false;
	_floor_foward = false;
	_cd_attack.trigger();

} // end constr (parameters)

Enemy::Enemy() : Character()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 1| ");

	_canCauseDmg = false;
	_facingRight = false;
	_canJump = false;
	_floor_foward = false;
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

void Enemy::decreaseTimers()
{
	_invulnerability.decreaseTime();
	_cd_attack.decreaseTime();
}

Player* Enemy::a_playerInRange()
{
	Player* pP = NULL;
	cMng* collMng = cMng::getInstance();
	if (collMng->intersects(_pPlayer1, &_overView))
		pP = _pPlayer1;
	else if (_pPlayer2 && collMng->intersects(_pPlayer2, &_overView))
		pP = _pPlayer2;
	
	return pP;
}

bool Enemy::playerAhead(Player* pPlayer)
{
	return (_facingRight && pPlayer->getPosition().x > _position.x) || (!_facingRight && pPlayer->getPosition().x < _position.x);
}

void Enemy::updateAnime_n_Collider()
{
	updateAnime();
	updateCollider();
	_overView.setPosition(_position);
}

void Enemy::check_attack()
{
	_canCauseDmg = false;
	if (_cd_attack.isZeroed())
	{
		Player* pPlayer = a_playerInRange();
		if (pPlayer && playerAhead(pPlayer))
		{
			attack();
		}
	}
}

void Enemy::attack()
{
	_state = COMBAT;
}

void Enemy::updateAttack()
{
	if (principalFrameOfAttack())
	{
		doPrincipalOfAttack();
	}
	if ((*_animator)[COMBAT]->isFinished())
	{
		_state = IDLE;
		_cd_attack.reset_and_trigger();
	}
}

bool Enemy::isAttacking() const
{
	return (_state == COMBAT);
}

bool Enemy::principalFrameOfAttack()
{
	return (*_animator)[COMBAT]->getFrameCounter() == (*_animator)[COMBAT]->getnFrames() - 1;
}

const sf::Vector2f Enemy::getFrontEdge() const
{
	sf::Vector2f halfSize = _current_collider->getSize() / 2.0f;
	float x = _position.x + (_facingRight? halfSize.x : -halfSize.x);
	return { x, _position.y + halfSize.y + 5.0f};
}

bool Enemy::ableToCauseDamage()
{
	return _canCauseDmg;
}

void Enemy::setFloor_foward(const bool floor_fwd)
{
	_floor_foward = floor_fwd;
}

const bool Enemy::getFloor_foward() const
{
	return _floor_foward;
}

sf::RectangleShape* Enemy::getAttackRect() const
{
	return NULL;
}
