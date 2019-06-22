#include "stdafx.h"
#include "WhiteSkeleton.h"
#include "Projectile.h"

WhiteSkeleton::WhiteSkeleton(const sf::Vector2f initPosition):
	Skeleton(initPosition)
{
	initialize_animator();
	initialize_AllColliders();
}

WhiteSkeleton::WhiteSkeleton() : 
	Skeleton()
{
}

WhiteSkeleton::~WhiteSkeleton()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	if (_animator)
		delete _animator;
}

void WhiteSkeleton::initialize_animator()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	_animator = new Animator(static_cast<Entity*>(this));

	*_animator << new Animation(gMng::white_skeleton_idle_texture, 1, 0.0f);
	*_animator << new Animation(gMng::white_skeleton_walk_texture, 4, 0.250f);
	*_animator << new Animation(gMng::white_skeleton_die_texture, 3, 0.250f);
	*_animator << new Animation(gMng::white_skeleton_atk_texture, 3, 0.200f);
}

void WhiteSkeleton::updateAction(const float deltaTime)
{
	if (_facingRight)
		_velocity.x = _speed;
	else
		_velocity.x = -_speed;
}
