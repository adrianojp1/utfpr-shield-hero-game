#include "stdafx.h"
#include "Skeleton.h"

Skeleton::Skeleton(const sf::Vector2f initPosition) : 
	Enemy(initPosition)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	_cd_attack.setTotalTime(1.0f);
	_speed = 0.0f;
	_canAttack = true;
	_velocity.x = _speed;
	_facingRight = false;
}

Skeleton::Skeleton() : 
	Enemy()
{
	_speed = 0.0f;
}

Skeleton::~Skeleton()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

}

//Define attack of both Skeletons
void Skeleton::attack()
{

}
