#pragma once

//======================================================================================================================================//
// === Classes Headers === //
#include "Enemy.h"
#include "Projectile_List.h"

//======================================================================================================================================//
// === Skeleton Class === //
class Skeleton : public Enemy
{
private:

public:
	//================================================================//
	// ========== Constructors ========== //
	Skeleton(const sf::Vector2f initPosition);
	Skeleton();
	// ========== Destructors ========== //
	virtual ~Skeleton();

	//================================================================//
	// ========== Initializers ========== //
	virtual void initialize_animator() = 0; //Initializes all the animators

	//================================================================//
	// ========== Motion ========== //
	virtual int getProj_id() = 0;
	void updateAttack();
	void cast_spell();
	void doPrincipalOfAttack();
	//================================================================//
	// ========== State checkers ========== //
private:
	//bool isAttacking() const;
protected:
	// ========== execute submethods ========== //
	virtual void updateAction(const float deltaTime);
};
