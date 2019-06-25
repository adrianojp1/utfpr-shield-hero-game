#include "stdafx.h"
#include "Boss.h"

Boss::Boss(const sf::Vector2f initPosition)
{
}

Boss::Boss()
{
}

Boss::~Boss()
{
}

void Boss::initialize_animator()
{
	_animator = new Animator(this);

	*_animator << new Animation(gMng::boss_idle_texture, 4, 150.0f, 2);
	*_animator << new Animation(gMng::boss_walk_texture, 6, 150.0f, 2);
	*_animator << new Animation(gMng::boss_atk_texture, 3, 100.0f, 2);
}

void Boss::attack()
{
}

void Boss::updateAction(const float deltaTime)
{
}
