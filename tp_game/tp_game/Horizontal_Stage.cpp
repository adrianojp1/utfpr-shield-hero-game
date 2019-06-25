#include "stdafx.h"
#include "Horizontal_Stage.h"

Horizontal_Stage::Horizontal_Stage(const int nPlayers) : Stage(1, nPlayers)
{
	initializeLevels(this, 5);
}

Horizontal_Stage::Horizontal_Stage() : Stage(1, 1)
{
}

Horizontal_Stage::~Horizontal_Stage()
{
}

Enemy* Horizontal_Stage::get_an_enemy(sf::Vector2f pos)
{
	Enemy* pEnemy = NULL;

	switch (rand() % 2)
	{
	case 0:
		pEnemy = new Orc(pos);
		break;

	case 1:
		pEnemy = new White_Skeleton(pos);
		break;

	default:
		break;
	}
	return pEnemy;
}

Obstacle* Horizontal_Stage::get_spike(sf::Vector2f pos)
{
	return new Static_Spike(pos);
}
