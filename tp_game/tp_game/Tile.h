#pragma once

//======================================================================================================================================//
// === Classes Headers === //
#include "Entity.h" //Base class

//======================================================================================================================================//
// === Tile Class === //
class Tile : public Entity
{
protected:
	// ========= Motion Members ========= //
	sf::RectangleShape* _collider;

	static sf::Vector2f _realSize;
public:
	//================================================================//
	// ========== Constructors ========== //
	Tile(const sf::Vector2f initPosition, const int id = 2);
	Tile();
	// ========== Destructors ========== //
	virtual ~Tile();

	//================================================================//
	// ========== Initializers ========== //
	virtual void initialize_animator();

	virtual sf::Vector2i getTileRectPos(int id);

	//================================================================//
	// ========== Loop methods ========== //
	virtual void execute(const float deltaTime);
	virtual void draw();

	virtual void colliding_onTop();
	virtual void updateAnime();

	//_realSize
	static void setRealSize(const sf::Vector2f realSize);
	static const sf::Vector2f getRealSize();
	//================================================================//
	//======================== Static Consts =========================//
	static const sf::Vector2f OriginalSize;
};