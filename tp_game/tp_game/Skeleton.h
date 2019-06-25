#pragma once

//======================================================================================================================================//
// === Classes Headers === //
#include "Enemy.h"

//======================================================================================================================================//
// === Skeleton Class === //
class Skeleton : public Enemy
{
private:

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
	//bool isAttacking() const;
protected:
	// ========== execute submethods ========== //
	virtual void updateAction(const float deltaTime) = 0;
}
;

