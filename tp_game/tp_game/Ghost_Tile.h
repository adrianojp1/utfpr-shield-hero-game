#pragma once

//======================================================================================================================================//
// === Classes Headers === //
#include "Obstacle.h" //Base class

//======================================================================================================================================//
// === Ghost_Tile Class === //
class Ghost_Tile : public Obstacle
{
private:
	
public:
	//================================================================//
	// ========== Constructors ========== //
	Ghost_Tile(const sf::Vector2f initPosition, const int id);
	Ghost_Tile();

	// ========== Destructors ========== //
	~Ghost_Tile();

	//================================================================//
	// ========== Initializers ========== //
	virtual void colliding_onTop();
	virtual void activ_ghost();
	virtual void deactiv_ghost();
private:
	// ========== execute submethods ========== //
	void updateAction(const float deltaTime);
};

