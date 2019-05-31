#pragma once

//======================================================================================================================================//
// === Classes Headers === //
#include "Entity.h"		//Base class

//======================================================================================================================================//
// === Derived classes from this === //
// Player
// Enemy

//======================================================================================================================================//
// === Character Class === //
class Character : public Entity
{
protected:
	// ========= Visual Members ========= //
	Animator* _animator;
	// ========= Motion Members ========= //
	//Colliders
	sf::RectangleShape* _idle_collider; //Idle
	sf::RectangleShape* _walk_collider; //Walking
	sf::RectangleShape* _combat_collider; //Defense
	sf::RectangleShape* _death_collider; //Death

	// ========= Motion Members ========= //
	float _jumpHeight;

	// ========= State control members ========= //
	bool _canJump;

	int _state;
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

	//================================================================//
	// ========== States ========== //
	virtual void updateState();
	virtual void setIdle();
	virtual void setWalk();
	virtual void setDeath();
	virtual void setCombat();
protected:
	// ========== execute submethods ========== //
	virtual void updateAction(const float deltaTime) = 0;
	virtual bool isWalking(const float HorizontalMovement) const;

	//================================================================//
	//======================== Static Consts =========================//
	//States
	static const int IDLE;
	static const int WALK;
	static const int DEATH;
	static const int COMBAT;
};

typedef Character Charc;