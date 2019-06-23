//======================================================================================================================================//
// === Pre-Compiled Header === //
#include "stdafx.h"

//======================================================================================================================================//
// === This Class Header === //
#include "Game.h"

//======================================================================================================================================//
// === Static initializations === //
Game* Game::_instance = NULL;

//======================================================================================================================================//
// === Game methods === //
Game::Game()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	initialize();


} // end constr

Game::~Game()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	if (_window)
		delete _window;
	if (_pPlayer1)
		delete _pPlayer1;
	if (_stage1)
		delete _stage1;
} // end destr

Game* Game::getInstance()
{
	if (_instance == NULL) {
		_instance = new Game();
		main_loop();
	}
	return _instance;
}

void Game::initialize()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	//Window: zoom(5x), ratio (4:3), ratio multiplier (250)
	_window = new Graphical_Manager;
	Abstract_Entity::setGraphManager(_window);
	Tile::setRealSize(Tile::OriginalSize * gMng::textures_scale);

	_main_menu = new Main_Menu();
	_newGame_menu = new NewGame_Menu();
	_pause_menu = new Pause_Menu();

	_nPlayers = 0;
	_pPlayer1 = NULL;
	_pPlayer2 = NULL;

	initialize_player1();
	initialize_player2();
	Abstract_Entity::setpPlayer1(_pPlayer1);

	_stage1 = NULL;

	_deltaTime = 0.0f;
	Timer::setpDeltaTime(&_deltaTime);

	_runningStage = false;
	_main_menu->open();

	_state = On_MainMenu::getInstance();

	_currentStage = _stage1;
} // end initialize

void Game::initialize_player1()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	if (!_pPlayer1)
	{
		_pPlayer1 = new Player(sf::Vector2f{ -128.0f, 136.0f });
		_pPlayer1->setPlayer1_configs();
	}
}

void Game::initialize_player2()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	if (!_pPlayer2)
	{
		_pPlayer2 = new Player(sf::Vector2f{ -150.0f, 136.0f });
		_pPlayer2->setPlayer2_configs();
	}
}

void Game::initialize_stage1()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	if (_pPlayer1)
		_pPlayer1->reset();
	if (_pPlayer2)
		_pPlayer2->reset();

	if (_stage1)
	{
		delete _stage1;
		_stage1 = NULL;
	}

	if (_nPlayers == 2)
	{
		_pPlayer2->activate();
		Abstract_Entity::setpPlayer2(_pPlayer2);
	}
	else
	{
		_pPlayer2->desactivate();
		Abstract_Entity::setpPlayer2(NULL);
	}

	_stage1 = new Stage(2, _nPlayers);
}

void Game::set_nPlayers(int nP)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	_nPlayers = nP;
}

void Game::set_currentStage(int stg_id)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	if (stg_id == 1)
		_currentStage = _stage1;
	//else
		//_currentStage = stage2;
}

Stage* Game::get_currentStage()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	return _currentStage;
}

Main_Menu* Game::get_main_menu()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	return _main_menu;
}

NewGame_Menu* Game::get_newGame_menu()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	return _newGame_menu;
}

Pause_Menu* Game::get_pause_menu()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	return _pause_menu;
}

void Game::pause_stage()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	if (_runningStage)
	{
		_currentStage->pause();
	}
}

void Game::unpause_stage()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	if (_runningStage)
	{
		_currentStage->unpause();
	}
}

bool Game::isRunning_stage()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	return _runningStage;
}

void Game::run_stage()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	_runningStage = true;
	_currentStage->start();
}

void Game::stop_runningStage()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	_runningStage = false;
}

void Game::open_Main_Menu()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	_main_menu->open();
}

void Game::open_NewGame_Menu()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	_newGame_menu->open();
}

void Game::open_Saves_Menu()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

}

void Game::open_Pause_Menu()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	_pause_menu->open();
}

void Game::main_loop()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");
	
	while (Game::getInstance()->_window->isOpen())
	{
		Game::getInstance()->update_deltaTime();

		Game::getInstance()->execute();

		Game::getInstance()->_window->execute();
		Game::getInstance()->_window->clear(); //Clear window buffer

		Game::getInstance()->draw();

		Game::getInstance()->_window->display(); //Show current frame
	}
}

void Game::close()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	_window->close();
}
// end main_loop

void Game::execute()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	_state->execute(_deltaTime);
}

void Game::draw()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	_state->draw();
} // end draw

void Game::update_deltaTime()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	_deltaTime = _clock.restart().asSeconds(); //Iteration clock
	if (_deltaTime > 1.0f / 20.f)
		_deltaTime = 1.0f / 20.f;
}

void Game::changeState(Game_State* state)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	_state = state;
}
