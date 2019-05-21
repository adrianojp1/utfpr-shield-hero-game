#pragma once

//======================================================================================================================================//
// === Classes Headers === //
#include "Character.h" //Base class

//======================================================================================================================================//
// === Enemy2 Class === //
class Enemy : public Charc
{
private:
	// ========= Visual Members ========= //
	//Animators
	Animator* _idle_animator; //Idle
	Animator* _walk_animator; //Walking
	Animator* _attack_animator; //Shoot (skeleton)
	Animator* _dead_animator; //Dying

	// ========= Motion Members ========= //
	//Colliders
	sf::RectangleShape* _idle_collider; //Idle
	sf::RectangleShape* _walk_collider; //Walking
	//sf::RectangleShape* _attack_collider; //(if change when is attacking)

	// ========= State control members ========= //
	bool _attacking;

public:
	//================================================================//
	// ========== Constructors ========== //
	Enemy(const sf::Vector2f initPosition);
	Enemy();
	// ========== Destructors ========== //
	~Enemy();

	//================================================================//
	// ========== Initializers ========== //
	void initialize_AllAnimators(); //Initializes all the animators

	void initialize_AllColliders(); //Initializes all the colliders
	void initialize_Collider(sf::RectangleShape*& pCollider, const sf::Vector2f size);		//Initialize a specific collider

	//================================================================//
	// ========== Loop methods ========== //
	void execute(const float deltaTime);
	void draw(MyWindow* window) const;
	
};
