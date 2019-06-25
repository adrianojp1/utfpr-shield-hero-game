#pragma once

//======================================================================================================================================//
// === Classes Headers === //
#include "Static_Spike.h" //Base class

//======================================================================================================================================//
// === Dynamic_Spike Class === //

class Dynamic_Spike : public Static_Spike
{
private:
	sf::Vector2f _hidden_position;
	
public:
	//================================================================//
	// ========== Constructors ========== //
	Dynamic_Spike(const sf::Vector2f initPosition, const int id = 36);
	Dynamic_Spike();

	// ========== Destructors ========== //
	~Dynamic_Spike();

	//================================================================//
	// ========== Initializers ========== //

private:
	// ========== execute submethods ========== //
	void updateAction(const float deltaTime);
};

