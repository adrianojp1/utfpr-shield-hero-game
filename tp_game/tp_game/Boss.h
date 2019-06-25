#pragma once
// === Classes Headers === //
#include "Enemy.h"

//======================================================================================================================================//
// === Boss Class === //
class Boss :
	public Enemy
{
private:

public:
	//================================================================//
	// ========== Constructors ========== //
	Boss(const sf::Vector2f initPosition);
	Boss();
	// ========== Destructors ========== //
	~Boss();

	//================================================================//
	// ========== Initializers ========== //
	void initialize_animator(); //Initializes all the animators

	virtual void attack();

	virtual void updateAction(const float deltaTime);
};