#pragma once

//======================================================================================================================================//
// === Classes Headers === //
#include "Entity.h" //Base class

//======================================================================================================================================//
// === Classes Declaration === //

//======================================================================================================================================//
// === Block Class === //
class Block : public Entity
{
private:
	// ========= Motion Members ========= //
	//Collider
	sf::RectangleShape* _collider;

	//sf::Vector2f _position;

public:
	//================================================================//
	// ========== Constructors ========== //
	Block(const sf::Vector2f initPosition);
	Block();
	// ========== Destructors ========== //
	virtual ~Block();

	//================================================================//
	// ========== Loop methods ========== //
	virtual void execute(const float deltaTime);
	virtual void draw(MyWindow* window) const;

	//================================================================//
	// ========== Collision ========== //
	//void move(float dx, float dy) { _position += sf::Vector2f(dx, dy); }

	//================================================================//
	// ========== Sets & Gets ========== //
	// _position
	//void setPosition(sf::Vector2f position);
	//sf::Vector2f getPosition() const;
	// _collider
	//sf::RectangleShape* getCollider() { return _collider; }
};