#pragma once
//======================================================================================================================================//
// === Classes Headers === //
#include "Stage.h"
#include "BlackSkeleton.h"
#include "Dynamic_Spike.h"
#include "Orc.h"

//======================================================================================================================================//
// === Vertical_Stage Class === //
class Vertical_Stage :
	public Stage
{
private:

public:
	Vertical_Stage(const int nPlayers);
	Vertical_Stage();
	~Vertical_Stage();

	virtual Enemy* get_an_enemy(sf::Vector2f pos);
	virtual Obstacle* get_spike(sf::Vector2f pos);
};

