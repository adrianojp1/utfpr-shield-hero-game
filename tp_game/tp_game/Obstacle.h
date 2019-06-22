#pragma once

//======================================================================================================================================//
// === Classes Headers === //
#include "Tile.h" //Base class

//======================================================================================================================================//
// === Derived classes from this === //
// Weak_Block
// Static_Spike

//======================================================================================================================================//
// === Obstacle Class === //
class Obstacle : public Tile
{
protected:
	Timer _cd_action; //Weak_Block & Dynamic Spike


public:
	//================================================================//
	// ========== Constructors ========== //
	Obstacle(const sf::Vector2f initPosition, const int id);
	Obstacle();

	// ========== Destructors ========== //
	virtual ~Obstacle();

	//================================================================//
	// ========== Initializers ========== //
	virtual void initialize_animator() = 0;

	//================================================================//
	// ========== Loop methods ========== //
	virtual void execute(const float deltaTime);

	//================================================================//
	// ========== Action ========== //
	virtual void updateAction(const float deltaTime) = 0;
	//virtual void updatePosition(const float deltaTime); //Dynamic Spike

};
