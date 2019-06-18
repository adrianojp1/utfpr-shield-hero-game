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

	std::vector<Entity*> _vblocksUnderneath;
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

	//virtual void onCollision(const sf::Vector2f collisionDirection);
	//virtual void collision_onLeft() = 0;
	//virtual void collision_onRight() = 0;

	//================================================================//
	// ========== State ========== //
	virtual void decreaseTimers();
	virtual void add_blockUnderneath(Entity* pBlock);
	virtual void clear_blocksUnderneath();

	//================================================================//
	// ========== State checkers ========== //
	
	virtual bool isAttacking() const = 0;
	
protected :
	// ========== execute submethods ========== //
	virtual void updateAction(const float deltaTime) = 0;
};
