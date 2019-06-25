#pragma once

//======================================================================================================================================//
// === Classes Headers === //
#include "Enemy.h"

//======================================================================================================================================//
// === Orc Class === //
class Orc : public Enemy
{
private:
	sf::RectangleShape _attack_rect;
public:
	//================================================================//
	// ========== Constructors ========== //
	Orc(const sf::Vector2f initPosition);
	Orc();
	// ========== Destructors ========== //
	~Orc();

	//================================================================//
	// ========== Initializers ========== //
	void initialize_animator(); //Initializes all the animators

	//================================================================//
	// ========== Motion ========== //
	void colliding_onLeft();
	void colliding_onRight();
	void doPrincipalOfAttack();
	//================================================================//
	// ========== State checkers ========== //
	//bool isAttacking() const;
	virtual sf::RectangleShape* getAttackRect();
private:
	// ========== execute submethods ========== //
	void updateAction(const float deltaTime);
};

