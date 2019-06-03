#pragma once

//======================================================================================================================================//
// === Classes Headers === //
#include "Character.h" //Base class

//======================================================================================================================================//
// === Enemy Class === //
class Enemy : public Character
{
protected:
	// ========= State control members ========= //
	bool _attacking;
	bool _canAttack;

	Timer cd_attack;
	int _collisionDamage;
public:
	//================================================================//
	// ========== Constructors ========== //
	Enemy(const sf::Vector2f initPosition);
	Enemy();
	// ========== Destructors ========== //
	virtual ~Enemy();

	//================================================================//
	// ========== Initializers ========== //
	virtual void initialize_animator() = 0; //Initializes all the animators

	virtual bool isVulnerable();

	virtual void setCollDmg(const int dmg);
	virtual int getCollDmg() const;

	//================================================================//
	// ========== Motion ========== //
	virtual void attack() = 0;

	//================================================================//
	// ========== State ========== //
	virtual void decreaseTimers();

	//================================================================//
	// ========== State checkers ========== //
	
	virtual bool isAttacking() const = 0;
protected :
	// ========== execute submethods ========== //
	virtual void updateAction(const float deltaTime) = 0;
};
