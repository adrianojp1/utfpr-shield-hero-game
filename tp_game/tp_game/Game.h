#pragma once

//======================================================================================================================================//
// === Classes Headers === //
#include "Stage.h"
#include "Main_Menu.h"
#include "NewGame_menu.h"
#include "Pause_Menu.h"

//======================================================================================================================================//
// === Game Class === //
class Game
{
private:
	Graphical_Manager* _window;

	Main_Menu* _main_menu;
	NewGame_Menu* _newGame_menu;
	//Saves_Menu* _saves_menu;
	Pause_Menu* _pause_menu;

	int _nPlayers;
	Player* _player1;
	Player* _player2;

	Stage* _stage1;
	//Stage1* _stage2;
	Stage* _currentStage;

	//Save* _currentSave;

	//State control
	bool _runningStage; //True if a stage is running, paused or not
	
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
	void initialize_player1();
	void initialize_player2();
	void initialize_stage1();

	//================================================================//
	// ========== Menus ========== //
	void open_Main_Menu();
	void open_NewGame_Menu();
	void open_Saves_Menu();
	void open_Pause_Menu();

	//================================================================//
	void main_loop();
	void execute();
	void draw();
	void update_deltaTime();

	void close();

	void set_nPlayers(int nP);
	void set_currentStage(int stg_id);

	void pause_stage();
	void unpause_stage();
	bool isRunning_stage();
	void run_stage();
	void stop_runningStage();
};