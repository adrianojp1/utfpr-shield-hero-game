#include "stdafx.h"
#include "Boss.h"

Boss::Boss(const sf::Vector2f initPosition) : Enemy(initPosition)
{
	initialize_animator();
	initialize_AllColliders();
	_speed = 200.0f;
	_state = IDLE;
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

	*_animator << new Animation(gMng::boss_idle_texture, 4, 150.0f, 2);
	*_animator << new Animation(gMng::boss_walk_texture, 6, 150.0f, 2);
	*_animator << new Animation(gMng::boss_atk_texture, 3, 100.0f, 2);
	*_animator << new Animation(gMng::boss_atk_texture, 3, 100.0f, 2);
}

void Boss::attack()
{
}

bool Boss::principalFrameOfAttack()
{
	return (*_animator)[2]->getFrameCounter() == (*_animator)[2]->getnFrames() - 2;
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

	cMng* collMng = cMng::getInstance();
	if (collMng->intersects(_pPlayer1, &_attack_rect))
		_pPlayer1->takeDmg(_attackDamage);
	if (_pPlayer2 && collMng->intersects(_pPlayer2, &_attack_rect))
		_pPlayer2->takeDmg(_attackDamage);
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
		_state = IDLE;
		/*
		_state = WALK;

		int chanceToTurn = 1;//%
		bool decidedToTurn = false;
		if (rand() % 101 < chanceToTurn + 1)
			bool decidedToTurn = true;

		if (!_floor_foward || decidedToTurn)
		{
			turnArround();
		}
		_floor_foward = false;
		moveFoward();*/
	}
}
