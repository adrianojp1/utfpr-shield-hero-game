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
	~Skeleton();

	//================================================================//
	// ========== Initializers ========== //
	void initialize_animator(); //Initializes all the animators

	//================================================================//
	// ========== Motion ========== //
	void attack();
	void turnArround();

	//================================================================//
	// ========== State checkers ========== //
	bool isAttacking() const;
private:
	// ========== execute submethods ========== //
	virtual void updateAction(const float deltaTime);
}
;

