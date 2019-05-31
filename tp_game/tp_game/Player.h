#pragma once

//======================================================================================================================================//
// === Classes Headers === //
#include "Character.h" //Base class

//======================================================================================================================================//
// === Player Class === //
class Player : public Character
{
private:
	// ========= State control members ========= //
	bool _defCounterUp;

	Timer _defCounterTimer; //Timer for the defense counter

	int _points;
public:
	//================================================================//
	// ========== Constructors ========== //
	Player(const sf::Vector2f initPosition);
	Player();
	// ========== Destructors ========== //
	virtual ~Player();

	//================================================================//
	// ========== Initializers ========== //
	void initialize_animator(); //Initializes all the animators

	//================================================================//
	// ========== Sets & Gets ========== //
	// _points
	void setPoints(const int pts);
	int getPoints() const;
	void add_points(const int pts);

	//================================================================//
	// ========== State checkers ========== //
	bool isDefending() const;
	bool isCounterUp() const;
	bool isDefending_with_Counter() const;

	//================================================================//
	// ========== States ========== //
	//virtual void setTo_death();
	virtual void setTo_combat();
private:
	// ========== Control keys methods ========== //
	bool leftIsKeyPressed() const;
	bool rightIsKeyPressed() const;
	bool jumpKeyPressed() const;
	bool anyMoveKeyPressed() const;
	bool defendKeyPressed() const;

	// ========== execute submethods ========== //
	void updateAction(const float deltaTime);
}; // end Player