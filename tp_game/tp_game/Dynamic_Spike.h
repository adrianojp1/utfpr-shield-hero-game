#pragma once

//======================================================================================================================================//
// === Classes Headers === //
#include "Static_Spike.h" //Base class

//======================================================================================================================================//
// === Dynamic_Spike Class === //

class Dynamic_Spike : public Static_Spike
{
private:

public:
	//================================================================//
	// ========== Constructors ========== //
	Dynamic_Spike(const sf::Vector2f initPosition, const int id);
	Dynamic_Spike();

	// ========== Destructors ========== //
	~Dynamic_Spike();

	//================================================================//
	// ========== Initializers ========== //
	virtual void initialize_animator();

private:
	// ========== execute submethods ========== //
	void updateAction(const float deltaTime);
	//void updatePosition(const float deltaTime);
};

