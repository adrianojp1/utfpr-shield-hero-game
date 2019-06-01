#pragma once

//======================================================================================================================================//
// === Classes Headers === //
#include "Character.h" //Base class

//======================================================================================================================================//
// === Enemy Class === //
class Enemy : public Character
{
private:
	// ========= State control members ========= //
	//bool _attacking;

	int _damage;
public:
	//================================================================//
	// ========== Constructors ========== //
	Enemy(const sf::Vector2f initPosition);
	Enemy();
	// ========== Destructors ========== //
	~Enemy();

	//================================================================//
	// ========== Initializers ========== //
	virtual void initialize_animator(); //Initializes all the animators

	virtual bool isVulnerable();

	virtual void setDmg(const int dmg);
	virtual int getDmg() const;
private :
	// ========== execute submethods ========== //
	void updateAction(const float deltaTime);
};
