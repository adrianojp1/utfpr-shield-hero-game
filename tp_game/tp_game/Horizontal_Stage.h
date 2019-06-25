#pragma once
//======================================================================================================================================//
// === Classes Headers === //
#include "Stage.h"
#include "WhiteSkeleton.h"
#include "Static_Spike.h"
#include "Orc.h"

//======================================================================================================================================//
// === Horizontal_Stage Class === //
class Horizontal_Stage :
	public Stage
{
private:

public:
	Horizontal_Stage(const int nPlayers);
	Horizontal_Stage();
	~Horizontal_Stage();

	virtual Enemy* get_an_enemy(sf::Vector2f pos);
	virtual Obstacle* get_spike(sf::Vector2f pos);
};

