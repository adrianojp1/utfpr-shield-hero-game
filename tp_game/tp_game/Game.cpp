//======================================================================================================================================//
// === Pre-Compiled Header === //
#include "stdafx.h"

//======================================================================================================================================//
// === This Class Header === //
#include "Game.h"

//======================================================================================================================================//
// === Game methods === //
Game::Game()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	initialize();

	main_loop();
} // end constr

Game::~Game()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	if (_window)
		delete _window;
	if (_player1)
		delete _player1;
	if (_stage1)
		delete _stage1;
} // end destr

void Game::initialize()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	Abstract_Entity::setpGame(this);

	//Window: zoom(5x), ratio (4:3), ratio multiplier (250)
	_window = new Graphical_Manager;
	Abstract_Entity::setGraphManager(_window);

	_main_menu = new Main_Menu();
	_newGame_menu = new NewGame_Menu();
	_pause_menu = new Pause_Menu();

	_nPlayers = 0;
	_player1 = NULL;
	_player2 = NULL;
	_currentStage = NULL;

	_stage1 = NULL;

	_deltaTime = 0.0f;
	Timer::setpDeltaTime(&_deltaTime);

	_runningStage = false;
	_main_menu->open();
	_currentStage = _stage1;
} // end initialize

void Game::initialize_player1()
{
	if (!_player1)
	{
		_player1 = new Player(sf::Vector2f{ -128.0f, 136.0f });
		_player1->setDefenseKey(sf::Keyboard::S);
		_player1->setJumpKey(sf::Keyboard::W);
		_player1->setLeftKey(sf::Keyboard::A);
		_player1->setRightKey(sf::Keyboard::D);
	}
}

void Game::initialize_player2()
{
	if (!_player2)
	{
		_player2 = new Player(sf::Vector2f{ -150.0f, 136.0f });
		_player2->setDefenseKey(sf::Keyboard::K);
		_player2->setJumpKey(sf::Keyboard::I);
		_player2->setLeftKey(sf::Keyboard::J);
		_player2->setRightKey(sf::Keyboard::L);
	}
}

void Game::initialize_stage1()
{
	if (!_stage1)
	{
		_stage1 = new Stage();

		initialize_player1();
		_stage1->setpPlayer1(_player1);

		if (_nPlayers == 2)
		{
			initialize_player2();
			_stage1->setpPlayer2(_player2);
		}
	}
}

void Game::set_nPlayers(int nP)
{
	_nPlayers = nP;
}

void Game::set_currentStage(int stg_id)
{
	if (stg_id == 1)
		_currentStage = _stage1;
	//else
		//_currentStage = stage2;
}

void Game::pause_stage()
{
	if (_runningStage)
	{
		_currentStage->pause();
	}
}

void Game::unpause_stage()
{
	if (_runningStage)
	{
		_currentStage->unpause();
	}
}

bool Game::isRunning_stage()
{
	return _runningStage;
}

void Game::run_stage()
{
	_runningStage = true;
	unpause_stage();
}

void Game::stop_runningStage()
{
	_runningStage = false;
}

void Game::open_Main_Menu()
{
	_main_menu->open();
}

void Game::open_NewGame_Menu()
{
	_newGame_menu->open();
}

void Game::open_Saves_Menu()
{
}

void Game::open_Pause_Menu()
{
	_pause_menu->open();
}

void Game::main_loop()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	while (_window->isOpen())
	{
		update_deltaTime();

		this->execute();

		_window->execute();
		_window->clear(); //Clear window buffer

		this->draw();

		_window->display(); //Show current frame
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
	if (!_runningStage)
	{
		if (_main_menu->isOpen())
		{
			_main_menu->execute(_deltaTime);
		}
		else if (_newGame_menu->isOpen())
		{
			_newGame_menu->execute(_deltaTime);
		}/*
		else if (_saves_menu->isActive())
		{
			_saves_menu->execute(_deltaTime);
		}*/
	}

	if (_runningStage)
	{
		if (_currentStage->isPaused())
		{
			_pause_menu->execute(_deltaTime);
		}
		else
		{
			_stage1->execute(_deltaTime);
		}
	}
}

void Game::draw()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	if (!_runningStage)
	{
		if (_main_menu->isOpen())
		{
			_main_menu->draw();
		}
		else if (_newGame_menu->isOpen())
		{
			_newGame_menu->draw();
		}/*
		else if (_saves_menu->isActive())
		{
			_saves_menu->draw();
		}*/
	}

	if (_runningStage)
	{
		if (_currentStage->isPaused())
		{
			_pause_menu->draw();
		}
		else
		{
			_stage1->draw();
		}
	}
} // end draw

void Game::update_deltaTime()
{
	_deltaTime = _clock.restart().asSeconds(); //Iteration clock
	if (_deltaTime > 1.0f / 20.f)
		_deltaTime = 1.0f / 20.f;
}
