#pragma once

//======================================================================================================================================//
// === Classes Headers === //
#include "Entity.h"		//Base class

//======================================================================================================================================//
// === Classes Declaration === //

//======================================================================================================================================//
// === Derived classes from this === //
// Player
// Enemy

//======================================================================================================================================//
// === Character Class === //
class Character : public Entity
{
protected:
	// ========= Motion Members ========= //
	float _jumpHeight;

	// ========= State control members ========= //
	bool _canJump;

public:
	//================================================================//
	// ========== Constructors ========== //
	Character(const sf::Vector2f initPosition);
	Character();
	// ========== Destructors ========== //
	virtual ~Character();

	//================================================================//
	// ========== Initializers ========== //

	//================================================================//
	// ========== Loop methods ========== //
	virtual void execute(const float deltaTime) = 0;
	virtual void draw() const = 0;

	//================================================================//
	// ========== Motion ========== //
	virtual void onCollision(const sf::Vector2f collisionDirection);

	//================================================================//
	// ========== Sets & Gets ========== //
	// _jumpHeight
	virtual void setJumpHeight(const float jumpHeight);
	virtual float getJumpHeight() const;

protected:
	// ========== execute submethods ========== //
	virtual void updateAction(const float deltaTime) = 0;
	virtual void updateAnimation(const float deltaTime) = 0;
	virtual bool isWalking(const float HorizontalMovement) const;

};
