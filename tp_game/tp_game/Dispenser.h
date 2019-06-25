#pragma once

//======================================================================================================================================//
// === Classes Headers === //
#include "Obstacle.h" //Base class
#include "Projectile_List.h"

//======================================================================================================================================//
// === Dispenser Class === //
class Dispenser : public Obstacle
{
private:
	sf::Vector2f _proj_initPos;
public:
	//================================================================//
	// ========== Constructors ========== //
	Dispenser(const sf::Vector2f initPosition, const bool facingRight = true, const int id = 15);
	Dispenser();

	// ========== Destructors ========== //
	virtual ~Dispenser();

	void spit_ball();
private:
	// ========== execute submethods ========== //
	void updateAction(const float deltaTime);
};

