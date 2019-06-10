#pragma once
//======================================================================================================================================//
// === Classes Headers === //
#include "Animator.h"		//Animations
#include "Timer.h"			//Timing effects
#include "Graphical_Manager.h"		//Drawer

//======================================================================================================================================//
// === Classes Declaration === //
class Game;

//======================================================================================================================================//
// === Derived classes from this === //
// Character
// Menu

//======================================================================================================================================//
// === Abstract_Entity Class === //
class Abstract_Entity
{
protected:
	static Graphical_Manager* _pGraphMng;
	static Game* _pGame;

	bool _active;

	sf::Vector2f _position;
public:
	//================================================================//
	// ========== Constructors ========== //
	Abstract_Entity(const sf::Vector2f initPosition, bool active = false);
	Abstract_Entity();
	// ========== Destructors ========== //
	virtual ~Abstract_Entity();

	//================================================================//
	// ========== Initializers ========== //
	
	//================================================================//
	// ========== Loop methods ========== //
	virtual void execute(const float deltaTime) = 0;
	virtual void draw() const = 0;

	//================================================================//
	// ========== Sets & Gets ========== //
	// _position
	virtual void setPosition(const sf::Vector2f position);
	virtual sf::Vector2f getPosition() const;
	// _active
	virtual void activate();
	virtual void desactivate();
	virtual bool isActive() const;
	// _pGraphMng
	static void setGraphManager(gMng* gMng);
	static gMng* getGraphManager();
	// _pGame
	static void setpGame(Game* pGame);
	static Game* getpGame();
};

