#pragma once

//======================================================================================================================================//
// === Classes Headers === //
#include "Enemy.h"

//======================================================================================================================================//
// === Skeleton Class === //
class Skeleton : public Enemy
{
protected:

public:
	//================================================================//
	// ========== Constructors ========== //
	Skeleton(const sf::Vector2f initPosition);
	Skeleton();
	// ========== Destructors ========== //
	~Skeleton();

	//================================================================//
	// ========== Initializers ========== //
	virtual void initialize_animator() = 0; //Initializes all the animators
	//virtual void initialize_overView();

	//================================================================//
	// ========== Motion ========== //
	virtual void attack(); //Attack of both skeletons
	

	//================================================================//
	// ========== State checkers ========== //
	//virtual bool player_on_overview() const;
private:
	// ========== execute submethods ========== //
	virtual void updateAction(const float deltaTime) = 0;
}
;

