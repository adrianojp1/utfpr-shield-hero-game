#pragma once

//======================================================================================================================================//
// === Classes Headers === //
#include "Character.h" //Base class

#include "Player.h"
//======================================================================================================================================//
// === Enemy Class === //
class Enemy : public Character
{
protected:
	// ========= State control members ========= //
	bool _canCauseDmg;

	Timer _cd_attack;
	int _collisionDamage;
	int _attackDamage;

	bool _floor_foward;

	sf::RectangleShape _overView;
	sf::Vector2f _attack_offset;
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

	//================================================================//
	// ========== Sets & Gets ============== //
	virtual void setCollDmg(const int dmg);
	virtual int getCollDmg() const;

	virtual void setAttackDmg(const int dmg);
	virtual int getAttackDmg() const;

	//_floor_foward
	virtual void setFloor_foward(const bool floor_fwd);
	virtual const bool getFloor_foward() const;

	virtual sf::RectangleShape* getAttackRect() const;
	//================================================================//
	// ========== Motion ========== //
	virtual void attack();
	virtual void updateAttack();
	//================================================================//
	// ========== State ========== //
	virtual void decreaseTimers();
	virtual Player* a_playerInRange();
	virtual bool playerAhead(Player* pPlayer);
	virtual void die();
	virtual void updateAnime_n_Collider();
	virtual void check_attack();
	virtual void followAPlayer();
	//================================================================//
	// ========== State checkers ========== //
	virtual bool isAttacking() const;
	virtual bool principalFrameOfAttack();
	virtual void doPrincipalOfAttack() = 0;
	virtual const sf::Vector2f getFrontEdge() const;
	bool ableToCauseDamage();
protected :
	// ========== execute submethods ========== //
	virtual void updateAction(const float deltaTime) = 0;
};
