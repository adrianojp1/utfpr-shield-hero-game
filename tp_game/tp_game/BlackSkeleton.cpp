#include "stdafx.h"
#include "Black_Skeleton.h"

BlackSkeleton::BlackSkeleton(const sf::Vector2f initPosition) :
	Skeleton(initPosition)
{
	initialize_animator();
	initialize_AllColliders();
	_cd_attack.setTotalTime(2.0f);
	_proj_speed = 300.0f;
}

BlackSkeleton::BlackSkeleton() :
	Skeleton()
{
}

BlackSkeleton::~BlackSkeleton()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	if (_animator)
		delete _animator;
}

void BlackSkeleton::initialize_animator()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	_animator = new Animator(static_cast<Entity*>(this));

	*_animator << new Animation(gMng::black_skeleton_idle_texture, 1, 0.0f, 2);
	*_animator << new Animation(gMng::black_skeleton_walk_texture, 4, 0.250f, 2);
	*_animator << new Animation(gMng::black_skeleton_die_texture, 3, 0.250f, 2);
	*_animator << new Animation(gMng::black_skeleton_atk_texture, 3, 0.120f, 2);
}

int BlackSkeleton::getProj_id()
{
	return 1;
}