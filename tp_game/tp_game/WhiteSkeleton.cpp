#include "stdafx.h"
#include "WhiteSkeleton.h"
#include "Projectile.h"

WhiteSkeleton::WhiteSkeleton(const sf::Vector2f initPosition):
	Skeleton(initPosition)
{
	initialize_animator();
	initialize_AllColliders();
	_cd_attack.setTotalTime(3.0f);
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

	*_animator << new Animation(gMng::white_skeleton_idle_texture, 1, 0.0f, 2);
	*_animator << new Animation(gMng::white_skeleton_walk_texture, 4, 0.250f, 2);
	*_animator << new Animation(gMng::white_skeleton_die_texture, 3, 0.250f, 2);
	*_animator << new Animation(gMng::white_skeleton_atk_texture, 3, 0.120f, 2);
}

int WhiteSkeleton::getProj_id()
{
	return 0;
}