#pragma once

//======================================================================================================================================//
// === Classes Headers === //
#include "Entity.h" //Base class

//======================================================================================================================================//
// === Block Class === //
class Block : public Entity
{
private:
	// ========= Motion Members ========= //
	sf::RectangleShape* _collider;

public:
	//================================================================//
	// ========== Constructors ========== //
	Block(const sf::Vector2f initPosition, const int id = 2);
	Block();
	// ========== Destructors ========== //
	virtual ~Block();

	//================================================================//
	// ========== Initializers ========== //
	void initialize_animator();

	//================================================================//
	// ========== Loop methods ========== //
	virtual void execute(const float deltaTime);
	virtual void draw();

	//================================================================//
	//======================== Static Consts =========================//
	static const sf::Vector2f size;
};