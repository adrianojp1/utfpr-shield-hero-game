#pragma once
//======================================================================================================================================//
// === Classes Headers === //
#include "Obstacle.h"

//======================================================================================================================================//
// === Obstacle_List Class === //
class Obstacle_List
{
private:
	std::deque<Obstacle*> _obst_deque;
public:
	Obstacle_List();
	virtual ~Obstacle_List();

	typedef std::deque<Obstacle*>::iterator iterator;

	iterator begin();
	iterator end();

	void clear();
	void includeObstacle(Obstacle* pO);
	void execute_obstacles(const float deltaTime);
	void update_drawables();
	void draw_obstacles();
	void delete_obstacles();
};

