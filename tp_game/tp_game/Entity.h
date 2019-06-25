#pragma once
//======================================================================================================================================//
// === Classes Headers === //
#include "Abstract_Entity.h"

//======================================================================================================================================//
// === Derived classes from this === //
// Character
// Tile


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

	// ========= Colliding bools ========= //
	bool _coll_onTop;
	bool _coll_onBot;
	bool _coll_onLeft;
	bool _coll_onRight;

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
	virtual void draw();

	//================================================================//
	// ========== Motion ========== //
	void move(const float dx, const float dy);
	virtual void move(const sf::Vector2f offset);
	virtual void onCollision(const sf::Vector2f collisionDirection);
	virtual void checkColls();
	virtual void resetColls();
	virtual void colliding_onLeft();
	virtual void colliding_onRight();
	virtual void colliding_onBottom();
	virtual void colliding_onTop();
	virtual void updatePosition(const float deltaTime);
	virtual void updateAnime_n_Collider();
	virtual void updateAnime();
	virtual void updateCollider();
	virtual void decreaseTimers();
	virtual void turnArround();
	virtual void moveFoward();
	virtual void moveToLeft(const float speedMultiplier = 1.0f);
	virtual void moveToRight(const float speedMultiplier = 1.0f);

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
