#pragma once

//======================================================================================================================================//
// === Classes Headers === //
#include "Character.h" //Base class

//======================================================================================================================================//
// === Player Class === //
class Player : public Charc
{
private:
	// ========= Visual Members ========= //
	//Animators
	Animator *_idle_animator; //Idle
	Animator *_walk_animator; //Walking
	Animator *_def1_animator; //Normal defense
	Animator *_def2_animator; //Counter defense

	// ========= Motion Members ========= //
	//Colliders
	sf::RectangleShape* _idle_collider; //Idle
	sf::RectangleShape* _walk_collider; //Walking
	sf::RectangleShape* _def_collider; //Defense

	// ========= State control members ========= //
	bool _defending;
	bool _defCounterUp;

	Timer _defCounterTimer; //Timer for the defense counter

public:
	//================================================================//
	// ========== Constructors ========== //
	Player(const sf::Vector2f initPosition);
	Player();
	// ========== Destructors ========== //
	virtual ~Player();

	//================================================================//
	// ========== Initializers ========== //
	void initialize_AllAnimators(); //Initializes all the animators

	void initialize_AllColliders(); //Initializes all the colliders

	//================================================================//
	// ========== Loop methods ========== //
	void execute(const float deltaTime);
	void draw() const;

	//================================================================//
	// ========== State checkers ========== //
	bool isDefending() const;
	bool isCounterUp() const;
	bool isDefending_with_Counter() const;

private:
	// ========== Control keys methods ========== //
	bool leftIsKeyPressed() const;
	bool rightIsKeyPressed() const;
	bool jumpKeyPressed() const;
	bool defendKeyPressed() const;

	// ========== execute submethods ========== //
	void updateAction(const float deltaTime);
	void updateAnimation(const float deltaTime);
	//virtual bool isWalking(const float HorizontalMovement) const;

}; // end Player