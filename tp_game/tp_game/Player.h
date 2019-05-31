#pragma once

//======================================================================================================================================//
// === Classes Headers === //
#include "Character.h" //Base class

//======================================================================================================================================//
// === Player Class === //
class Player : public Character
{
private:
	// ========= State control members ========= //
	bool _defCounterUp;

	Timer _defCounterTimer; //Timer for the defense counter

public:
	//================================================================//
	// ========== Constructors ========== //
	Player(const sf::Vector2f initPosition);
	Player();
	// ========== Destructors ========== //
	virtual ~Player();

	//================================================================//
	// ========== Initializers ========== //
	void initialize_animator(); //Initializes all the animators

	void initialize_AllColliders(); //Initializes all the colliders

	//================================================================//
	// ========== Loop methods ========== //
	void execute(const float deltaTime);
	void draw() const;

	//================================================================//
	// ========== State checkers ========== //
	bool isDefending() const;
	bool isCounterUp() const;
	bool isDefending_with_Counter() const;

	//================================================================//
	// ========== States ========== //
	//virtual void setDeath();
	virtual void setCombat();
private:
	// ========== Control keys methods ========== //
	bool leftIsKeyPressed() const;
	bool rightIsKeyPressed() const;
	bool jumpKeyPressed() const;
	bool anyMoveKeyPressed() const;
	bool defendKeyPressed() const;

	// ========== execute submethods ========== //
	void updateAction(const float deltaTime);
	//void updateAnimation(const float deltaTime);
	//virtual bool isWalking(const float HorizontalMovement) const;

}; // end Player