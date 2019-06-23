#pragma once

//======================================================================================================================================//
// === Classes Headers === //
#include "Obstacle.h" //Base class

//======================================================================================================================================//
// === Weak_Block Class === //
class Weak_Block : public Obstacle
{
private:


public:
	//================================================================//
	// ========== Constructors ========== //
	Weak_Block(const sf::Vector2f initPosition, const int id);
	Weak_Block();

	// ========== Destructors ========== //
	~Weak_Block();

	//================================================================//
	// ========== Initializers ========== //
	virtual void initialize_animator();

private:
	// ========== execute submethods ========== //
	void updateAction(const float deltaTime); //tremer e sumir.
};

