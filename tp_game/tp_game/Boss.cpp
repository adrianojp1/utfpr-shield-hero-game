#include "stdafx.h"
#include "Boss.h"

Boss::Boss(const sf::Vector2f initPosition) : Enemy(initPosition)
{
	initialize_animator();
	initialize_AllColliders();
	_speed = 70.0f;
	_hp = 10;
	_cd_attack.setTotalTime(2.0f);
	_attack_offset = sf::Vector2f{ 31.0f, 5.0f } *gMng::textures_scale;
	_attack_rect.setSize(sf::Vector2f{ 49.0f, 62.0f }*gMng::textures_scale);
	_attack_rect.setOrigin(_attack_rect.getSize());

	_overView.setSize((*_animator)[COMBAT]->getpSprite()->getSize() * gMng::textures_scale);
	_overView.setOrigin(_overView.getSize() / 2.0f);
}

Boss::Boss()
{
}

Boss::~Boss()
{
}

void Boss::initialize_animator()
{
	_animator = new Animator(static_cast<Entity*>(this));

	*_animator << new Animation(gMng::boss_idle_texture, 4, 0.150f, 2);
	*_animator << new Animation(gMng::boss_walk_texture, 6, 0.300f, 2);
	*_animator << new Animation(gMng::boss_atk_texture, 3, 0.100f, 2);
	*_animator << new Animation(gMng::boss_atk_texture, 3, 0.100f, 2);
}

bool Boss::principalFrameOfAttack()
{
	return 1;
}

void Boss::doPrincipalOfAttack()
{
	if (_facingRight)
	{
		_attack_rect.setPosition(_position + _attack_offset);
	}
	else
	{
		_attack_rect.setPosition(_position - _attack_offset);
	}

	_canCauseDmg = true;
}

void Boss::updateAction(const float deltaTime)
{
	check_attack();
	if (isAttacking())
	{
		updateAttack();
	}
	else
	{
		if (_cd_attack.isTicking() && a_playerInRange())
			_state = IDLE;
		else
		{
			_state = WALK;
			followAPlayer();
		}
	}
}

sf::RectangleShape* Boss::getAttackRect()
{
	return &_attack_rect;
}
