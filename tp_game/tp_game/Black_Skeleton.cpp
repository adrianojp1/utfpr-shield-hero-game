#include "stdafx.h"
#include "Black_Skeleton.h"

Black_Skeleton::Black_Skeleton(const sf::Vector2f initPosition) :
	Skeleton(initPosition)
{
	initialize_animator();
	initialize_AllColliders();
}

Black_Skeleton::Black_Skeleton() :
	Skeleton()
{
}

Black_Skeleton::~Black_Skeleton()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	if (_animator)
		delete _animator;
}

void Black_Skeleton::initialize_animator()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	_animator = new Animator(static_cast<Entity*>(this));

	*_animator << new Animation(gMng::black_skeleton_idle_texture, 1, 0.0f, 2);
	*_animator << new Animation(gMng::black_skeleton_walk_texture, 4, 0.250f, 2);
	*_animator << new Animation(gMng::black_skeleton_die_texture, 3, 0.250f, 2);
	*_animator << new Animation(gMng::black_skeleton_atk_texture, 3, 0.120f, 2);
}

int Black_Skeleton::getProj_id()
{
	return 1;
}