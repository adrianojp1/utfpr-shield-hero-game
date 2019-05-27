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
	// ========= Visual Members ========= //
	//Animator* _current_animator; //Pointer for current animator
	//bool _facingRight; //Bool for the side direction

	// ========= Motion Members ========= //
	//sf::RectangleShape* _current_collider; //Pointer for current collider

	//float _speed; //Horizontal walking speed
	float _jumpHeight;
	//sf::Vector2f _position;
	//sf::Vector2f _velocity;

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
	virtual void initialize_Collider(sf::RectangleShape*& pCollider, const sf::Vector2f size); //Initialize a specific collider

	//================================================================//
	// ========== Loop methods ========== //
	virtual void execute(const float deltaTime) = 0;
	virtual void draw(MyWindow* window) const = 0;

	//================================================================//
	// ========== Motion ========== //
	//virtual void move(const float dx, const float dy);
	//virtual void move(const sf::Vector2f offset);
	virtual void onCollision(const sf::Vector2f collisionDirection);

	//================================================================//
	// ========== Sets & Gets ========== //
	// _jumpHeight
	virtual void setJumpHeight(const float jumpHeight);
	virtual float getJumpHeight() const;
	/* All virtuals
	// _speed
	virtual void setSpeed(const float speed);
	virtual float getSpeed() const;
	// _position
	virtual void setPosition(const sf::Vector2f position);
	virtual sf::Vector2f getPosition() const;
	// _collider
	virtual sf::RectangleShape* getCollider() const;
	*/

protected:
	// ========== execute submethods ========== //
	virtual void updateAction(const float deltaTime) = 0;
	virtual void updateAnimation(const float deltaTime) = 0;
	virtual bool isWalking(const float HorizontalMovement) const;

};
