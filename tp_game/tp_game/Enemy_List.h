#pragma once
//======================================================================================================================================//
// === Classes Headers === //
#include "Enemy.h"

//======================================================================================================================================//
// === Enemy_List Class === //
class Enemy_List
{
private:
	std::list<Enemy*> enemy_list;
public:
	//================================================================//
// ========== Constructors ========== //
	Enemy_List();
	// ========== Destructors ========== //
	virtual ~Enemy_List();

	typedef std::list<Enemy*>::iterator iterator;

	iterator begin();
	iterator end();

	void clear();
	void includeEnemy(Enemy* pe);
	void removeEnemy(Enemy* pe);
	void execute_enemies(const float deltaTime);
	void draw_enemies();
};

