#pragma once

//======================================================================================================================================//
// === Classes Headers === //
#include "Stage.h"
#include "Main_Menu.h"

//======================================================================================================================================//
// === Game Class === //
class Game
{
private:
	Graphical_Manager* _window;

	Main_Menu* _main_menu;
	//Pause_Menu* _pause_menu;
	//NewGame_Menu* _newGame_menu;
	//Saves_Menu* _saves_menu;

	Player* _player1;
	//Player* _player2;

	Stage* _stage1;
	//Stage1* _stage2;

	//Time control
	float _deltaTime;
	sf::Clock _clock; //To get the deltaTime

public:
	//================================================================//
	// ========== Constructors ========== //
	Game();
	// ========== Destructors ========== //
	~Game();

	//================================================================//
	// ========== Initializers ========== //
	void initialize();

	//================================================================//
	void main_loop();
	void close();

	//================================================================//
	// ========== Loop methods ========== //
	void execute(float deltaTime);
	void draw() const;
};