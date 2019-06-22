#pragma once

//======================================================================================================================================//
// === Classes Headers === //
#include "Obstacle.h" //Base class

//======================================================================================================================================//
// === Derived classes from this === //
// Dynamic Spike

//======================================================================================================================================//
// === Static_Spike Class === //
class Static_Spike : public Obstacle
{
private:


public:
	//================================================================//
	// ========== Constructors ========== //
	Static_Spike(const sf::Vector2f initPosition, const int id);
	Static_Spike();

	// ========== Destructors ========== //
	~Static_Spike();

	//================================================================//
	// ========== Initializers ========== //
	virtual void initialize_animator();

private:
	// ========== execute submethods ========== //
	void updateAction(const float deltaTime);
};


