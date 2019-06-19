#pragma once
//======================================================================================================================================//
// === Classes Headers === //
#include "Abstract_Entity.h"

//======================================================================================================================================//
// === Derived classes from this === //
// Character
// Menu

//======================================================================================================================================//
// === Entity Class === //
class Entity : public Abstract_Entity
{
protected:
	// ========= Visual Members ========= //
	Animator *_animator;
	bool _facingRight; //Bool for the side direction

	// ========= Motion Members ========= //
	sf::RectangleShape *_current_collider; //Pointer for current collider
	float _speed;
	sf::Vector2f _velocity;

public:
	//================================================================//
	// ========== Constructors ========== //
	Entity(const sf::Vector2f initPosition, const bool active = false, const int id = -1);
	Entity();
	// ========== Destructors ========== //
	virtual ~Entity();

	//================================================================//
	// ========== Initializers ========== //
	virtual void initialize_Collider(sf::RectangleShape *&pCollider, sf::Vector2f spriteSize); //Initialize a specific collider
	virtual void initialize_animator() = 0;

	//================================================================//
	// ========== Loop methods ========== //
	virtual void execute(const float deltaTime) = 0;
	virtual void draw() = 0;

	//================================================================//
	// ========== Motion ========== //
	void move(const float dx, const float dy);
	virtual void move(const sf::Vector2f offset);
	virtual void onCollision(const sf::Vector2f collisionDirection);

	//================================================================//
	// ========== Sets & Gets ========== //
	// _speed
	virtual void setSpeed(const float speed);
	virtual float getSpeed() const;
	// _collider
	virtual sf::RectangleShape *getCollider() const;
	// _facingRight
	virtual bool isFacingRight() const;
};
