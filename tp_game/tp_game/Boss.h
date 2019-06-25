#pragma once
// === Classes Headers === //
#include "Enemy.h"

//======================================================================================================================================//
// === Boss Class === //
class Boss :
	public Enemy
{
private:
	sf::RectangleShape _attack_rect;
public:
	//================================================================//
	// ========== Constructors ========== //
	Boss(const sf::Vector2f initPosition);
	Boss();
	// ========== Destructors ========== //
	~Boss();

	//================================================================//
	// ========== Initializers ========== //
	void initialize_animator(); //Initializes all the animators

	virtual void attack();
	virtual bool principalFrameOfAttack();
	virtual void doPrincipalOfAttack();
	virtual void updateAction(const float deltaTime);

	virtual sf::RectangleShape* getAttackRect();
};