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
	Timer _invulnerability;

	int _state;

	int _hp;
public:
	//================================================================//
	// ========== Constructors ========== //
	Character(const sf::Vector2f initPosition);
	Character();
	// ========== Destructors ========== //
	virtual ~Character();

	//================================================================//
	// ========== Initializers ========== //
	virtual void initialize_AllColliders();

	//================================================================//
	// ========== Loop methods ========== //
	virtual void execute(const float deltaTime);
	virtual void draw() const;

	//================================================================//
	// ========== Motion ========== //
	virtual void onCollision(const sf::Vector2f collisionDirection);
	virtual bool isVulnerable();
	virtual bool isDying();
	virtual void takeDmg(const int dmg);
	virtual void die();

	//================================================================//
	// ========== Sets & Gets ========== //
	// _jumpHeight
	virtual void setJumpHeight(const float jumpHeight);
	virtual float getJumpHeight() const;
	// _hp
	virtual void setHp(const int hp);
	virtual int getHp() const;

	//================================================================//
	// ========== States ========== //
	virtual void updateState();
	virtual void setTo_idle();
	virtual void setTo_walk();
	virtual void setTo_death();
	virtual void setTo_combat();
protected:
	// ========== execute submethods ========== //
	virtual void updateAction(const float deltaTime) = 0;

	//================================================================//
	//======================== Static Consts =========================//
	//States
	static const int IDLE;
	static const int WALK;
	static const int DEATH;
	static const int COMBAT;
};

typedef Character Charc;