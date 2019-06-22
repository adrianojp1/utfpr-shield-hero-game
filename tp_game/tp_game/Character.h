#pragma once

//======================================================================================================================================//
// === Classes Headers === //
#include "Entity.h" //Base class

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
	sf::RectangleShape *_idle_collider;   //Idle
	sf::RectangleShape *_walk_collider;   //Walking
	sf::RectangleShape *_combat_collider; //Defense
	sf::RectangleShape *_death_collider;  //Death

	// ========= Motion Members ========= //
	float _jumpHeight;

	// ========= State control members ========= //
	bool _canJump;

	Timer _invulnerability;
	bool _vulnerable;

	int _state;

	int _hp;
	int _maxHp;

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
	virtual void initialize_animator() = 0;

	//================================================================//
	// ========== Loop methods ========== //
	virtual void execute(const float deltaTime);
	//virtual void draw();

	//================================================================//
	// ========== Motion ========== //
	virtual void updateAction(const float deltaTime) = 0;
	virtual void updateDeath();
	virtual void updatePosition(const float deltaTime);
	virtual void applyGforce(const float deltaTime);
	virtual void jump();
	virtual void moveToLeft(const float speedMultiplier = 1.0f);
	virtual void moveToRight(const float speedMultiplier = 1.0f);
	virtual void moveFoward();
	virtual void colliding_onBottom();

	//================================================================//
	// ========== State ========== //
	virtual bool isVulnerable();
	virtual void apply_invulnerable_effect();
	virtual void apply_default_effect();
	virtual bool isDying();
	virtual void takeDmg(const int dmg);
	virtual void die();
	virtual void doAfterDeath();
	virtual void ressurect();
	virtual void resetHp();
	virtual void decreaseTimers();

	virtual void updateAnime_n_Collider(const float deltaTime);

	//================================================================//
	// ========== Sets & Gets ========== //
	// _jumpHeight
	virtual void setJumpHeight(const float jumpHeight);
	virtual float getJumpHeight() const;
	// _hp
	virtual void setHp(const int hp);
	virtual int getHp() const;
	//_maxHp;
	virtual void setMaxHp(const int maxHp);
	virtual int getMaxHp() const;

	//================================================================//
	// ========== States ========== //
	virtual void switchAnime_n_Collider();
	virtual void switchTo_idle();
	virtual void switchTo_walk();
	virtual void switchTo_death();
	virtual void switchTo_combat();

protected:
	//================================================================//
	//======================== Static Consts =========================//
	enum States {
		IDLE,
		WALK,
		DEATH,
		COMBAT
	};
};

typedef Character Charc;