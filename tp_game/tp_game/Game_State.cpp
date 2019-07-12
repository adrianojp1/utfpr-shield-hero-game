//======================================================================================================================================//
// === Pre-Compiled Header === //
#include "stdafx.h"

//======================================================================================================================================//
// === This Class Header === //
#include "Game_State.h"

//======================================================================================================================================//
// === Classes Headers === //
#include "Game.h"

//======================================================================================================================================//
// === Game_State methods === //
void Game_State::changeState(Game_State *pState)
{
	Game *pG = Game::getInstance();
	pG->changeState(pState);
	pG->execute();
}

Game_State::Game_State()
{
}

Game_State::~Game_State()
{
}

//======================================================================================================================================//
// === RunningStage methods === //
Game_State *RunningStage::_instance = NULL;

RunningStage::RunningStage()
{
}

RunningStage::~RunningStage()
{
}

void RunningStage::execute(const float deltaTime)
{
	Game *pG = Game::getInstance();
	if (pG->get_currentStage()->isPaused())
	{
		pG->open_Pause_Menu();
		Abstract_Entity::getGraphManager()->setViewCenter({0.0f, 0.0f});
		changeState(On_PauseMenu::getInstance());
	}
	else
		pG->get_currentStage()->execute(deltaTime);
}

void RunningStage::draw()
{
	Game::getInstance()->get_currentStage()->draw();
}

Game_State *RunningStage::getInstance()
{
	if (!_instance)
		_instance = static_cast<Game_State *>(new RunningStage);
	return _instance;
}

//======================================================================================================================================//
// === On_MainMenu methods === //
Game_State *On_MainMenu::_instance = NULL;

On_MainMenu::On_MainMenu()
{
}

On_MainMenu::~On_MainMenu()
{
}

void On_MainMenu::execute(const float deltaTime)
{
	Game *pG = Game::getInstance();
	if (pG->get_main_menu()->isOpen())
		pG->get_main_menu()->execute(deltaTime);

	else if (pG->get_newGame_menu()->isOpen())
		changeState(On_NewGameMenu::getInstance());
	else if (pG->isRunning_stage())
		changeState(RunningStage::getInstance());
	//if(Game::getInstance()->get_saves_menu()->isOpen())
	//	Game::getInstance()->changeState(On_SavesMenu::getInstance());
}

void On_MainMenu::draw()
{
	Game::getInstance()->get_main_menu()->draw();
}

Game_State *On_MainMenu::getInstance()
{
	if (!_instance)
		_instance = static_cast<Game_State *>(new On_MainMenu);
	return _instance;
}

//======================================================================================================================================//
// === On_NewGameMenu methods === //
Game_State *On_NewGameMenu::_instance = NULL;

On_NewGameMenu::On_NewGameMenu()
{
}

On_NewGameMenu::~On_NewGameMenu()
{
}

void On_NewGameMenu::execute(const float deltaTime)
{
	Game *pG = Game::getInstance();
	if (pG->get_newGame_menu()->isOpen())
		pG->get_newGame_menu()->execute(deltaTime);

	else if (pG->get_main_menu()->isOpen())
		changeState(On_MainMenu::getInstance());
	else
	{
		pG->start_newMatch(2, 5);
		changeState(RunningStage::getInstance());
	}
}

void On_NewGameMenu::draw()
{
	Game::getInstance()->get_newGame_menu()->draw();
}

Game_State *On_NewGameMenu::getInstance()
{
	if (!_instance)
		_instance = static_cast<Game_State *>(new On_NewGameMenu);
	return _instance;
}

//======================================================================================================================================//
// === On_NewGameMenu methods === //
Game_State *On_PauseMenu::_instance = NULL;

On_PauseMenu::On_PauseMenu()
{
}

On_PauseMenu::~On_PauseMenu()
{
}

void On_PauseMenu::execute(const float deltaTime)
{
	Game *pG = Game::getInstance();
	if (pG->get_main_menu()->isOpen())
		changeState(On_MainMenu::getInstance());
	else if (pG->get_pause_menu()->isOpen())
		pG->get_pause_menu()->execute(deltaTime);
	else
		changeState(RunningStage::getInstance());
}

void On_PauseMenu::draw()
{
	Game::getInstance()->get_pause_menu()->draw();
}

Game_State *On_PauseMenu::getInstance()
{
	if (!_instance)
		_instance = static_cast<Game_State *>(new On_PauseMenu);
	return _instance;
}
