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
	static Projectile_List* _level_proj_list;
	sf::Vector2f _proj_initPos;
public:
	//================================================================//
	// ========== Constructors ========== //
	Dispenser(const sf::Vector2f initPosition, const bool facingRight = true, const int id = 15);
	Dispenser();

	// ========== Destructors ========== //
	virtual ~Dispenser();

	static void setProjList(Projectile_List* projList);
	static Projectile_List* getProjList();

	void spit_ball();
private:
	// ========== execute submethods ========== //
	void updateAction(const float deltaTime);
};

