#include "stdafx.h"
#include "Obstacle_List.h"

Obstacle_List::Obstacle_List()
{
}

Obstacle_List::~Obstacle_List()
{
	clear();
}

Obstacle_List::iterator Obstacle_List::begin()
{
	return _obst_deque.begin();
}

Obstacle_List::iterator Obstacle_List::end()
{
	return _obst_deque.end();
}

void Obstacle_List::clear()
{
	_obst_deque.clear();
}

void Obstacle_List::includeObstacle(Obstacle* pO)
{
	if(pO)
		_obst_deque.push_back(pO);
}

void Obstacle_List::execute_obstacles(const float deltaTime)
{
	for (Obstacle* pO : *this)
	{
		pO->execute(deltaTime);
	}
}

void Obstacle_List::update_drawables()
{
	for (Obstacle* pO : *this)
	{
		pO->updateAnime_n_Collider();
	}
}

void Obstacle_List::draw_obstacles()
{
	for (Obstacle* pO : *this)
	{
		pO->draw();
	}
}
