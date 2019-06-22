#pragma once
//======================================================================================================================================//
// === Classes Headers === //
#include "Enemy.h"

//======================================================================================================================================//
// === Derived classes from this === //
// Character
// Tile

//======================================================================================================================================//
// === Entity Class === //
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
	void draw_enemies();

	void mngCollision_player(Player* pPlayer);
};

