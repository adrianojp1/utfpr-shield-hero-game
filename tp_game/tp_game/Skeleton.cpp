#include "stdafx.h"
#include "Skeleton.h"

Skeleton::Skeleton(const sf::Vector2f initPosition) : Enemy(initPosition)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	_cd_attack.setTotalTime(4.0f);
	_speed = 0.0f;
	_canAttack = true;
	_velocity.x = _speed;
	_facingRight = false;
	_overView.setSize({ 2688.0f, 13.0f*gMng::textures_scale.y });
	_overView.setOrigin(_overView.getSize() / 2.0f);
	_attack_offset = sf::Vector2f{-3.0f , 2.5f } *gMng::textures_scale;
}

Skeleton::Skeleton() : Enemy()
{
	_speed = 0.0f;
}

Skeleton::~Skeleton()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");
}

void Skeleton::updateAttack()
{
	if ((*_animator)[COMBAT]->isFinished())
	{
		doPrincipalOfAttack();
		_state = IDLE;
		_cd_attack.reset_and_trigger();
	}
}

void Skeleton::cast_spell(Player* pP)
{
	sf::Vector2f cast_position;
	cast_position.y = _position.y + _attack_offset.y;
	if (pP->getPosition().x - this->_position.x >= 0)
	{
		_facingRight = true;
		cast_position.x = _position.x + _attack_offset.x;
	}
	else
	{
		_facingRight = false;
		cast_position.x = _position.x - _attack_offset.x;
	}
	Projectile* pProj = new Projectile(cast_position, _attackDamage, _facingRight, getProj_id());
	pProj->setSpeed(200.0f);
}

void Skeleton::cast_spell(Player* pP1, Player* pP2)
{
	sf::Vector2f cast_position;
	cast_position.y = _position.y + _attack_offset.y;
	if (pP1->getPosition().x - this->_position.x >= 0 || pP2->getPosition().x - this->_position.x >= 0)
	{
		_facingRight = true;
		cast_position.x = _position.x + _attack_offset.x;
	}
	else
	{
		_facingRight = false;
		cast_position.x = _position.x - _attack_offset.x;
	}
	Projectile* pProj = new Projectile(cast_position, _attackDamage, _facingRight, getProj_id());
	pProj->setSpeed(200.0f);
}

void Skeleton::doPrincipalOfAttack()
{
	if (_pPlayer2)
		cast_spell(_pPlayer1, _pPlayer2);
	else
	cast_spell(_pPlayer1);
}

void Skeleton::check_attack()
{
	if (_cd_attack.isZeroed())
	{
		Player* pPlayer = a_playerInRange();
		if (pPlayer)
		{
			attack();
		}
	}
}

void Skeleton::updateAction(const float deltaTime)
{
	check_attack();
	if (isAttacking())
	{
		updateAttack();
	}
}
