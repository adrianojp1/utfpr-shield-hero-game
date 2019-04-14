#pragma once

//======================================================================================================================================//
// === Classes Headers === //
#include "Animator.h"

//======================================================================================================================================//
// === Classes Declaration === //
class MyWindow;

//======================================================================================================================================//
// === Player Class === //
class Player
{
private:
	// ========= Visual Members ========= //
	//Player animators
	Animator* _idle_anmt; //Animator for idle state
	Animator* _walk_anmt; //Animator for walk state
	
	sf::Sprite _sprite; //Sprite for textures setting
	bool _facingRight; //Bool for the side direction
	
	// ========= Motion Members ========= //
	float _speed; //Horizontal speed
	float _jumpHeight;
	sf::Vector2f _position;

public:
	//================================================================//
	// ========== Constructors ========== //
	Player(sf::Vector2f initPosition, float speed, float jumpHeight);
	Player();
	// ========== Destructors ========== //
	~Player();

	//================================================================//
	// ========== Initializers ========== //
	void initializeAnimators();

	//================================================================//
	// ========== Loop methods ========== //
	void execute(float deltaTime);
	void draw(MyWindow* window);

private:
	// ========== Control keys methods ========== //
	bool leftIsKeyPressed();
	bool rightIsKeyPressed();
	bool jumpKeyPressed();
	bool defendKeyPressed();

	// ========== execute submethods ========== //
	void updatePosition(sf::Vector2f* movement, float deltaTime);
	void updateAnimation(sf::Vector2f movement, float deltaTime);
	void moveToLeft(float* HorizontalMovement, float offset);
	void moveToRight(float* HorizontalMovement, float offset);
	bool isIdle(float HorizontalMovement);
};

