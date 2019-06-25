#pragma once

//======================================================================================================================================//
// === Classes Headers === //
#include "Enemy.h"
#include "Projectile_List.h"

//======================================================================================================================================//
// === Skeleton Class === //
class Skeleton : public Enemy
{
private:
	sf::Vector2f _proj_offset;

public:
	//================================================================//
	// ========== Constructors ========== //
	Skeleton(const sf::Vector2f initPosition);
	Skeleton();
	// ========== Destructors ========== //
	virtual ~Skeleton();

	//================================================================//
	// ========== Initializers ========== //
	virtual void initialize_animator() = 0; //Initializes all the animators

	//================================================================//
	// ========== Motion ========== //
	virtual void attack(); //Attack of both skeletons

	//================================================================//
	// ========== State checkers ========== //
	//virtual bool player_on_overview() const;
private:
	//bool isAttacking() const;
protected:
	// ========== execute submethods ========== //
	virtual void updateAction(const float deltaTime) = 0;
};
