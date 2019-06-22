#pragma once
//======================================================================================================================================//
// === Classes Headers === //
#include "Animator.h"		//Animations
#include "Timer.h"			//Timing effects
#include "Graphical_Manager.h"		//Drawer

//======================================================================================================================================//
// === Classes Declaration === //
class Player;

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

	bool _active;

	sf::Vector2f _position;

	static Player* _pPlayer1;
	static Player* _pPlayer2;

	int _id;
public:
	//================================================================//
	// ========== Constructors ========== //
	Abstract_Entity(const sf::Vector2f initPosition, const bool active = false, const int id = -1);
	Abstract_Entity();
	// ========== Destructors ========== //
	virtual ~Abstract_Entity();

	//================================================================//
	// ========== Initializers ========== //
	
	//================================================================//
	// ========== Loop methods ========== //
	virtual void execute(const float deltaTime) = 0;
	virtual void draw() = 0;

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
	// _pPlayer1
	static void setpPlayer1(Player* pP1);
	static Player* getpPlayer1();
	// _pPlayer2
	static void setpPlayer2(Player* pP2);
	static Player* getpPlayer2();
	//_id
	void setId(const int id);
	const int getId();
};

