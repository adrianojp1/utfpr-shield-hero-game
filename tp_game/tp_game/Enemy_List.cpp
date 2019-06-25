//======================================================================================================================================//
// === Pre-Compiled Header === //
#include "stdafx.h"

//======================================================================================================================================//
// === This Class Header === //
#include "Enemy_List.h"

//======================================================================================================================================//
// === Classes headers for definition === //
#include "Player.h"

//======================================================================================================================================//
// === Enemy_List methods === //
Enemy_List::Enemy_List()
{
}

Enemy_List::~Enemy_List()
{
	clear();
}

Enemy_List::iterator Enemy_List::begin()
{
	return enemy_list.begin();
}

Enemy_List::iterator Enemy_List::end()
{
	return enemy_list.end();
}

void Enemy_List::clear()
{
	enemy_list.clear();
}

void Enemy_List::includeEnemy(Enemy* pe)
{
	if(pe)
		enemy_list.push_back(pe);
}

void Enemy_List::removeEnemy(Enemy* pe)
{
	enemy_list.remove(pe);
}

void Enemy_List::execute_enemies(const float deltaTime)
{
	for (Enemy* pEne : *this)
	{
		pEne->execute(deltaTime);
	}
}

void Enemy_List::update_drawables()
{
	for (Enemy* pE : *this)
	{
		pE->updateAnime_n_Collider();
	}
}

void Enemy_List::draw_enemies()
{
	for (Enemy* pEn : *this)
	{
		pEn->draw();
	}
}