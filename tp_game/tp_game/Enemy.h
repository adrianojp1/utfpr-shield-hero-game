#pragma once

//======================================================================================================================================//
// === Classes Headers === //
#include "Character.h" //Base class

//======================================================================================================================================//
// === Enemy Class === //
class Enemy : public Character
{
private:
	// ========= State control members ========= //
	//bool _attacking;

public:
	//================================================================//
	// ========== Constructors ========== //
	Enemy(const sf::Vector2f initPosition);
	Enemy();
	// ========== Destructors ========== //
	~Enemy();

	//================================================================//
	// ========== Initializers ========== //
	void initialize_animator(); //Initializes all the animators

	void initialize_AllColliders();													   //Initializes all the colliders

	//================================================================//
	// ========== Loop methods ========== //
	void execute(const float deltaTime);
	void draw() const;

private :
	// ========== execute submethods ========== //
	void updateAction(const float deltaTime);
	//void updateAnimation(const float deltaTime);
	//virtual bool isWalking(const float HorizontalMovement) const;
};
