#pragma once

//======================================================================================================================================//
// === Classes Headers === //
#include "Enemy.h"

//======================================================================================================================================//
// === Orc Class === //
class Orc : public Enemy
{
private:

public:
	//================================================================//
	// ========== Constructors ========== //
	Orc(const sf::Vector2f initPosition);
	Orc();
	// ========== Destructors ========== //
	~Orc();

	//================================================================//
	// ========== Initializers ========== //
	void initialize_animator(); //Initializes all the animators

	//================================================================//
	// ========== Motion ========== //
	void attack();
	void colliding_onLeft();
	void colliding_onRight();

	//================================================================//
	// ========== State checkers ========== //
	//bool isAttacking() const;
private:
	// ========== execute submethods ========== //
	void updateAction(const float deltaTime);
};

