#include "stdafx.h"
#include "Skeleton.h"

Skeleton::Skeleton(const sf::Vector2f initPosition) : Enemy(initPosition)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	_cd_attack.setTotalTime(4.0f);
	_speed = 0.0f;
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

void Skeleton::cast_spell()
{
	sf::Vector2f cast_position;
	cast_position.y = _position.y + _attack_offset.y;
	if (_facingRight)
	{
		cast_position.x = _position.x + _attack_offset.x;
	}
	else
		cast_position.x = _position.x - _attack_offset.x;
	Projectile* pProj = new Projectile(cast_position, _attackDamage, _facingRight, getProj_id());
	pProj->setSpeed(200.0f);
}

void Skeleton::doPrincipalOfAttack()
{
	cast_spell();
}

void Skeleton::updateAction(const float deltaTime)
{
	check_attack();
	if (isAttacking())
	{
		updateAttack();
	}
}
