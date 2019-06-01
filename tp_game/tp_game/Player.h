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

	sf::Keyboard::Key _jumpKey;
	sf::Keyboard::Key _leftKey;
	sf::Keyboard::Key _rightKey;
	sf::Keyboard::Key _defenseKey;
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
	//Keys
	void setJumpKey(const sf::Keyboard::Key jumpkey);
	sf::Keyboard::Key getJumpKey() const;
	void setRightKey(const sf::Keyboard::Key rightKey);
	sf::Keyboard::Key getRightKey() const;
	void setLeftKey(const sf::Keyboard::Key leftKey);
	sf::Keyboard::Key getLeftKey() const;
	void setDefenseKey(const sf::Keyboard::Key defenseKey);
	sf::Keyboard::Key getDefenseKey() const;

	//================================================================//
	// ========== State checkers ========== //
	bool isDefending() const;
	bool isCounterUp() const;
	bool isDefending_with_Counter() const;

	//================================================================//
	// ========== States ========== //
	virtual void setTo_combat();
	virtual void resetHp();
	virtual void decreaseTimers();
	virtual void manageDefenseCounter();
	virtual void ressurect();
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