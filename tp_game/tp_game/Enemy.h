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

	Timer _cd_attack;
	int _collisionDamage;
	int _attackDamage;

	bool _floor_foward;


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

	virtual void setAttackDmg(const int dmg);
	virtual int getAttackDmg() const;

	//================================================================//
	// ========== Motion ========== //
	virtual void attack() = 0;

	//================================================================//
	// ========== State ========== //
	virtual void decreaseTimers();

	//================================================================//
	// ========== State checkers ========== //
	virtual bool isAttacking() const;

	virtual const sf::Vector2f getFrontEdge() const;
	//_floor_foward
	virtual void setFloor_foward(const bool floor_fwd);
	virtual const bool getFloor_foward() const;
	
protected :
	// ========== execute submethods ========== //
	virtual void updateAction(const float deltaTime) = 0;
};
