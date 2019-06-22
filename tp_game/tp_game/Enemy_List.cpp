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
// === Animator methods === //
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
	enemy_list.push_back(pe);
}

void Enemy_List::removeEnemy(Enemy* pe)
{
	enemy_list.remove(pe);
}

void Enemy_List::draw_enemies()
{
	for (Enemy* pEn : *this)
	{
		pEn->draw();
	}
}

void Enemy_List::mngCollision_player(Player* pPlayer)
{
	if (pPlayer && pPlayer->isVulnerable())
	{
		cMng* collMng = Collision_Manager::getInstance();

		sf::Vector2f intersection;
		sf::Vector2f collisionDirection;

		for (Enemy* pEnemy : *this)
		{
			if (collMng->check_collision(static_cast<Entity*>(pPlayer), static_cast<Entity*>(pEnemy), &intersection, &collisionDirection))
			{
				if (pPlayer->isDefendingInFront(collisionDirection))
				{
					collisionDirection = -collisionDirection;
					collMng->push_entities(static_cast<Entity*>(pEnemy), static_cast<Entity*>(pPlayer), &intersection, &collisionDirection, 0.0f);
					pEnemy->onCollision(collisionDirection);
				}
				else
				{
					pPlayer->takeDmg(pEnemy->getCollDmg());
				}
			}
		}
	}
}
