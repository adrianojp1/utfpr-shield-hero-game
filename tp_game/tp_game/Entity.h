#pragma once
//======================================================================================================================================//
// === Classes Headers === //
#include "Animator.h"		//Animations
#include "Timer.h"			//Timing effects
#include "Graphical_Manager.h"		//Drawer

//======================================================================================================================================//
// === Derived classes from this === //
// Character
// Menu

//======================================================================================================================================//
// === Entity Class === //
class Entity
{
protected:
	// ========= Visual Members ========= //
	Animator* _current_animator; //Pointer for current animator
	bool _facingRight; //Bool for the side direction

	// ========= Motion Members ========= //
	sf::RectangleShape* _current_collider; //Pointer for current collider

	float _speed;
	sf::Vector2f _position;
	sf::Vector2f _velocity;

	bool _active;

	static Graphical_Manager* _pGraphMng;
public:
	//================================================================//
	// ========== Constructors ========== //
	Entity(const sf::Vector2f initPosition, bool active = false);
	Entity();
	// ========== Destructors ========== //
	virtual ~Entity();

	//================================================================//
	// ========== Initializers ========== //
	virtual void initialize_Collider(sf::RectangleShape*& pCollider, sf::Vector2f spriteSize); //Initialize a specific collider

	//================================================================//
	// ========== Loop methods ========== //
	virtual void execute(const float deltaTime) = 0;
	virtual void draw() const = 0;

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
	// _position
	virtual void setPosition(const sf::Vector2f position);
	virtual sf::Vector2f getPosition() const;
	// _collider
	virtual sf::RectangleShape* getCollider() const;
	// _active
	virtual void activate();
	virtual void desactivate();
	virtual bool isActive() const;
	// _pGraphMng
	static void setGraphManager(gMng* gMng);
	static gMng* getGraphManager();

protected:
	// ========== execute submethods ========== //
	virtual void updateAction(const float deltaTime);
	virtual void updateAnimation(const float deltaTime);
};

