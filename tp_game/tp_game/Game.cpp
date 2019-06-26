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

	destroy(_window);
	if (_pPlayer1)
		delete _pPlayer1;
	if (_pPlayer2)
		delete _pPlayer2;
	if (_main_menu)
		delete _main_menu;
	_stages.erase(_stages.begin(), _stages.end());
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

	_stages.push_back(NULL);
	_stages.push_back(NULL);
	_currentStage_index = 0;

	_deltaTime = 0.0f;
	Timer::setpDeltaTime(&_deltaTime);

	_main_menu->open();

	_state = On_MainMenu::getInstance();

	srand(static_cast<unsigned int>(time(NULL)));
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

void Game::initialize_stage(const int stg_id)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");
	int index = stg_id - 1;
	
	if (_stages[index])
	{
		delete _stages[index];
		_stages[index] = NULL;
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

	switch (stg_id)
	{
	case 1:
		_stages[index] = new Horizontal_Stage(_nPlayers);
		break;
	case 2:
		_stages[index] = new Vertical_Stage(_nPlayers);
		break;
	default:
		break;
	}
}

void Game::resetPlayers()
{
	if (_pPlayer1)
		_pPlayer1->reset();
	if (_pPlayer2)
		_pPlayer2->reset();
}

void Game::set_nPlayers(int nP)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	_nPlayers = nP;
}

void Game::set_currentStage(int stg_id)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	_currentStage_index = stg_id - 1;
}

Stage* Game::get_currentStage()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	return _stages[_currentStage_index];
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

void Game::destroy(void* pointer)
{
	if (pointer)
		delete pointer;
}

/*
void Game::load_save()
{
	recoverSave();
}

void Game::recoverSave()
{
	std::ifstream match_recoverer("save.dat", std::ios::in);
	if (!match_recoverer)
	{
		std::cerr << "File couldn't be opened!" << std::endl;
		fflush(stdin);
		getchar();
		return;
	}

	//match_recoverer >> *_stages[_currentStage_index];


	match_recoverer.close();
}

void Game::recordSave()
{
	std::ofstream match_recorder("save.dat", std::ios::out);
	if (!match_recorder)
	{
		std::cerr << "File couldn't be opened!" << std::endl;
		fflush(stdin);
		getchar();
		return;
	}

	match_recorder 
		<< _currentStage_index + 1 << ' '
		<< _stages[_currentStage_index]->get_lv_id() << '\n'
		<< 

	match_recorder.close();
}
*/
void Game::goToNextStage()
{
	if (_currentStage_index < _stages.size() - 1)
	{
		_currentStage_index++;
		start_stage(_currentStage_index + 1);
		execute();
	}
	else
	{
		std::cout << "Game finished!" << std::endl;
		getchar();
		/* Game was finished */
	}
}

void Game::pause_stage()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	if (isRunning_stage())
	{
		_stages[_currentStage_index]->pause();
	}
}

void Game::unpause_stage()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	if(isRunning_stage())
		_stages[_currentStage_index]->unpause();
}

bool Game::isRunning_stage()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	return _stages[_currentStage_index]->isRunning();
}

void Game::run_stage()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	_stages[_currentStage_index]->start();
}

void Game::stop_runningStage()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	_stages[_currentStage_index]->stop();
}

void Game::start_stage(int stg_id)
{
	initialize_stage(stg_id);
	set_currentStage(stg_id);
	run_stage();
}

void Game::start_newMatch(int stg_id, int lv_id)
{
	start_stage(stg_id);
	resetPlayers();
	get_currentStage()->set_lv_id(lv_id);
	get_currentStage()->start_currentLv();
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

	Game* pG = Game::getInstance();
	while (pG->_window->isOpen())
	{
		pG->update_deltaTime();

		pG->execute();

		pG->_window->execute();
		pG->_window->clear(); //Clear window buffer

		pG->draw();

		pG->_window->display(); //Show current frame
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
	float maxDeltaTime = 1.0f / 10.0f;
	_deltaTime = _clock.restart().asSeconds(); //Iteration clock
	if (_deltaTime > maxDeltaTime)
		_deltaTime = maxDeltaTime;
}

void Game::changeState(Game_State* state)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	_state = state;
}
