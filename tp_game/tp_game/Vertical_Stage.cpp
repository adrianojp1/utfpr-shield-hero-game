#include "stdafx.h"
#include "Vertical_Stage.h"

Vertical_Stage::Vertical_Stage(const int nPlayers) : Stage(2, nPlayers)
{
	initializeLevels(this, 5);
	_vLevels[4]->spawnBoss({ 800.0f, 600.0f });
}

Vertical_Stage::Vertical_Stage() : Stage(2, 1)
{
}

Vertical_Stage::~Vertical_Stage()
{
}

Enemy* Vertical_Stage::get_an_enemy(sf::Vector2f pos)
{
	Enemy* pEnemy = NULL;

	switch (rand() % 2)
	{
	case 0:
		pEnemy = new Orc(pos);
		break;

	case 1:
		pEnemy = new Black_Skeleton(pos);
		break;

	default:
		break;
	}
	return pEnemy;
}

Obstacle* Vertical_Stage::get_spike(sf::Vector2f pos)
{
	return new Dynamic_Spike(pos);
}


