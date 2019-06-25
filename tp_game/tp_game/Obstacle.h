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
	bool _triggered;
	int _collisionDamage;
public:
	//================================================================//
	// ========== Constructors ========== //
	Obstacle(const sf::Vector2f initPosition, const int id);
	Obstacle();

	// ========== Destructors ========== //
	~Obstacle();

	//================================================================//
	// ========== Initializers ========== //

	//================================================================//
	// ========== Loop methods ========== //
	virtual void execute(const float deltaTime);

	virtual void decreaseTimers();

	virtual void setCollDmg(const int collDmg);
	virtual const int getCollDmg() const;

	//================================================================//
	// ========== Action ========== //
	virtual void updateAction(const float deltaTime) = 0;

};
