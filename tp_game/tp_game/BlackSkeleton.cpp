#include "stdafx.h"
#include "BlackSkeleton.h"

BlackSkeleton::BlackSkeleton(const sf::Vector2f initPosition) :
	Skeleton(initPosition)
{
	initialize_animator();
	initialize_AllColliders();
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

	*_animator << new Animation(gMng::black_skeleton_idle_Sp_Fp, 1, 0.0f);
	*_animator << new Animation(gMng::black_skeleton_walk_Sp_Fp, 4, 0.250f);
	*_animator << new Animation(gMng::black_skeleton_die_Sp_Fp, 3, 0.250f);
	*_animator << new Animation(gMng::black_skeleton_atk_Sp_Fp, 3, 0.200f);
	*_animator << new Animation(gMng::black_skeleton_proj_Sp_Fp, 1, 0.0f);
}

void BlackSkeleton::updateAction(const float deltaTime)
{
}
