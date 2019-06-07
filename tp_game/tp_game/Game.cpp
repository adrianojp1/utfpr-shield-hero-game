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

	//Window: zoom(5x), ratio (4:3), ratio multiplier (250)
	_window = new Graphical_Manager;
	Abstract_Entity::setGraphManager(_window);

	_main_menu = new Main_Menu();
	Main_Menu::setpGame(this);

	//Player: initial position (0, 0)
	_player1 = new Player(sf::Vector2f{-128.0f, 136.0f});
	_player1->setDefenseKey(sf::Keyboard::S);
	_player1->setJumpKey(sf::Keyboard::W);
	_player1->setLeftKey(sf::Keyboard::A);
	_player1->setRightKey(sf::Keyboard::D);

	_stage1 = new Stage(_player1);

	_deltaTime = 0.0f;
	Timer::setpDeltaTime(&_deltaTime);

	_main_menu->open();
} // end initialize

void Game::main_loop()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	while (_window->isOpen())
	{
		_deltaTime = _clock.restart().asSeconds(); //Iteration clock
		if (_deltaTime > 1.0f / 20.f)
			_deltaTime = 1.0f / 20.f;

		if (_main_menu->isActive())
		{
			_main_menu->execute(_deltaTime);
		}
		//_pause_menu;
		//_newGame_menu;
		//_saves_menu;
		if (!_main_menu->isActive())
		{
			_stage1->execute(_deltaTime);
		}

		_window->execute();

		_window->clear(); //Clear window buffer

		draw(); //Future game drawer: draw all objects

		_window->display(); //Show current frame
	}						//end main loop
}
void Game::close()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	_window->close();
}
// end main_loop

void Game::draw() const
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string) " | -ov: 0 | ");

	if (_main_menu->isActive())
	{
		_main_menu->draw();
	}
	else
	{
		_stage1->draw();
	}
} // end draw