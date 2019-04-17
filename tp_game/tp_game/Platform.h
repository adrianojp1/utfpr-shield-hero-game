#pragma once

//======================================================================================================================================//
// === Classes Headers === //
#include "Animator.h"

//======================================================================================================================================//
// === Classes Declaration === //
class MyWindow;

//======================================================================================================================================//
// === Platform Class === //
class Platform
{
private:
	// ========= Motion Members ========= //
	//Collider
	sf::RectangleShape* _collider;

	sf::Vector2f _position;

public:
	//================================================================//
	// ========== Constructors ========== //
	Platform(sf::Color color, sf::Vector2f size, sf::Vector2f position);
	// ========== Destructors ========== //
	~Platform();

	//================================================================//
	// ========== Loop methods ========== //
	void execute(float deltaTime);
	void draw(MyWindow* window);

	//================================================================//
	// ========== Collision ========== //
	void move(float dx, float dy) { _position += sf::Vector2f(dx, dy); }

	//================================================================//
	// ========== Sets & Gets ========== //
	// _position
	void setPosition(sf::Vector2f position);
	sf::Vector2f getPosition() const;
	// _collider
	sf::RectangleShape* getCollider() { return _collider; }
};