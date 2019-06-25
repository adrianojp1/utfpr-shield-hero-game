//======================================================================================================================================//
// === Pre-Compiled Header === //
#include "stdafx.h"

//======================================================================================================================================//
// === This Class Header === //
#include "Collision_Manager.h"

//======================================================================================================================================//
// === Classes headers for definition === //
#include "Entity.h"
#include "Player.h"
#include "Enemy.h"
#include "Obstacle.h"
#include "Tile.h"
#include "Projectile.h"

#include "Enemy_List.h"
#include "Tile_List.h"
#include "Obstacle_List.h"
#include "Projectile_List.h"

//======================================================================================================================================//
// === Static initializations === //
Collision_Manager* Collision_Manager::_instance = NULL;

//======================================================================================================================================//
// === Collision_Manager methods === //
Collision_Manager::Collision_Manager()
{
}

Collision_Manager::~Collision_Manager()
{
}

Collision_Manager* Collision_Manager::getInstance()
{
	if (!_instance)
		_instance = new Collision_Manager();
	return _instance;
}

void Collision_Manager::collide(Player* pPlayer, Tile* pTile)
{
	if (pPlayer && pTile)
	{
		sf::Vector2f intersection;
		sf::Vector2f collisionDirection;

		if(check_collision_n_push(static_cast<Entity*>(pPlayer), pTile, &intersection, &collisionDirection, 0.0f))
				pPlayer->onCollision(collisionDirection);
	}
}

void Collision_Manager::collide(Player* pPlayer, Enemy* pEnemy)
{
	if (pPlayer && pEnemy && pEnemy->isActive() && pPlayer->isVulnerable())
	{
		sf::Vector2f intersection;
		sf::Vector2f collisionDirection;

		if (check_collision(static_cast<Entity*>(pPlayer), static_cast<Entity*>(pEnemy), &intersection, &collisionDirection) && 
			pEnemy->isAttacking())
		{
			
		}
	}
}

void Collision_Manager::collide(Player* pPlayer, Obstacle* pObstacle)
{
	if (pPlayer && pObstacle && pPlayer->isVulnerable())
	{
		sf::Vector2f intersection;
		sf::Vector2f collisionDirection;

		if (check_collision(static_cast<Entity*>(pPlayer), static_cast<Entity*>(pObstacle), &intersection, &collisionDirection))
		{
			pPlayer->takeDmg(pObstacle->getCollDmg());
			pObstacle->onCollision(-collisionDirection);
		}
	}
}

void Collision_Manager::collide(Player* pPlayer, Projectile* pProjectile)
{
	if (pPlayer && pProjectile && pProjectile->isActive() && !pProjectile->wasReflected())
	{
		sf::Vector2f intersection;
		sf::Vector2f collisionDirection;

		if (check_collision(static_cast<Entity*>(pPlayer), static_cast<Entity*>(pProjectile), &intersection, &collisionDirection))
		{
			if (pPlayer->isDefendingInFront(collisionDirection))
			{
				if (pPlayer->isCounterUp())
				{
					pProjectile->reflect();
				}
				else
				{
					pProjectile->desactivate();
				}
			}
			else if(pPlayer->isVulnerable())
			{
				pPlayer->takeDmg(pProjectile->getCollDmg());
				pProjectile->desactivate();
			}
		}
	}
}

void Collision_Manager::collide(Enemy* pEnemy, Tile* pTile)
{
	if (pEnemy && pTile)
	{
		sf::Vector2f intersection;
		sf::Vector2f collisionDirection;

		if (!pEnemy->getFloor_foward() && contains(pTile, pEnemy->getFrontEdge()))
			pEnemy->setFloor_foward(true);
		if (check_collision(static_cast<Entity*>(pEnemy), pTile, &intersection, &collisionDirection))
		{
			push_entities(static_cast<Entity*>(pEnemy), pTile, &intersection, &collisionDirection, 0.0f);
			pEnemy->onCollision(collisionDirection);
		}
	}
}

void Collision_Manager::collide(Enemy* pEnemy, Obstacle* pObstacle)
{
	if (pEnemy && pObstacle)
	{
		sf::Vector2f intersection;
		sf::Vector2f collisionDirection;

		if (check_collision(static_cast<Entity*>(pEnemy), pObstacle, &intersection, &collisionDirection))
		{
			push_entities(static_cast<Entity*>(pEnemy), pObstacle, &intersection, &collisionDirection, 0.0f);
			pEnemy->onCollision(collisionDirection);
		}
	}
}

void Collision_Manager::collide(Enemy* pEnemy, Projectile* pProjectile)
{
	if (pEnemy && pProjectile && pEnemy->isActive() && pProjectile->isActive() && pProjectile->wasReflected() && check_collision(pEnemy, pProjectile))
	{
		pEnemy->takeDmg(pProjectile->getCollDmg());
		pProjectile->desactivate();
	}
}

void Collision_Manager::collide(Obstacle* pObstacle, Tile* pTile)
{

}

void Collision_Manager::collide(Player* pPlayer, Tile_List* t_list)
{
	if (pPlayer && t_list)
	{
		for (Tile* pT : *t_list)
		{
			collide(pPlayer, pT);
		}
	}
}

void Collision_Manager::collide(Player* pPlayer, Enemy_List* e_list)
{
	if (pPlayer && pPlayer->isVulnerable() && e_list)
	{
		for (Enemy* pEne : *e_list)
		{
			collide(pPlayer, pEne);
		}
	}
}

void Collision_Manager::collide(Player* pPlayer, Obstacle_List* o_list)
{
	if (pPlayer && pPlayer->isVulnerable() && o_list)
	{
		for (Obstacle* pO : *o_list)
		{
			collide(pPlayer, pO);
		}
	}
}

void Collision_Manager::collide(Player* pPlayer, Projectile_List* p_list)
{
	if (pPlayer && p_list)
	{
		for (Projectile* pP : *p_list)
		{
			collide(pPlayer, pP);
		}
	}
}

void Collision_Manager::collide(Enemy_List* e_list, Tile_List* t_list)
{
	if (t_list && e_list)
	{
		for (Tile* pT : *t_list)
		{
			for (Enemy* pE : *e_list)
			{
				collide(pE, pT);
			}
		}
	}
}

void Collision_Manager::collide(Enemy_List* e_list, Obstacle_List* o_list)
{
	if (o_list && e_list)
	{
		for (Obstacle* pO : *o_list)
		{
			for (Enemy* pE : *e_list)
			{
				collide(pE, pO);
			}
		}
	}
}

void Collision_Manager::collide(Enemy_List* e_list, Projectile_List* p_list)
{
	if (e_list && p_list)
	{
		for (Enemy* pE : *e_list)
			for (Projectile* pP : *p_list)
				collide(pE, pP);
	}
}

void Collision_Manager::collide(Obstacle_List* o_list, Tile_List* t_list)
{
	if (t_list && o_list)
	{
		for (Tile* pT : *t_list)
		{
			for (Obstacle* pO : *o_list)
			{
				collide(pO, pT);
			}
		}
	}
}

bool Collision_Manager::check_collision(Entity* ent1, Entity* ent2)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	sf::Vector2f otherPosition = ent2->getPosition();
	sf::Vector2f otherHalfSize = ent2->getCollider()->getSize() / 2.0f;
	sf::Vector2f thisPosition = ent1->getPosition();
	sf::Vector2f thisHalfSize = ent1->getCollider()->getSize() / 2.0f;

	sf::Vector2f delta = { otherPosition.x - thisPosition.x, otherPosition.y - thisPosition.y };

	sf::Vector2f intersection = { abs(delta.x) - (otherHalfSize.x + thisHalfSize.x),
								 abs(delta.y) - (otherHalfSize.y + thisHalfSize.y) };

	if (intersection.x < 0.0f && intersection.y < 0.0f)
	{
		return true;
	}
	return false;
}

bool Collision_Manager::check_collision(Entity* ent1, Entity* ent2, sf::Vector2f* intersection, sf::Vector2f* coll_direction)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	sf::Vector2f otherPosition = ent2->getPosition();
	sf::Vector2f otherHalfSize = ent2->getCollider()->getSize() / 2.0f;
	sf::Vector2f thisPosition = ent1->getPosition();
	sf::Vector2f thisHalfSize = ent1->getCollider()->getSize() / 2.0f;

	sf::Vector2f delta = { otherPosition.x - thisPosition.x, otherPosition.y - thisPosition.y };

	*intersection = { abs(delta.x) - (otherHalfSize.x + thisHalfSize.x),
					 abs(delta.y) - (otherHalfSize.y + thisHalfSize.y) };

	if (intersection->x < 0.0f && intersection->y < 0.0f)
	{
		if (intersection->x > intersection->y) // = (abs(intersectX) < abs(intersectY))
		{									   // pushing on the X axe
			if (delta.x > 0.0f)
			{
				*coll_direction = sf::Vector2f(1.0f, 0.0f);
			}
			else
			{
				*coll_direction = sf::Vector2f(-1.0f, 0.0f);
			}
		}
		else
		{ // pushing on the Y axe
			if (delta.y > 0.0f)
			{
				*coll_direction = sf::Vector2f(0.0f, 1.0f);
			}
			else
			{
				*coll_direction = sf::Vector2f(0.0f, -1.0f);
			}
		}
		return true;
	}
	return false;
}

void Collision_Manager::push_entities(Entity* ent1, Entity* ent2, sf::Vector2f* intersection, sf::Vector2f* coll_direction, float push)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	push = std::min(std::max(push, 0.0f), 1.0f); // clumping push between 0.0f and 1.0f

	if (intersection->x > intersection->y) // = (abs(intersectX) < abs(intersectY))
	{									   // pushing on the X axe
		if (coll_direction->x > 0.0f)
		{

			ent1->move((intersection->x * (1.0f - push)), 0.0f);
			ent2->move((-intersection->x * push), 0.0f);
		}
		else
		{
			ent1->move((-intersection->x * (1.0f - push)), 0.0f);
			ent2->move((intersection->x * push), 0.0f);
		}
	}
	else
	{ // pushing on the Y axe
		if (coll_direction->y > 0.0f)
		{
			ent1->move(0.0f, (intersection->y * (1.0f - push)));
			ent2->move(0.0f, (-intersection->y * push));
		}
		else
		{
			ent1->move(0.0f, (-intersection->y * (1.0f - push)));
			ent2->move(0.0f, (intersection->y * push));
		}
	}
}

bool Collision_Manager::check_collision_n_push(Entity* ent1, Entity* ent2, sf::Vector2f* intersection, sf::Vector2f* coll_direction, float push)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	if (check_collision(ent1, ent2, intersection, coll_direction))
	{
		push_entities(ent1, ent2, intersection, coll_direction, push);
		return true;
	}
	return false;
}

bool Collision_Manager::contains(Entity* ent, sf::Vector2f point)
{
	sf::Vector2f halfSize = ent->getCollider()->getSize();
	sf::Vector2f pos = ent->getCollider()->getPosition();

	sf::Vector2f inf_lims = pos - halfSize;
	sf::Vector2f sup_lims = pos + halfSize;

	return ((point.x > inf_lims.x) && (point.x < sup_lims.x) && (point.y > inf_lims.y) && (point.y < sup_lims.y)) ? true : false;
}

bool Collision_Manager::intersects(Entity* ent, sf::RectangleShape* rect)
{
	sf::Vector2f otherPosition = rect->getPosition();
	sf::Vector2f otherHalfSize = rect->getSize() / 2.0f;
	sf::Vector2f thisPosition = ent->getPosition();
	sf::Vector2f thisHalfSize = ent->getCollider()->getSize() / 2.0f;

	sf::Vector2f delta = { otherPosition.x - thisPosition.x, otherPosition.y - thisPosition.y };

	sf::Vector2f intersection = { abs(delta.x) - (otherHalfSize.x + thisHalfSize.x),
								 abs(delta.y) - (otherHalfSize.y + thisHalfSize.y) };

	if (intersection.x < 0.0f && intersection.y < 0.0f)
	{
		return true;
	}
	return false;
}
